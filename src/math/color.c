/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:52:15 by kschmidt          #+#    #+#             */
/*   Updated: 2023/05/19 11:08:02 by kschmidt         ###   ########.fr       */
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

t_color color_waverage(t_color *cols, int size)
{
	t_color avg;
	int i;

	avg = (t_color){0, 0, 0};
	i = 0;
	while (i < size)
	{
		avg.r += cols[i].r;
		avg.g += cols[i].g;
		avg.b += cols[i].b;
		i++;
	}
	return (color_scale(avg, 1.0 / size));
}