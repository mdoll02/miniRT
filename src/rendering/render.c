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
#include "rendering.h"
#include "mlx/mlx.h"
#include "vec_math.h"
#include "color_math.h"

static void	mrt_pixel_put(t_mlx_image *img, int x, int y, t_color color)
{
	char	*dst;

	dst = img->addr + ((HEIGHT - 1 - y) * img->line_length + \
										x * (img->bbp / 8));
	*(unsigned int *)dst = color_to_int(color);
}

t_intersection	find_closest_intersection(t_minirt *minirt, t_vec3 ray_start,
			t_object *ignore, t_vec3 ray_dir)
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
		if (!isnan(isect.pos.x) && !isnan(isect.pos.y) && !isnan(isect.pos.z))
		{
			isect.t = vec3_mag(vec3_sub(isect.pos, ray_start));
			if (isect.t < closest_isect.t && isfinite(isect.t))
				closest_isect = isect;
		}
		obj = obj->next;
	}
	return (closest_isect);
}

t_color	sample_color_at_intersection(t_minirt *mrt, t_intersection c_isect
, t_vec3 ray_dir, int depth)
{
	t_color			color;
	t_color			object_color;
	int				illuminated;
	t_vec3			light_dir;
	double			diffuse;

	color = (t_color){0, 0, 0};
	if (depth >= MAX_DEPTH)
		return (color);
	object_color = c_isect.obj->f_sample_color(c_isect.obj, c_isect.pos);
	if (MAT_REFLECTIVE > 0.0f)
		color = color_add(color, get_reflection(ray_dir, mrt, c_isect, depth));
	if (MAT_TRANSPARENCY > 0.0f)
		color = color_add(color, get_transparency(ray_dir, mrt,
					c_isect, depth));
	illuminated = is_illuminated(mrt, c_isect, mrt->world.light);
	light_dir = vec3_normalize(vec3_sub(mrt->world.light.pos, c_isect.pos));
	diffuse = vec3_dot(c_isect.normal, light_dir);
	diffuse = fmax(diffuse, 0.0f);
	if (MAT_REFLECTIVE > 0 && illuminated)
		diffuse += specular_lighting(mrt, c_isect, light_dir);
	if (illuminated)
		return (color_add(color, color_scale(object_color, diffuse)));
	return (color_add(color, color_scale(object_color,
				mrt->world.ambient.brightness)));
}

void	render_scene(t_minirt *minirt)
{
	t_vec3			ray_start;
	t_color			pixel_color;
	t_vec3			ray_dir;
	t_intersection	isect;
	t_coordinates	coords;

	ray_start = minirt->world.camera.pos;
	coords.y = HEIGHT;
	while (coords.y-- >= 0)
	{
		coords.x = 0;
		while (coords.x < WIDTH)
		{
			ray_dir = calculate_ray_direction(minirt, coords.x, coords.y);
			isect = find_closest_intersection(minirt, ray_start, 0, ray_dir);
			if (isect.obj)
				pixel_color = sample_color_at_intersection(minirt, \
					isect, ray_dir, 0);
			else
				pixel_color = minirt->world.ambient.color;
			mrt_pixel_put(&minirt->img, coords.x, coords.y, pixel_color);
			coords.x++;
		}
	}
	mlx_put_image_to_window(minirt->ctx, minirt->win, minirt->img.img, 0, 0);
}

// TODO move all struct into header file