/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expose.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 22:21:46 by kschmidt          #+#    #+#             */
/*   Updated: 2023/06/01 22:24:26 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hooks.h"
#include "mlx/mlx.h"

int	expose_hook(t_minirt *minirt)
{
	mlx_put_image_to_window(minirt->ctx, minirt->win, minirt->img.img, 0, 0);
	return (0);
}
