/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 21:22:52 by kschmidt          #+#    #+#             */
/*   Updated: 2023/05/04 12:30:27 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "vec_math.h"

t_vec3	vec3_init(float x, float y, float z)
{
	return ((t_vec3){x, y, z});
}

float	vec3_dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec3	vec3_reflect(t_vec3 vec, t_vec3 normal)
{
	return (vec3_sub(vec, vec3_mul(normal, 2 * vec3_dot(vec, normal))));
}

t_vec3	vec3_refract(t_vec3 vec, t_vec3 normal, float eta)
{
	float	cos_theta;
	t_vec3	vec_perp;
	t_vec3	vec_para;

	cos_theta = fminf(vec3_dot(vec3_mul(vec, -1), normal), 1.0);
	vec_perp = vec3_mul(vec3_add(vec, vec3_mul(normal, cos_theta)), eta);
	vec_para = vec3_mul(normal, -sqrtf(fabsf(1.0f - vec3_mag(vec_perp))));
	return (vec3_add(vec_perp, vec_para));
}

t_vec3	vec3_neg(t_vec3 vec)
{
	return ((t_vec3){-vec.x, -vec.y, -vec.z});
}