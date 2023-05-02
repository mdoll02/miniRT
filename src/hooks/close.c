/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_hooks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 10:46:53 by kschmidt          #+#    #+#             */
/*   Updated: 2023/05/02 11:29:50 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx/mlx.h>
#include <libc.h>
#include "hooks.h"

int	close_hook(t_minirt *minirt)
{
	mlx_destroy_window(minirt->ctx, minirt->win);
	free(minirt->ctx);
	exit(0);
}
