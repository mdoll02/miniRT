/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_math.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:51:48 by kschmidt          #+#    #+#             */
/*   Updated: 2023/05/04 21:50:08 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_COLOR_MATH_H
#define MINIRT_COLOR_MATH_H

#include "definitions.h"

t_color color_limit(t_color color);
t_color	color_add(t_color a, t_color b);
t_color color_scale(t_color color, double scalar);

#endif //MINIRT_COLOR_MATH_H
