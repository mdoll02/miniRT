/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 20:37:04 by kschmidt          #+#    #+#             */
/*   Updated: 2023/05/10 09:40:55 by mdoll            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include "rendering.h"
#include "mlx/mlx.h"
#include "vec_math.h"
#include "color_math.h"


static unsigned int	color_to_int(t_color color)
{
	return (((int)color.r & 0xff) << 16
		| ((int)color.g & 0xff) << 8
		| ((int)color.b & 0xff));
}

static void	mrt_pixel_put(t_mlx_image* img, int x, int y, t_color color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x
			* (img->bbp / 8));
	*(unsigned int *)dst = color_to_int(color);
}

t_vec3 calculate_ray_direction(t_minirt *minirt, int x, int y)
{
	float u = (float)x / WIDTH;
	float v = (float)y / HEIGHT;

	return vec3_normalize((t_vec3){
			(2 * u - 1) * tanf(minirt->world.camera.fov / 2),
			(2 * v - 1) * tanf(minirt->world.camera.fov / 2) / (WIDTH / HEIGHT),
			-1
	});
}

t_intersection find_closest_intersection(t_minirt *minirt, t_vec3 ray_start, t_object *ignore, t_vec3 ray_dir)
{
	t_intersection closest_isect;
	t_intersection isect;
	t_object *obj = minirt->world.objects;

	closest_isect = (t_intersection){0, INFINITY, {0, 0, 0}, {0, 0, 0}};
	while (obj)
	{
		if (obj == ignore)
		{
			obj = obj->next;
			continue;
		}
		isect = obj->f_intersect(obj, ray_start, ray_dir);
		isect.obj = obj;
		if (isnan(isect.pos.x) || isnan(isect.pos.y) || isnan(isect.pos.z))
		{
			obj = obj->next;
			continue;
		}
		isect.t = vec3_mag(vec3_sub(isect.pos, ray_start));

		if (isect.t < closest_isect.t && isfinite(isect.t))
			closest_isect = isect;

		obj = obj->next;
	}

	return closest_isect;
}

int is_illuminated(t_minirt *mrt, t_intersection isect, t_light light)
{
	t_vec3 dir = vec3_sub(light.pos, isect.pos);
	double dist = vec3_mag(dir);
	dir = vec3_normalize(dir);
	t_intersection obstructed = find_closest_intersection(mrt, isect.pos, isect.obj, dir);
	return !obstructed.obj || vec3_mag(vec3_sub(obstructed.pos, isect.pos)) > dist;
}

#define MAX_DEPTH 5
#define MAT_REFLECTIVE .5f
#define MAT_TRANSPARENCY .0f
#define MAT_IOR .4f

t_color sample_color_at_intersection(t_minirt *mrt, t_intersection closest_isect
									 , t_vec3 ray_dir, int depth)
{
	if (depth >= MAX_DEPTH)
		return (t_color){0, 0, 0};

	t_color color = closest_isect.obj->f_sample_color(closest_isect.obj, closest_isect.pos);

	t_intersection isect;
	if (MAT_REFLECTIVE > 0.0f)
	{
		t_vec3 refl_dir = vec3_reflect(ray_dir, closest_isect.normal);
		isect = find_closest_intersection(mrt, closest_isect.pos, closest_isect.obj, refl_dir);
		if (isect.obj)
		{
			t_color refl_color = sample_color_at_intersection(mrt, isect, refl_dir, depth + 1);
			color = color_add(color, color_scale(refl_color, MAT_REFLECTIVE));
		}
	}

	if (MAT_TRANSPARENCY > 0.0f)
	{
		t_vec3 refr_dir = vec3_refract(ray_dir, isect.normal, MAT_IOR);
		isect = find_closest_intersection(mrt, closest_isect.pos, closest_isect.obj, refr_dir);
		if (isect.obj)
		{
			t_color refr_color = sample_color_at_intersection(mrt, isect, refr_dir, depth + 1);
			color = color_add(color, color_scale(refr_color, MAT_TRANSPARENCY));
		}
	}

	int illuminated = is_illuminated(mrt, closest_isect, mrt->world.light);
	t_vec3 light_dir = vec3_normalize(vec3_sub(mrt->world.light.pos, closest_isect.pos));
	double diffuse = vec3_dot(closest_isect.normal, light_dir);
	if (diffuse < 0)
		diffuse = -diffuse;
	color = color_scale(color, diffuse);
	if (!illuminated)
		color = color_scale(color, 0.1f);
	return color;
}

void render_scene(t_minirt *minirt)
{
	t_vec3 ray_start = minirt->world.camera.pos;
	t_color bg_color = minirt->world.ambient.color;
	t_color pixel_color;

	for (int y = 0; y < HEIGHT; y++)
	{
		printf("\rRendering: %d%%", (int) (100.0f * y / HEIGHT));
		for (int x = 0; x < WIDTH; x++)
		{
			// calculate the ray direction for the current pixel
			t_vec3 ray_dir = calculate_ray_direction(minirt, x, y);

			// find the closest intersection point of the ray with the objects in the scene
			t_intersection isect = find_closest_intersection(minirt, ray_start, 0, ray_dir);

			// sample the color at the intersection point or the background color
			if (isect.obj) {
				pixel_color = sample_color_at_intersection(minirt, isect,
																 ray_dir, 0);
			}
			else
				pixel_color = bg_color;
			mrt_pixel_put(&minirt->img, x, y, pixel_color);
		}
	}
	printf("\rRendering: 100%%\n");
	mlx_put_image_to_window(minirt->ctx, minirt->win, minirt->img.img, 0, 0);
	mlx_string_put(minirt->ctx, minirt->win, 10, 20, 0xFFF, "Rendering Done!");
}