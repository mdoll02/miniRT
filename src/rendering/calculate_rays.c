/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_rays.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoll <mdoll@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 09:58:18 by mdoll             #+#    #+#             */
/*   Updated: 2023/05/23 09:58:24 by mdoll            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "rendering.h"
#include "vec_math.h"

static t_vec3	transform_ray(t_vec3 ray_dir, t_camera_vectors cam_v)
{
	t_vec3				transformed_dir;

	transformed_dir.x = vec3_dot(ray_dir, cam_v.camera_right);
	transformed_dir.y = vec3_dot(ray_dir, cam_v.camera_up);
	transformed_dir.z = vec3_dot(ray_dir, cam_v.camera_dir);
	return (transformed_dir);
}

t_vec3	calculate_ray_direction(t_minirt *mrt, int x, int y)
{
	double				u;
	double				v;
	double				fov_radians;
	t_camera_vectors	cam_v;
	t_vec3				ray_dir;

	u = (double)x / WIDTH;
	v = (double)y / HEIGHT;
	fov_radians = fmax(0, fmin(mrt->world.camera.fov, 180.0f)) * M_PI / 180.0;
	cam_v.camera_dir = vec3_normalize(mrt->world.camera.dir);
	cam_v.camera_right = vec3_normalize(vec3_cross((t_vec3){0, 1, 0},
				cam_v.camera_dir));
	cam_v.camera_up = vec3_cross(cam_v.camera_right, cam_v.camera_dir);
	ray_dir.x = (2 * u - 1) * tan(fov_radians / 2);
	ray_dir.y = (1 - 2 * v) * tan(fov_radians / 2) * HEIGHT / WIDTH;
	ray_dir.z = -1;
	return (vec3_normalize(transform_ray(ray_dir, cam_v)));
}
