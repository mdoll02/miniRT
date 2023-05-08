/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 23:06:28 by kschmidt          #+#    #+#             */
/*   Updated: 2023/05/08 10:45:09 by mdoll            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <math.h>
#include "rendering.h"
#include "vec_math.h"
#include <stdio.h>

t_vec3	top_intersect(t_cylinder *cylinder, t_vec3 pos, t_vec3 dir)
{
	t_plane	top;
	t_vec3	inter_top;
	t_vec3	p1_to_top;

	top.pos = vec3_add(cylinder->pos, vec3_mul(cylinder->axis, cylinder->height * 0.5));
	top.normal = cylinder->axis;
	inter_top = plane_intersect(&top, pos, dir);
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
	t_plane	bot;
	t_vec3	inter_bot;
	t_vec3	p1_to_bot;

	bot.pos = vec3_sub(cylinder->pos, vec3_mul(cylinder->axis, cylinder->height * 0.5));
	bot.normal = cylinder->axis;
	inter_bot = plane_intersect(&bot, pos, dir);
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

t_vec3 cylinder_intersect(t_cylinder *cylinder, t_vec3 pos, t_vec3 dir)
{
	t_vec3	oc;
	double	a;
	double	b;
	double	c;
	double	discr;
	double	t1;
	double	t2;
	double	temp;
	t_vec3	point;
	t_vec3	p1_to_p;
	double	proj_len;
	t_vec3	inter_top;
	t_vec3	inter_bot;

	oc = vec3_sub(pos, cylinder->pos);
	a = vec3_dot(dir, dir) - pow(vec3_dot(dir, cylinder->axis), 2);
	b = 2 * (vec3_dot(dir, oc) - vec3_dot(dir, cylinder->axis) * vec3_dot(oc, cylinder->axis));
	c = vec3_dot(oc, oc) - pow(vec3_dot(oc, cylinder->axis), 2) - pow(cylinder->diameter / 2, 2);
	discr = b * b - 4 * a * c;
	if (discr < 0)
		return ((t_vec3){INFINITY, INFINITY, INFINITY});
	t1 = (-b + sqrt(discr)) / (2 * a);
	t2 = (-b - sqrt(discr)) / (2 * a);
	if (t1 > t2)
	{
		temp = t1;
		t1 = t2;
		t2 = temp;
	}
	point = vec3_add(pos, vec3_mul(dir, t1));
	p1_to_p = vec3_sub(point, cylinder->pos);
	proj_len = vec3_dot(p1_to_p, cylinder->axis) + cylinder->height * 0.5;
	inter_top = top_intersect(cylinder, pos, dir);
	inter_bot = bottom_intersect(cylinder, pos, dir);
	if (proj_len >= 0 && proj_len <= cylinder->height)
		return (point);
	if ((inter_bot.x != INFINITY || inter_bot.y != INFINITY || inter_bot.z != INFINITY) && (inter_top.x != INFINITY || inter_top.y != INFINITY || inter_top.z != INFINITY))
	{
		if (vec3_mag(vec3_sub(inter_bot, pos)) < vec3_mag(vec3_sub(inter_top, pos)))
			return (inter_bot);
		else
			return (inter_top);
	}
	if (inter_top.x != INFINITY || inter_top.y != INFINITY || inter_top.z != INFINITY)
		return (inter_top);
	if (inter_bot.x != INFINITY || inter_bot.y != INFINITY || inter_bot.z != INFINITY)
		return (inter_bot);
	return ((t_vec3){INFINITY, INFINITY, INFINITY});
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
