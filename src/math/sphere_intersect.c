/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_intersect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 21:28:48 by kschmidt          #+#    #+#             */
/*   Updated: 2023/05/22 10:18:07 by mdoll            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "rendering.h"
#include "vec_math.h"

t_intersection	sphere_intersect(t_sphere *sphere, t_vec3 pos, t_vec3 dir)
{
	t_intersection	intersection;
	t_isec_values	iv;
	double			radius;
	double			t;

	radius = sphere->diameter / 2;
	iv.oc = vec3_sub(pos, sphere->pos);
	iv.b = 2 * vec3_dot(iv.oc, dir);
	iv.a = vec3_dot(dir, dir);
	iv.c = vec3_dot(iv.oc, iv.oc) - radius * radius;
	iv.discr = iv.b * iv.b - 4 * iv.a * iv.c;
	if (iv.discr < 0)
		return ((t_intersection){.pos = vec3_init(NAN, NAN, NAN)});
	t = (-iv.b - sqrt(iv.discr)) / (2 * iv.a);
	if (t < 0)
		t = (-iv.b + sqrt(iv.discr)) / (2 * iv.a);
	if (t < 0)
		return ((t_intersection){.pos = vec3_init(NAN, NAN, NAN)});
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
