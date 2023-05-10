/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_intersect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 21:28:48 by kschmidt          #+#    #+#             */
/*   Updated: 2023/05/10 09:38:51 by mdoll            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "rendering.h"
#include "vec_math.h"

t_intersection	sphere_intersect(t_sphere *sphere, t_vec3 pos, t_vec3 dir)
{
	t_intersection	intersection;
	double radius = sphere->diameter / 2;
	t_vec3 oc = vec3_sub(pos, sphere->pos);
	double a = vec3_dot(dir, dir);
	double b = 2 * vec3_dot(oc, dir);
	double c = vec3_dot(oc, oc) - radius * radius;
	double discriminant = b * b - 4 * a * c;

	if (discriminant < 0)
	{
		intersection.pos = vec3_init(NAN, NAN, NAN);
		return (intersection);
	}
	double t = (-b - sqrt(discriminant)) / (2 * a);
	if (t < 0)
		t = (-b + sqrt(discriminant)) / (2 * a);
	if (t < 0)
	{
		intersection.pos = vec3_init(NAN, NAN, NAN);
		return (intersection);
	}
	intersection.pos = vec3_add(pos, vec3_mul(dir, t));
	intersection.normal = sphere_normal(sphere, intersection.pos);
	return (intersection);
}

t_vec3	sphere_normal(t_sphere *sphere, t_vec3 pos)
{
	return (vec3_normalize(vec3_sub(pos, sphere->pos)));
}

t_color	sphere_sample_color(t_sphere *sphere, t_vec3 pos)
{
	(void)pos;
	return (sphere->color);
}
