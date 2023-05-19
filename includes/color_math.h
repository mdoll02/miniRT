/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_math.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:51:48 by kschmidt          #+#    #+#             */
/*   Updated: 2023/05/19 10:31:31 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_COLOR_MATH_H
#define MINIRT_COLOR_MATH_H

#include "definitions.h"

t_color color_limit(t_color color);
t_color	color_add(t_color a, t_color b);
t_color color_scale(t_color color, double scalar);
t_color color_waverage(t_color *cols, int size);

#endif //MINIRT_COLOR_MATH_H
