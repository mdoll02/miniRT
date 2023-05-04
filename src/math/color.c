/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:52:15 by kschmidt          #+#    #+#             */
/*   Updated: 2023/05/04 12:54:31 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color_math.h"

t_color	color_add(t_color a, t_color b)
{
	return ((t_color){a.r + b.r, a.g + b.g, a.b + b.b});
}

t_color color_scale(t_color color, double scaler)
{
	return ((t_color){color.r * scaler,
					  color.g * scaler,
					  color.b * scaler});
}