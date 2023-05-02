/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_intersect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 21:28:48 by kschmidt          #+#    #+#             */
/*   Updated: 2023/05/02 22:24:58 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "rendering.h"
#include "vec_math.h"

t_vec3	sphere_intersect(t_sphere *sphere, t_vec3 pos, t_vec3 dir)
{
	t_vec3 oc = vec3_sub(pos, sphere->pos);
	float a = vec3_dot(dir, dir);
	float b = 2 * vec3_dot(oc, dir);
	float c = vec3_dot(oc, oc) - sphere->radius * sphere->radius;
	float discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return vec3_init(NAN, NAN, NAN);
	float t = (-b - sqrtf(discriminant)) / (2 * a);
	if (t < 0)
		t = (-b + sqrtf(discriminant)) / (2 * a);
	if (t < 0)
		return vec3_init(NAN, NAN, NAN);
	return vec3_add(pos, vec3_mul(dir, t));
}

t_color	sphere_sample_color(t_sphere *sphere, t_vec3 pos)
{
	(void)pos;
	return (sphere->color);
}
