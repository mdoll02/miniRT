/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 10:49:13 by kschmidt          #+#    #+#             */
/*   Updated: 2023/06/01 22:21:17 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "definitions.h"
#include "hooks.h"
#include "mlx/mlx.h"

void	register_hooks(t_minirt *minirt)
{
	mlx_expose_hook(minirt->win, expose_hook, minirt);
	mlx_hook(minirt->win, DestroyNotify, 0, close_hook, minirt);
	mlx_key_hook(minirt->win, key_hook, minirt);
}
