/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerboard_sample.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 23:27:04 by kschmidt          #+#    #+#             */
/*   Updated: 2023/05/02 23:27:04 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

t_color	checkerboard_color(t_object *obj, t_vec3 pos)
{
	t_color	check;

	(void)obj;
	check.r = (float)((int)(pos.x + 1000) % 2);
	check.g = (float)((int)(pos.y + 1000) % 2);
	check.b = (float)((int)(pos.z + 1000) % 2);
	if (check.r == check.g && check.g == check.b)
		return ((t_color){255, 255, 255});
	return ((t_color){0, 0, 0});
}