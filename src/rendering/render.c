/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 20:37:04 by kschmidt          #+#    #+#             */
/*   Updated: 2023/05/04 13:51:14 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
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

t_intersection find_closest_intersection(t_minirt *minirt, t_vec3 ray_start, t_vec3 ray_dir)
{
	t_intersection closest_isect;
	t_intersection isect;
	t_object *obj = minirt->world.objects;

	closest_isect = (t_intersection){0, INFINITY, {0, 0, 0}, {0, 0, 0}};
	while (obj)
	{
		isect.obj = obj;
		isect.pos = obj->f_intersect(obj, ray_start, ray_dir);
		if (isnan(isect.pos.x) || isnan(isect.pos.y) || isnan(isect.pos.z))
		{
			obj = obj->next;
			continue;
		}
		isect.normal = obj->f_get_normal(obj, isect.pos);
		isect.t = vec3_mag(vec3_sub(isect.pos, ray_start));

		if (isect.t < closest_isect.t && isfinite(isect.t))
			closest_isect = isect;

		obj = obj->next;
	}

	return closest_isect;
}

#define MAX_DEPTH 5
#define MAT_REFLECTIVE 0.01f
#define MAT_TRANSPARENCY 0.0f
#define MAT_IOR 1.5f

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
		isect = find_closest_intersection(mrt, closest_isect.pos, refl_dir);
		if (isect.obj)
		{
			t_color refl_color = sample_color_at_intersection(mrt, isect, refl_dir, depth + 1);
			color = color_add(color, color_scale(refl_color, MAT_REFLECTIVE));
		}
	}

	if (MAT_TRANSPARENCY > 0.0f)
	{
		t_vec3 refr_dir = vec3_refract(ray_dir, isect.normal, MAT_IOR);
		isect = find_closest_intersection(mrt, closest_isect.pos, refr_dir);
		if (isect.obj)
		{
			t_color refr_color = sample_color_at_intersection(mrt, isect, refr_dir, depth + 1);
			color = color_add(color, color_scale(refr_color, MAT_TRANSPARENCY));
		}
	}
	return color;
}

void render_scene(t_minirt *minirt)
{
	t_vec3 ray_start = minirt->world.camera.pos;
	t_color bg_color = minirt->world.ambient.color;
	t_color pixel_color;

	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			// calculate the ray direction for the current pixel
			t_vec3 ray_dir = calculate_ray_direction(minirt, x, y);

			// find the closest intersection point of the ray with the objects in the scene
			t_intersection isect = find_closest_intersection(minirt, ray_start, ray_dir);

			// sample the color at the intersection point or the background color
			if (isect.obj) {
				pixel_color = sample_color_at_intersection(minirt, isect,
																 ray_dir, 0);
				// last ray to light source
				t_vec3 light_dir = vec3_normalize(vec3_sub(minirt->world.light.pos, isect.pos));
				t_intersection isect2 = find_closest_intersection(minirt, isect.pos, light_dir);
				if (!isect2.obj || vec3_mag(vec3_sub(minirt->world.light.pos, isect.pos)) > isect2.t)
					pixel_color = color_scale(minirt->world.ambient.color, minirt->world.ambient.brightness);
			}
			else
				pixel_color = bg_color;
			mrt_pixel_put(&minirt->img, x, y, pixel_color);
		}
	}

	mlx_put_image_to_window(minirt->ctx, minirt->win, minirt->img.img, 0, 0);
	mlx_string_put(minirt->ctx, minirt->win, 10, 20, 0xFFF, "Rendering Done!");
}