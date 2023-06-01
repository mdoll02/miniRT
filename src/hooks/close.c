/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_hooks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 10:46:53 by kschmidt          #+#    #+#             */
/*   Updated: 2023/05/02 18:35:38 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx/mlx.h>
#include <stdlib.h>
#include "hooks.h"

static void	clean_objects(t_object *obj)
{
	t_object	*tmp;

	while (obj)
	{
		tmp = obj;
		obj = obj->next;
		free(tmp);
	}
	free(obj);
}

int	close_hook(t_minirt *minirt)
{
	clean_objects(minirt->world.objects);
	mlx_destroy_window(minirt->ctx, minirt->win);
	free(minirt->ctx);
	exit(0);
}
