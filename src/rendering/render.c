/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 20:37:04 by kschmidt          #+#    #+#             */
/*   Updated: 2023/05/02 22:44:53 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "rendering.h"
#include "mlx/mlx.h"
#include "vec_math.h"

void	render_scene(t_minirt *minirt)
{
	t_vec3		ray_start;
	t_vec3		ray_dir;
	t_color		bg_color;
	int			x;
	int			y;
	float		u;
	float		v;
	t_object	*closest_obj;
	float		closest_t;
	t_vec3		hit_pos;
	t_object	*obj;
	t_vec3		isect;
	float 		t;
	t_color		pixel_color;

	ray_start = minirt->world.camera.pos;
	bg_color = minirt->world.ambient.color;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			// Calculate the ray direction for the current pixel
			u = (float)x / WIDTH;
			v = (float)y / HEIGHT;
			ray_dir = vec3_normalize((t_vec3){
					(2 * u - 1) * tanf(minirt->world.camera.fov / 2),
					(2 * v - 1) * tanf(minirt->world.camera.fov / 2)
					/ (WIDTH / HEIGHT), -1
				});

			// Find the closest intersection point of the ray with the objects in the scene
			closest_obj = 0;
			closest_t = INFINITY;
			hit_pos = (t_vec3){0, 0, 0};
			obj = minirt->world.objects;
			while (obj)
			{
				if (!obj->f_intersect)
				{
					obj = obj->next;
					continue ;
				}
				isect = obj->f_intersect(obj, ray_start, ray_dir);
				if (!isnan(isect.x) && !isnan(isect.y) && !isnan(isect.z))
				{
					t = vec3_mag(vec3_sub(isect, ray_start));
					if (t < closest_t)
					{
						closest_t = t;
						closest_obj = obj;
						hit_pos = vec3_add(ray_start,
								vec3_mul(ray_dir, closest_t));
					}
				}
				obj = obj->next;
			}

			// Sample the color at the intersection point or the background color
			pixel_color = bg_color;
			if (closest_obj != 0)
				pixel_color = closest_obj->f_sample_color(closest_obj, hit_pos);

			// Draw the pixel with the sampled color
			mlx_pixel_put(minirt->ctx, minirt->win, x, y,
				((int)pixel_color.r << 16) | ((int)pixel_color.g << 8)
				| (int)pixel_color.b);
			x++;
		}
		y++;
	}
	mlx_string_put(minirt->ctx, minirt->win, 10, 20, 0xFFFFFF, "Rendering Done!");
}