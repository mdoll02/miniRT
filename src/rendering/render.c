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

static void	mrt_pixel_put(t_mlx_image *img, int x, int y, t_color color)
{
	char	*dst;

	dst = img->addr + ((HEIGHT - 1 - y) * img->line_length + \
										x * (img->bbp / 8));
	*(unsigned int *)dst = color_to_int(color);
}

t_vec3	calculate_ray_direction(t_minirt *minirt, int x, int y)
{
	double	u;
	double	v;
	double	fov_radians;
	t_vec3	ray_dir;
	double	ar;

	u = (double)x / WIDTH;
	v = (double)y / HEIGHT;
	ar = (double)WIDTH / HEIGHT;
	fov_radians = minirt->world.camera.fov * M_PI / 180.0;
	ray_dir.x = (2 * u - 1) * tan(fov_radians / 2);
	ray_dir.y = (2 * v - 1) * tan(fov_radians / 2) / ar;
	ray_dir.z = -1;
	ray_dir = vec3_normalize(ray_dir);
	return (ray_dir);
}

t_intersection	find_closest_intersection(t_minirt *minirt, t_vec3 ray_start, t_object *ignore, t_vec3 ray_dir)
{
	t_intersection	closest_isect;
	t_intersection	isect;
	t_object		*obj;

	obj = minirt->world.objects;
	closest_isect = (t_intersection){0, INFINITY, {0, 0, 0}, {0, 0, 0}};
	while (obj)
	{
		if (obj == ignore)
		{
			obj = obj->next;
			continue ;
		}
		isect = obj->f_intersect(obj, ray_start, ray_dir);
		isect.obj = obj;
		if (isnan(isect.pos.x) || isnan(isect.pos.y) || isnan(isect.pos.z))
		{
			obj = obj->next;
			continue ;
		}
		isect.t = vec3_mag(vec3_sub(isect.pos, ray_start));
		if (isect.t < closest_isect.t && isfinite(isect.t))
			closest_isect = isect;
		obj = obj->next;
	}
	return (closest_isect);
}

int	is_illuminated(t_minirt *mrt, t_intersection isect, t_light light)
{
	t_vec3			dir;
	double			dist;
	double			angle;
	t_intersection	obstructed;

	dir = vec3_sub(light.pos, isect.pos);
	dist = vec3_mag(dir);
	dir = vec3_normalize(dir);
	angle = vec3_dot(isect.normal, dir);
	if (angle > 0.0f)
	{
		obstructed = find_closest_intersection(mrt, isect.pos, isect.obj, dir);
		if (!obstructed.obj || vec3_mag(vec3_sub(obstructed.pos, isect.pos)) > dist)
			return (1);
	}
	return (0);
}

#define MAX_DEPTH 5
#define MAT_REFLECTIVE .0f
#define MAT_TRANSPARENCY .0f
#define MAT_IOR .4f
#define SHININESS 32

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
			color = color_add(color_scale(color, 1 - MAT_REFLECTIVE), color_scale(refl_color, MAT_REFLECTIVE));
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
	if (SHININESS > 0)
	{
		t_vec3 view_dir = vec3_normalize(vec3_sub(mrt->world.camera.pos, closest_isect.pos));
		t_vec3 halfway_dir = vec3_normalize(vec3_add(light_dir, view_dir));
		double specular = pow(fmax(vec3_dot(closest_isect.normal, halfway_dir), 0.0), SHININESS);
		diffuse = mrt->world.ambient.brightness + diffuse + specular;
	}
	if (diffuse < 0)
		diffuse = -diffuse;
	if (!illuminated)
		return (color_scale(color, mrt->world.ambient.brightness));
	return (color_scale(color, diffuse));
}

void	render_scene(t_minirt *minirt)
{
	t_vec3			ray_start;
	t_color			bg_color;
	t_color			pixel_color;
	t_vec3			ray_dir;
	t_intersection	isect;
	int				y;
	int				x;

	ray_start = minirt->world.camera.pos;
	bg_color = minirt->world.ambient.color;
	y = 0;
	x = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			ray_dir = calculate_ray_direction(minirt, x, y);
			isect = find_closest_intersection(minirt, ray_start, 0, ray_dir);
			if (isect.obj)
				pixel_color = sample_color_at_intersection(minirt, \
					isect, ray_dir, 0);
			else
				pixel_color = bg_color;
			mrt_pixel_put(&minirt->img, x, y, pixel_color);
			x++;
		}
		mlx_put_image_to_window(minirt->ctx, minirt->win, \
			minirt->img.img, 0, 0);
		y++;
	}
	printf("\rRendering: 100%%\n");
	mlx_put_image_to_window(minirt->ctx, minirt->win, minirt->img.img, 0, 0);
	mlx_string_put(minirt->ctx, minirt->win, 10, 20, 0xFFF, "Rendering Done!");
}
