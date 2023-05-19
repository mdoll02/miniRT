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
	t_vec3	camera_dir;
	t_vec3	camera_right;
	t_vec3	camera_up;
	t_vec3	ray_dir;
	t_vec3	transformed_dir;

	u = (double)x / WIDTH;
	v = (double)y / HEIGHT;
	fov_radians = minirt->world.camera.fov * M_PI / 180.0;
	camera_dir = vec3_normalize(minirt->world.camera.dir);
	camera_right = vec3_normalize(vec3_cross((t_vec3){0, 1, 0}, camera_dir));
	camera_up = vec3_cross(camera_right, camera_dir);
	ray_dir.x = (2 * u - 1) * tan(fov_radians / 2);
	ray_dir.y = (1 - 2 * v) * tan(fov_radians / 2) * HEIGHT / WIDTH;
	ray_dir.z = -1;
	transformed_dir.x = vec3_dot(ray_dir, camera_right);
	transformed_dir.y = vec3_dot(ray_dir, camera_up);
	transformed_dir.z = vec3_dot(ray_dir, camera_dir);
	return (vec3_normalize(transformed_dir));
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
#define MAT_REFLECTIVE .3f
#define MAT_TRANSPARENCY .0f
#define MAT_IOR .4f

t_color sample_color_at_intersection(t_minirt *mrt, t_intersection closest_isect
									 , t_vec3 ray_dir, int depth)
{
	t_color color = (t_color){0, 0, 0};
	t_color object_color;
	t_intersection isect;

	if (depth >= MAX_DEPTH)
		return color;
	object_color = closest_isect.obj->f_sample_color(closest_isect.obj, closest_isect.pos);
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
		t_vec3 refr_dir = vec3_refract(ray_dir, closest_isect.normal, MAT_IOR);
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
		diffuse = 0;
	if (MAT_REFLECTIVE > 0 && illuminated)
	{
		t_vec3 view_dir = vec3_normalize(vec3_sub(mrt->world.camera.pos, closest_isect.pos));
		t_vec3 halfway_dir = vec3_normalize(vec3_add(light_dir, view_dir));
		double specular = pow(fmax(vec3_dot(closest_isect.normal, halfway_dir), 0.0), MAT_REFLECTIVE * 12);
		diffuse += specular;
	}
	t_color lighting = color_scale(object_color, diffuse);
	if (illuminated)
		return color_add(color, lighting);
	return color_add(color, color_scale(object_color, mrt->world.ambient.brightness));
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
	y = HEIGHT - 1;
	while (y >= 0)
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
		y--;
	}
	mlx_put_image_to_window(minirt->ctx, minirt->win, minirt->img.img, 0, 0);
	mlx_string_put(minirt->ctx, minirt->win, 10, 20, 0xFFF, "Rendering Done!");
}
