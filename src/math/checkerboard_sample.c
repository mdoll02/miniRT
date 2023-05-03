/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerboard_sample.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 23:27:04 by kschmidt          #+#    #+#             */
/*   Updated: 2023/05/03 11:16:09 by mdoll            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "rendering.h"

#define CHECKER_SIZE 5.f

t_color	checkerboard_color(t_object *obj, t_vec3 pos)
{
	t_color	black;
	t_color	white;
	t_vec3	pos2;
	t_vec3	ipos;

	(void) obj;
	black = (t_color){0, 0, 0};
	white = (t_color){255, 255, 255};
	pos2.x = pos.x / CHECKER_SIZE;
	pos2.y = pos.y / CHECKER_SIZE;
	pos2.z = pos.z / CHECKER_SIZE;
	ipos.x = roundf(pos2.x);
	ipos.y = roundf(pos2.y);
	ipos.z = roundf(pos2.z);
	if ((int)(ipos.x + ipos.y + ipos.z) % 2 == 0)
		return (white);
	return (black);
}
