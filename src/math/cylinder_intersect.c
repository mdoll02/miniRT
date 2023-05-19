/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 23:06:28 by kschmidt          #+#    #+#             */
/*   Updated: 2023/05/19 09:11:33 by mdoll            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "rendering.h"
#include "vec_math.h"
#include <stdio.h>

t_vec3	top_intersect(t_cylinder *cylinder, t_vec3 pos, t_vec3 dir)
{
	t_plane			top;
	t_vec3			inter_top;
	t_vec3			p1_to_top;
	t_intersection	inter;

	top.pos = vec3_add(cylinder->pos, vec3_mul(cylinder->axis, cylinder->height * 0.5));
	top.normal = cylinder->axis;
	inter = plane_intersect(&top, pos, dir);
	inter_top = inter.pos;
	if (isnan(inter_top.x) || isnan(inter_top.y) || isnan(inter_top.z))
		return ((t_vec3){INFINITY, INFINITY, INFINITY});
	else
	{
		p1_to_top = vec3_sub(inter_top, top.pos);
		if (vec3_mag(p1_to_top) < cylinder->diameter / 2)
			return (inter_top);
	}
	return ((t_vec3){INFINITY, INFINITY, INFINITY});
}

t_vec3	bottom_intersect(t_cylinder *cylinder, t_vec3 pos, t_vec3 dir)
{
	t_plane			bot;
	t_vec3			inter_bot;
	t_vec3			p1_to_bot;
	t_intersection	inter;

	bot.pos = vec3_sub(cylinder->pos, vec3_mul(cylinder->axis, cylinder->height * 0.5));
	bot.normal = cylinder->axis;
	inter = plane_intersect(&bot, pos, dir);
	inter_bot = inter.pos;
	if (isnan(inter_bot.x) || isnan(inter_bot.y) || isnan(inter_bot.z))
		return ((t_vec3){INFINITY, INFINITY, INFINITY});
	else
	{
		p1_to_bot = vec3_sub(inter_bot, bot.pos);
		if (vec3_mag(p1_to_bot) < cylinder->diameter / 2)
			return (inter_bot);
	}
	return ((t_vec3){INFINITY, INFINITY, INFINITY});
}

t_intersection cylinder_intersect(t_cylinder *cylinder, t_vec3 pos, t_vec3 dir)
{
	t_vec3	oc;
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	t1;
	double	t2;
	t_vec3	p1;
	t_vec3	p2;
	double	h;
	double	proj1;
	double	proj2;
	t_vec3	inter_top;
	t_vec3	inter_bot;
	double	t;
	t_vec3	intersection_pos;
	t_vec3	normal;

	oc = vec3_sub(pos, cylinder->pos);
	a = vec3_dot(dir, dir) - pow(vec3_dot(dir, cylinder->axis), 2);
	b = 2 * (vec3_dot(dir, oc) - vec3_dot(dir, cylinder->axis) * vec3_dot(oc, cylinder->axis));
	c = vec3_dot(oc, oc) - pow(vec3_dot(oc, cylinder->axis), 2) - pow(cylinder->diameter / 2, 2);
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return ((t_intersection){.pos = vec3_init(INFINITY, INFINITY, INFINITY)});
	t1 = (-b + sqrt(discriminant)) / (2 * a);
	t2 = (-b - sqrt(discriminant)) / (2 * a);
	p1 = vec3_add(pos, vec3_mul(dir, t1));
	p2 = vec3_add(pos, vec3_mul(dir, t2));
	h = cylinder->height * 0.5;
	proj1 = vec3_dot(vec3_sub(p1, cylinder->pos), cylinder->axis);
	proj2 = vec3_dot(vec3_sub(p2, cylinder->pos), cylinder->axis);
	if (proj1 < -h || proj1 > h)
		t1 = INFINITY;
	if (proj2 < -h || proj2 > h)
		t2 = INFINITY;
	inter_top = top_intersect(cylinder, pos, dir);
	inter_bot = bottom_intersect(cylinder, pos, dir);
	if (t1 < t2)
		t = t1;
	else
		t = t2;
	if (t < 0)
	{
		if (t1 > t2)
			t = t1;
		else
			t = t2;
	}
	if (inter_top.x != INFINITY)
	{
		if (vec3_mag(vec3_sub(inter_top, pos)) < t)
			return ((t_intersection){.pos = inter_top, .normal = cylinder->axis});
	}
	if (inter_bot.x != INFINITY)
	{
		if (vec3_mag(vec3_sub(inter_bot, pos)) < t)
			return ((t_intersection){.pos = inter_bot, .normal = vec3_neg(cylinder->axis)});
	}
	if (t < 0)
		return ((t_intersection){.pos = vec3_init(INFINITY, INFINITY, INFINITY)});
	intersection_pos = vec3_add(pos, vec3_mul(dir, t));
	normal = cylinder_normal(cylinder, intersection_pos);
	return ((t_intersection){.pos = vec3_add(pos, vec3_mul(dir, t)), .normal = normal});
}

t_vec3	cylinder_normal(t_cylinder *cyl, t_vec3 pos)
{
	t_vec3	axis;
	t_vec3	to_pos;
	double	proj_len;
	t_vec3	proj_vec;
	t_vec3	normal;

	axis = vec3_normalize(cyl->axis);
	to_pos = vec3_sub(pos, cyl->pos);
	proj_len = vec3_dot(to_pos, axis);
	proj_vec = vec3_add(cyl->pos, vec3_mul(axis, proj_len));
	normal = vec3_normalize(vec3_sub(pos, proj_vec));
	return (normal);
}


t_color	cylinder_sample_color(t_cylinder *cyl, t_vec3 pos)
{
	(void)pos;
	return (cyl->color);
}
