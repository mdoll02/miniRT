/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoll <mdoll@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 11:25:35 by mdoll             #+#    #+#             */
/*   Updated: 2023/05/25 09:49:24 by mdoll            ###   ########.fr       */
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
	t_vec3			inter_cap;
	t_vec3			p1_to_cap;
	t_intersection	inter;
	t_vec3			normal;

	normal = vec3_normalize(cylinder->axis);
	if (is_top)
		cap.pos = vec3_add(cylinder->pos, vec3_mul(normal, \
			cylinder->height * 0.5));
	else
		cap.pos = vec3_sub(cylinder->pos, vec3_mul(normal, \
			cylinder->height * 0.5));
	cap.normal = normal;
	inter = plane_intersect(&cap, pos, dir);
	inter_cap = inter.pos;
	if (isnan(inter_cap.x) || isnan(inter_cap.y) || isnan(inter_cap.z))
		return ((t_vec3){INFINITY, INFINITY, INFINITY});
	else
	{
		p1_to_cap = vec3_sub(inter_cap, cap.pos);
		if (vec3_mag(p1_to_cap) < cylinder->diameter / 2)
			return (inter_cap);
	}
	return ((t_vec3){INFINITY, INFINITY, INFINITY});
}

static t_distance	get_distance(t_cylinder *cylinder, t_vec3 pos, t_vec3 dir)
{
	t_isec_values	iv;
	t_distance		dist;
	double			radius;
	t_vec3			normal;

	radius = (double)cylinder->diameter / 2;
	normal = vec3_normalize(cylinder->axis);
	iv.oc = vec3_sub(pos, cylinder->pos);
	iv.a = vec3_dot(dir, dir) - pow(vec3_dot(dir, normal), 2);
	iv.b = 2 * (vec3_dot(dir, iv.oc) - vec3_dot(dir, normal) * \
		vec3_dot(iv.oc, normal));
	iv.c = vec3_dot(iv.oc, iv.oc) - pow(vec3_dot(iv.oc, normal), 2) \
		- pow(radius, 2);
	iv.discr = pow(iv.b, 2) - 4 * iv.a * iv.c;
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
