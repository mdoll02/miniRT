/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_math.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 20:49:19 by kschmidt          #+#    #+#             */
/*   Updated: 2023/05/02 21:40:42 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC_MATH_H
# define VEC_MATH_H

# include "definitions.h"

t_vec3	vec3_init(float x, float y, float z);
t_vec3	vec3_add(t_vec3 a, t_vec3 b);
t_vec3	vec3_sub(t_vec3 a, t_vec3 b);
t_vec3	vec3_mul(t_vec3 a, float scalar);
t_vec3	vec3_normalize(t_vec3 vec);
float	vec3_mag(t_vec3 vec);
float	vec3_dot(t_vec3 a, t_vec3 b);

#endif //VEC_MATH_H
