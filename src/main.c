/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 09:50:18 by kschmidt          #+#    #+#             */
/*   Updated: 2023/05/02 23:41:22 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx/mlx.h>
#include <stdlib.h>
#include <stdio.h>
#include "hooks.h"
#include "parsing.h"
#include "libft.h"
#include "rendering.h"

static void	error_and_exit(const char *msg)
{
	printf("Error\n%s\n", msg);
	exit(1);
}

int	main(int argc, char **argv)
{
	t_minirt	minirt;

	if (argc != 2)
		error_and_exit("Wrong number of arguments");
	ft_bzero(&minirt, sizeof(t_minirt));
	if (parse_rt_file(argv[1], &minirt.world))
		exit(1);
	printf("Parsed file successfully\n");
	minirt.ctx = mlx_init();
	minirt.win = mlx_new_window(minirt.ctx, WIDTH, HEIGHT, "Pain");
	minirt.img.img = mlx_new_image(minirt.ctx, WIDTH, HEIGHT);
	minirt.img.addr = mlx_get_data_addr(minirt.img.img, &minirt.img.bbp,
			&minirt.img.line_length, &minirt.img.endian);
	render_scene(&minirt);
	register_hooks(&minirt);
	mlx_loop(minirt.ctx);
	return (0);
}
