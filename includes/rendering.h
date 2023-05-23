/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 20:39:12 by kschmidt          #+#    #+#             */
/*   Updated: 2023/05/22 12:42:04 by mdoll            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERING_H
# define RENDERING_H

# include <stdbool.h>
# include "definitions.h"

# define MAX_DEPTH 5
# define MAT_REFLECTIVE .3f
# define MAT_TRANSPARENCY .0f
# define MAT_IOR .4f

t_vec3			sphere_normal(t_sphere *sphere, t_vec3 pos);
t_color			sphere_sample_color(t_sphere *sphere, t_vec3 pos);
t_vec3			plane_normal(t_plane *plane, t_vec3 pos);
t_color			plane_sample_color(t_plane *plane, t_vec3 pos);
t_vec3			cylinder_normal(t_cylinder *cyl, t_vec3 pos);
t_color			cylinder_sample_color(t_cylinder *cyl, t_vec3 pos);
t_color			checkerboard_color(t_object *obj, t_vec3 pos);
t_intersection	cylinder_intersect(t_cylinder *cylinder, t_vec3 pos, \
													t_vec3 dir);
t_vec3			cylinder_cap_intersect(t_cylinder *cylinder, t_vec3 pos, \
													t_vec3 dir, bool is_top);
double			cylinder_side_intersect(t_cylinder *cylinder, t_vec3 pos, \
																t_vec3 dir);
t_intersection	sphere_intersect(t_sphere *sphere, t_vec3 pos, t_vec3 dir);
t_intersection	plane_intersect(t_plane *plane, t_vec3 pos, t_vec3 dir);
void			render_scene(t_minirt *minirt);
int				is_illuminated(t_minirt *mrt, t_intersection isect,
					t_light light);
double			specular_lighting(t_minirt *mrt, t_intersection closest_isect,
					t_vec3 light_dir);
t_intersection	find_closest_intersection(t_minirt *minirt, t_vec3 ray_start,
					t_object *ignore, t_vec3 ray_dir);
t_color			sample_color_at_intersection(t_minirt *mrt,
					t_intersection closest_isect, t_vec3 ray_dir, int depth);
t_color			get_reflection(t_vec3 ray_dir, t_minirt *mrt,
					t_intersection closest_isect, int depth);
t_color			get_transparency(t_vec3 ray_dir, t_minirt *mrt,
					t_intersection closest_isect, int depth);
t_vec3			calculate_ray_direction(t_minirt *minirt, int x, int y);

#endif //RENDERING_H
