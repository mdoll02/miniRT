/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoll <mdoll@stduent.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 09:50:18 by mdoll             #+#    #+#             */
/*   Updated: 2023/05/02 10:26:54 by mdoll            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx/mlx.h>
#include <stdlib.h>
#include "definitions.h"

int	main(void)
{
	t_mlx_context	ctx;
	t_mlx_window	win;

	ctx = mlx_init();
	win = mlx_new_window(ctx, 1280, 720, "Pain");
	mlx_loop(ctx);
	mlx_destroy_window(ctx, win);
	free(ctx);
	return (0);
}
