/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_math.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 20:49:19 by kschmidt          #+#    #+#             */
/*   Updated: 2023/05/29 10:24:15 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC_MATH_H
# define VEC_MATH_H

# include "definitions.h"

# define M_PI 3.14159265358979323846

t_vec3	vec3_init(double x, double y, double z);
t_vec3	vec3_add(t_vec3 a, t_vec3 b);
t_vec3	vec3_sub(t_vec3 a, t_vec3 b);
t_vec3	vec3_mul(t_vec3 a, double scalar);
t_vec3	vec3_normalize(t_vec3 vec);
double	vec3_mag(t_vec3 vec);
double	vec3_dot(t_vec3 a, t_vec3 b);
t_vec3	vec3_reflect(t_vec3 dir, t_vec3 normal);
t_vec3	vec3_refract(t_vec3 dir, t_vec3 normal, double eta);
t_vec3	vec3_neg(t_vec3 vec);
t_vec3	vec3_cross(t_vec3 a, t_vec3 b);

#endif //VEC_MATH_H
