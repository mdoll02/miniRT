/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoll <mdoll@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 11:25:35 by mdoll             #+#    #+#             */
/*   Updated: 2023/05/28 16:51:05 by kschmidt         ###   ########.fr       */
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

static t_distance	get_distance(t_cylinder *cylinder, t_vec3 pos, t_vec3 dir)
{
	t_isec_values	iv;
	t_distance		dist;
	double			radius;
	t_vec3			normal;
	double			normaldot;
	double			ocdot;

	radius = cylinder->diameter / 2.0;
	normal = vec3_normalize(cylinder->axis);
	iv.oc = vec3_sub(pos, cylinder->pos);
	normaldot = vec3_dot(dir, normal);
	ocdot = vec3_dot(iv.oc, normal);
	iv.a = vec3_dot(dir, dir) - (normaldot * normaldot);
	iv.b = 2 * (vec3_dot(dir, iv.oc) - normaldot * ocdot);
	iv.c = vec3_dot(iv.oc, iv.oc) - (ocdot * ocdot) - (radius * radius);
	iv.discr = (iv.b * iv.b) - 4 * iv.a * iv.c;
	if (iv.discr < 0)
		return ((t_distance){NAN, NAN});
	dist.t1 = (-iv.b + sqrt(iv.discr)) / (2 * iv.a);
	dist.t2 = (-iv.b - sqrt(iv.discr)) / (2 * iv.a);
	return (dist);
}

static t_proj_len	get_projection_length(t_cylinder *cylinder, t_vec3 pos, \
												t_vec3 dir, t_distance dist)
{
	t_vec3			p1;
	t_vec3			p2;
	t_proj_len		proj_len;
	t_vec3			normal;

	normal = vec3_normalize(cylinder->axis);
	p1 = vec3_add(pos, vec3_mul(dir, dist.t1));
	p2 = vec3_add(pos, vec3_mul(dir, dist.t2));
	proj_len.proj1 = vec3_dot(vec3_sub(p1, cylinder->pos), normal);
	proj_len.proj2 = vec3_dot(vec3_sub(p2, cylinder->pos), normal);
	return (proj_len);
}

double	cylinder_side_intersect(t_cylinder *cylinder, t_vec3 pos, t_vec3 dir)
{
	t_distance		dist;
	t_proj_len		proj_len;
	double			h;
	double			t;

	dist = get_distance(cylinder, pos, dir);
	if (isnan(dist.t1) || isnan(dist.t2))
		return (NAN);
	h = cylinder->height * 0.5;
	proj_len = get_projection_length(cylinder, pos, dir, dist);
	if (proj_len.proj1 < -h || proj_len.proj1 > h)
		dist.t1 = INFINITY;
	if (proj_len.proj2 < -h || proj_len.proj2 > h)
		dist.t2 = INFINITY;
	t = dist.t2;
	if (dist.t1 < dist.t2)
		t = dist.t1;
	if (t < 0)
	{
		if (dist.t1 > dist.t2)
			t = dist.t1;
		else
			t = dist.t2;
	}
	return (t);
}
