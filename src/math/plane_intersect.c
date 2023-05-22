/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_intersect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 23:22:22 by kschmidt          #+#    #+#             */
/*   Updated: 2023/05/10 09:33:26 by mdoll            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <float.h>
#include "rendering.h"
#include "vec_math.h"

t_intersection	plane_intersect(t_plane *plane, t_vec3 pos, t_vec3 dir)
{
	double			denom;
	double			t;
	t_intersection	intersection;

	denom = vec3_dot(plane->normal, dir);
	if (fabs(denom) < DBL_EPSILON)
	{
		intersection.pos = vec3_init(NAN, NAN, NAN);
		return (intersection);
	}
	t = vec3_dot(vec3_sub(plane->pos, pos), plane->normal) / denom;
	if (t < 0)
	{
		intersection.pos = vec3_init(NAN, NAN, NAN);
		return (intersection);
	}
	intersection.pos = vec3_add(pos, vec3_mul(dir, t));
	intersection.normal = plane->normal;
	return (intersection);
}

t_vec3	plane_normal(t_plane *plane, t_vec3 pos)
{
	(void)pos;
	return (plane->normal);
}

t_color	plane_sample_color(t_plane *plane, t_vec3 pos)
{
	(void)pos;
	return (plane->color);
}
