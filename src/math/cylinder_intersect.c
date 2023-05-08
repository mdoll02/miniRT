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

t_vec3 cylinder_intersect(t_cylinder *cylinder, t_vec3 pos, t_vec3 dir)
{
	t_vec3 oc = vec3_sub(pos, cylinder->pos);

	double a = vec3_dot(dir, dir) - pow(vec3_dot(dir, cylinder->axis), 2);
	double b = 2 * (vec3_dot(dir, oc) - vec3_dot(dir, cylinder->axis) * vec3_dot(oc, cylinder->axis));
	double c = vec3_dot(oc, oc) - pow(vec3_dot(oc, cylinder->axis), 2) - pow(cylinder->diameter / 2, 2);

	double discr = b * b - 4 * a * c;

	if (discr < 0)
		return (t_vec3){INFINITY, INFINITY, INFINITY};

	double t1 = (-b + sqrt(discr)) / (2 * a);
	double t2 = (-b - sqrt(discr)) / (2 * a);

	if (t1 > t2)
	{
		double temp = t1;
		t1 = t2;
		t2 = temp;
	}

	t_vec3 point = vec3_add(pos, vec3_mul(dir, t1));
	t_vec3 p1_to_p = vec3_sub(point, cylinder->pos);
	double proj_len = vec3_dot(p1_to_p, cylinder->axis) + cylinder->height * 0.5;
	if (proj_len < -cylinder->height / 2 || proj_len > cylinder->height / 2)
		return (t_vec3){INFINITY, INFINITY, INFINITY};
	return point;
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
