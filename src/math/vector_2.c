/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 21:22:52 by kschmidt          #+#    #+#             */
/*   Updated: 2023/05/04 13:28:23 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "vec_math.h"

t_vec3	vec3_init(double x, double y, double z)
{
	return ((t_vec3){x, y, z});
}

double	vec3_dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec3	vec3_reflect(t_vec3 dir, t_vec3 normal)
{
	return (vec3_sub(dir, vec3_mul(normal, 2 * vec3_dot(dir, normal))));
}

t_vec3	vec3_refract(t_vec3 dir, t_vec3 normal, double eta)
{
	double	k;
	double	cos_theta;
	t_vec3	refracted;

	cos_theta = fmin(vec3_dot(vec3_neg(dir), normal), 1.0);
	k = 1.0 - eta * eta * (1.0 - cos_theta * cos_theta);
	if (k < 0.0)
		return (vec3_init(NAN, NAN, NAN));
	refracted = vec3_sub(vec3_mul(dir, eta), vec3_mul(normal, eta * cos_theta + sqrtf(k)));
	return (refracted);
}

t_vec3	vec3_neg(t_vec3 vec)
{
	return ((t_vec3){-vec.x, -vec.y, -vec.z});
}
