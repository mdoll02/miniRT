/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoll <mdoll@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 11:25:35 by mdoll             #+#    #+#             */
/*   Updated: 2023/06/02 12:36:46 by mdoll            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdbool.h>
#include "rendering.h"
#include "vec_math.h"

t_vec3	cylinder_cap_intersect(t_cylinder *cylinder, t_vec3 pos, t_vec3 dir, \
														bool is_top)
{
	t_plane			cap;
	t_vec3			p1_to_cap;
	t_intersection	inter;
	t_vec3			normal;

	normal = vec3_normalize(cylinder->axis);
	if (is_top)
	{
		cap.pos = vec3_add(cylinder->pos, vec3_mul(normal, \
			cylinder->height * 0.5));
		cap.normal = cylinder->axis;
	}
	else
	{
		cap.pos = vec3_sub(cylinder->pos, vec3_mul(normal, \
			cylinder->height * 0.5));
		cap.normal = vec3_neg(cylinder->axis);
	}
	inter = plane_intersect(&cap, pos, dir);
	if (isnan(inter.pos.x) || isnan(inter.pos.y) || isnan(inter.pos.z))
		return ((t_vec3){INFINITY, INFINITY, INFINITY});
	p1_to_cap = vec3_sub(inter.pos, cap.pos);
	if (vec3_mag(p1_to_cap) < cylinder->diameter / 2)
		return (inter.pos);
	return ((t_vec3){INFINITY, INFINITY, INFINITY});
}

inline static t_double_values	get_distance(t_cylinder *cylinder,
	t_vec3 pos, t_vec3 dir)
{
	t_isec_values	iv;
	t_double_values	dist;
	double			radius;
	t_vec3			normal;
	t_double_values	dot;

	radius = cylinder->diameter / 2.0;
	normal = vec3_normalize(cylinder->axis);
	iv.oc = vec3_sub(pos, cylinder->pos);
	dot.d2 = vec3_dot(dir, normal);
	dot.d1 = vec3_dot(iv.oc, normal);
	iv.a = vec3_dot(dir, dir) - (dot.d2 * dot.d2);
	iv.b = 2 * (vec3_dot(dir, iv.oc) - dot.d2 * dot.d1);
	iv.c = vec3_dot(iv.oc, iv.oc) - (dot.d1 * dot.d1) - (radius * radius);
	iv.discr = (iv.b * iv.b) - 4 * iv.a * iv.c;
	if (iv.discr < 0)
		return ((t_double_values){NAN, NAN});
	iv.discr = sqrt(iv.discr);
	dist.d1 = (-iv.b + iv.discr) / (2 * iv.a);
	dist.d2 = (-iv.b - iv.discr) / (2 * iv.a);
	return (dist);
}

inline static t_double_values	get_projection_length(t_cylinder *cylinder,
		t_vec3 pos, t_vec3 dir, t_double_values dist)
{
	t_vec3			p1;
	t_vec3			p2;
	t_double_values	proj_len;
	t_vec3			normal;

	normal = vec3_normalize(cylinder->axis);
	p1 = vec3_add(pos, vec3_mul(dir, dist.d1));
	p2 = vec3_add(pos, vec3_mul(dir, dist.d2));
	proj_len.d1 = vec3_dot(vec3_sub(p1, cylinder->pos), normal);
	proj_len.d2 = vec3_dot(vec3_sub(p2, cylinder->pos), normal);
	return (proj_len);
}

double	cylinder_side_intersect(t_cylinder *cylinder, t_vec3 pos, t_vec3 dir)
{
	t_double_values		dist;
	t_double_values		proj_len;
	double				h;
	double				t;

	dist = get_distance(cylinder, pos, dir);
	if (isnan(dist.d1) || isnan(dist.d2))
		return (NAN);
	h = cylinder->height * 0.5;
	proj_len = get_projection_length(cylinder, pos, dir, dist);
	if (proj_len.d1 < -h || proj_len.d1 > h)
		dist.d1 = INFINITY;
	if (proj_len.d2 < -h || proj_len.d2 > h)
		dist.d2 = INFINITY;
	t = dist.d2;
	if (dist.d1 < dist.d2)
		t = dist.d1;
	if (t < 0)
	{
		if (dist.d1 > dist.d2)
			t = dist.d1;
		else
			t = dist.d2;
	}
	return (t);
}
