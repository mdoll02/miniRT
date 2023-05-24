/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_intersection.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoll <mdoll@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:15:25 by mdoll             #+#    #+#             */
/*   Updated: 2023/05/23 14:15:28 by mdoll            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
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
		color = color_add(color, get_transparency(ray_dir, mrt, \
					c_isect, depth));
	illuminated = is_illuminated(mrt, c_isect, mrt->world.light);
	light_dir = vec3_normalize(vec3_sub(mrt->world.light.pos, c_isect.pos));
	diffuse = vec3_dot(c_isect.normal, light_dir);
	diffuse = fmax(diffuse, 0.0f);
	if (MAT_REFLECTIVE > 0 && illuminated)
		diffuse += specular_lighting(mrt, c_isect, light_dir);
	if (illuminated)
		return (color_scale(color_add(color, color_scale(object_color, diffuse)), mrt->world.light.brightness));
	return (color_add(color, color_scale(object_color, \
						mrt->world.ambient.brightness)));
}
