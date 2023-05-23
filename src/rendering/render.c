/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 20:37:04 by kschmidt          #+#    #+#             */
/*   Updated: 2023/05/23 14:21:17 by mdoll            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"
#include "mlx/mlx.h"
#include "vec_math.h"
#include "color_math.h"

static void	mrt_pixel_put(t_mlx_image *img, int x, int y, t_color color)
{
	char	*dst;

	dst = img->addr + ((HEIGHT - 1 - y) * img->line_length + \
										x * (img->bbp / 8));
	*(unsigned int *)dst = color_to_int(color);
}

static void	render_pixel(t_vec3 ray_start, t_coordinates coords, \
							t_minirt *minirt)
{
	t_color			pixel_color;
	t_vec3			ray_dir;
	t_intersection	isect;

	ray_dir = calculate_ray_direction(minirt, coords.x, coords.y);
	isect = find_closest_intersection(minirt, ray_start, 0, ray_dir);
	if (isect.obj)
		pixel_color = sample_color_at_intersection(minirt, \
					isect, ray_dir, 0);
	else
		pixel_color = minirt->world.ambient.color;
	mrt_pixel_put(&minirt->img, coords.x, coords.y, pixel_color);
}

void	render_scene(t_minirt *minirt)
{
	t_vec3			ray_start;
	t_coordinates	coords;

	ray_start = minirt->world.camera.pos;
	coords.y = HEIGHT;
	while (coords.y-- >= 0)
	{
		coords.x = 0;
		while (coords.x < WIDTH)
		{
			render_pixel(ray_start, coords, minirt);
			coords.x++;
		}
		mlx_put_image_to_window(minirt->ctx, minirt->win, \
			minirt->img.img, 0, 0);
	}
	mlx_put_image_to_window(minirt->ctx, minirt->win, minirt->img.img, 0, 0);
}
