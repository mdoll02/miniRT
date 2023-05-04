/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:52:15 by kschmidt          #+#    #+#             */
/*   Updated: 2023/05/04 21:49:57 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "color_math.h"

t_color color_limit(t_color color)
{
	return ((t_color){fmax(fmin(color.r, 255), 0),
					  fmax(fmin(color.g, 255), 0),
					  fmax(fmin(color.b, 255), 0)});
}

t_color	color_add(t_color a, t_color b)
{
	return (color_limit((t_color){a.r + b.r, a.g + b.g, a.b + b.b}));
}

t_color color_scale(t_color color, double scaler)
{
	return (color_limit((t_color){color.r * scaler,
					  color.g * scaler,
					  color.b * scaler}));
}