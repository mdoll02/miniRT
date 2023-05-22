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
#include <stdbool.h>
#include "rendering.h"
#include "vec_math.h"

t_intersection	cylinder_intersect(t_cylinder *cyl, t_vec3 pos, t_vec3 dir)
{
	t_vec3	i_top;
	t_vec3	i_bot;
	t_vec3	intersection_pos;
	double	t;

	t = cylinder_side_intersect(cyl, pos, dir);
	if (isnan(t))
		return ((t_intersection){.pos = \
							vec3_init(INFINITY, INFINITY, INFINITY)});
	i_top = cylinder_cap_intersect(cyl, pos, dir, true);
	i_bot = cylinder_cap_intersect(cyl, pos, dir, false);
	if ((i_top.x != INFINITY || i_top.y != INFINITY || i_top.z != INFINITY) \
							&& (vec3_mag(vec3_sub(i_top, pos)) < t))
		return ((t_intersection){.pos = i_top, .normal = cyl->axis});
	if ((i_bot.x != INFINITY || i_bot.y != INFINITY || i_bot.z != INFINITY) \
							&& vec3_mag(vec3_sub(i_bot, pos)) < t)
		return ((t_intersection){.pos = i_bot, .normal = vec3_neg(cyl->axis)});
	if (t < 0)
		return ((t_intersection){.pos = \
									vec3_init(INFINITY, INFINITY, INFINITY)});
	intersection_pos = vec3_add(pos, vec3_mul(dir, t));
	return ((t_intersection){.pos = vec3_add(pos, vec3_mul(dir, t)), \
							.normal = cylinder_normal(cyl, intersection_pos)});
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
