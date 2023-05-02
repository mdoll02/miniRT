/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 21:22:52 by kschmidt          #+#    #+#             */
/*   Updated: 2023/05/02 21:30:26 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec_math.h"

t_vec3	vec3_init(float x, float y, float z)
{
	return ((t_vec3){x, y, z});
}

float	vec3_dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}