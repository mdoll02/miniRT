/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 23:06:28 by kschmidt          #+#    #+#             */
/*   Updated: 2023/05/04 12:33:36 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <math.h>
#include "rendering.h"
#include "vec_math.h"

t_vec3 cylinder_intersect(t_cylinder *cylinder, t_vec3 pos, t_vec3 dir)
{
	float a = dir.x * dir.x + dir.z * dir.z;
	float b = 2 * (dir.x * (pos.x - cylinder->pos.x) + dir.z * (pos.z - cylinder->pos.z));
	float c = (pos.x - cylinder->pos.x) * (pos.x - cylinder->pos.x) + (pos.z - cylinder->pos.z) * (pos.z - cylinder->pos.z) - cylinder->radius * cylinder->radius;
	float discriminant = b * b - 4 * a * c;

	if (discriminant < 0)
		return (vec3_init(NAN, NAN, NAN));

	float t1 = (-b - sqrtf(discriminant)) / (2 * a);
	float t2 = (-b + sqrtf(discriminant)) / (2 * a);

	float y1 = pos.y + t1 * dir.y;
	float y2 = pos.y + t2 * dir.y;
	float y = cylinder->pos.y - cylinder->height / 2;

	if (y1 < y || y1 > y + cylinder->height)
		t1 = NAN;

	if (y2 < y || y2 > y + cylinder->height)
		t2 = NAN;

	if (isnan(t1) && isnan(t2))
		return (vec3_init(NAN, NAN, NAN));

	float t = isnan(t1) ? t2 : isnan(t2) ? t1 : fminf(t1, t2);
	return (vec3_add(pos, vec3_mul(dir, t)));
}

t_vec3 cylinder_normal(t_cylinder *cyl, t_vec3 pos)
{
	t_vec3 axis;
	t_vec3 to_pos;
	t_vec3 normal;
	float d;

	axis = vec3_normalize(cyl->axis);
	to_pos = vec3_sub(pos, cyl->pos);
	d = vec3_dot(to_pos, axis);
	if (d < 0 || d > cyl->height)
		return vec3_normalize(to_pos);
	else
	{
		normal = vec3_normalize(vec3_sub(to_pos, vec3_mul(axis, d)));
		if (vec3_dot(normal, to_pos) > 0)
			normal = vec3_neg(normal);
		return normal;
	}
}


t_color	cylinder_sample_color(t_cylinder *cyl, t_vec3 pos)
{
	(void)pos;
	return (cyl->color);
}