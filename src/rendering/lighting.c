/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoll <mdoll@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 14:00:13 by mdoll             #+#    #+#             */
/*   Updated: 2023/05/29 10:46:57 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "rendering.h"
#include "vec_math.h"
#include "color_math.h"

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
		if (!obstructed.obj || vec3_mag(vec3_sub(obstructed.pos,
					isect.pos)) > dist)
			return (1);
	}
	return (0);
}

double	specular_lighting(t_minirt *mrt, t_intersection closest_isect,
							t_vec3 light_dir)
{
	t_vec3	view_dir;
	t_vec3	halfway_dir;
	double	specular;

	view_dir = vec3_normalize(vec3_sub(mrt->world.camera.pos,
				closest_isect.pos));
	halfway_dir = vec3_normalize(vec3_add(light_dir, view_dir));
	specular = pow(fmax(vec3_dot(closest_isect.normal, halfway_dir), 0.0),
			32);
	return (specular);
}

t_color	get_reflection(t_vec3 ray_dir, t_minirt *mrt,
	t_intersection closest_isect, int depth)
{
	t_vec3			refl_dir;
	t_color			refl_color;
	t_intersection	isect;

	refl_dir = vec3_reflect(ray_dir, closest_isect.normal);
	isect = find_closest_intersection(mrt, closest_isect.pos,
			closest_isect.obj, refl_dir);
	if (isect.obj)
	{
		refl_color = sample_color_at_intersection(mrt, isect,
				refl_dir, depth + 1);
		return (color_scale(refl_color, MAT_REFLECTIVE));
	}
	return (color_scale(mrt->world.ambient.color,
			mrt->world.ambient.brightness));
}

t_color	get_transparency(t_vec3 ray_dir, t_minirt *mrt,
		t_intersection closest_isect, int depth)
{
	t_vec3			refr_dir;
	t_color			refr_color;
	t_intersection	isect;

	refr_dir = vec3_refract(ray_dir, closest_isect.normal, MAT_IOR);
	isect = find_closest_intersection(mrt, closest_isect.pos,
			closest_isect.obj, refr_dir);
	if (isect.obj)
	{
		refr_color = sample_color_at_intersection(mrt, isect,
				refr_dir, depth + 1);
		return (color_scale(refr_color, MAT_TRANSPARENCY));
	}
	return (color_scale(mrt->world.ambient.color, MAT_TRANSPARENCY));
}
