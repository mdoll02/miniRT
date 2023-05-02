/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 09:50:18 by kschmidt          #+#    #+#             */
/*   Updated: 2023/05/02 10:43:37 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx/mlx.h>
#include <stdlib.h>
#include "definitions.h"

int	main(void)
{
	t_minirt	minirt;

	minirt.ctx = mlx_init();
	minirt.win = mlx_new_window(minirt.ctx, 1280, 720, "Pain");
	mlx_loop(minirt.ctx);
	mlx_destroy_window(minirt.ctx, minirt.win);
	free(minirt.ctx);
	return (0);
}
