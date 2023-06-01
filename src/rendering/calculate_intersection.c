/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_intersection.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoll <mdoll@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:15:25 by mdoll             #+#    #+#             */
/*   Updated: 2023/06/01 21:42:25 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <float.h>
#include "rendering.h"
#include "vec_math.h"
#include "color_math.h"

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
			if (isect.t < closest_isect.t && isfinite(isect.t)
				&& isect.t > FLT_EPSILON * 2)
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
	double			ambient;

	color = (t_color){0, 0, 0};
	if (depth >= MAX_DEPTH)
		return (color);
	object_color = c_isect.obj->f_sample_color(c_isect.obj, c_isect.pos);
	if (MAT_REFLECTIVE > 0.0f)
		color = color_add(color, get_reflection(ray_dir, mrt, c_isect, depth));
	if (MAT_TRANSPARENCY > 0.0f)
		color = color_add(color, get_transparency(ray_dir, mrt, \
					c_isect, depth));
	illuminated = is_illuminated(mrt, c_isect, mrt->world.light);
	light_dir = vec3_normalize(vec3_sub(mrt->world.light.pos, c_isect.pos));
	diffuse = 1 - vec3_mag(vec3_mul(vec3_sub(mrt->world.light.pos, c_isect.pos), 0.002));
	if (MAT_REFLECTIVE > 0 && illuminated)
		diffuse += specular_lighting(mrt, c_isect, light_dir);
	if (!illuminated)
		diffuse = 0;
	diffuse *= mrt->world.light.brightness;
	ambient = mrt->world.ambient.brightness;
	ambient = fmax(0, fmin(ambient, 1.0f));
	color = color_add(color, color_scale(object_color, diffuse));
	color = color_add(color, color_scale(object_color, ambient));
	//color = color_add(color, color_scale(mrt->world.ambient.color, mrt->world.ambient.brightness));
	return (color);
}
