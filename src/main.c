/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 09:50:18 by kschmidt          #+#    #+#             */
/*   Updated: 2023/05/02 13:52:40 by mdoll            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx/mlx.h>
#include <printf.h>
#include <stdlib.h>
#include "hooks.h"
#include "parsing.h"

static void	error_and_exit(const char *msg)
{
	printf("Error\n%s\n", msg);
	exit(1);
}

int	main(int argc, char **argv)
{
	t_minirt	minirt;

	if (argc != 2)
		error_and_exit("Wrong number of arguments\n");
	if (parse_rt_file(argv[1], &minirt.world))
		error_and_exit("Failed to parse file\n");
	minirt.ctx = mlx_init();
	minirt.win = mlx_new_window(minirt.ctx, 1280, 720, "Pain");
	register_hooks(&minirt);
	mlx_loop(minirt.ctx);
}
