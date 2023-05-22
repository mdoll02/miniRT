/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 20:39:12 by kschmidt          #+#    #+#             */
/*   Updated: 2023/05/10 09:33:26 by mdoll            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERING_H
# define RENDERING_H

# include <stdbool.h>
# include "definitions.h"

t_vec3			sphere_normal(t_sphere *sphere, t_vec3 pos);
t_color			sphere_sample_color(t_sphere *sphere, t_vec3 pos);
t_vec3			plane_normal(t_plane *plane, t_vec3 pos);
t_color			plane_sample_color(t_plane *plane, t_vec3 pos);
t_vec3			cylinder_normal(t_cylinder *cyl, t_vec3 pos);
t_color			cylinder_sample_color(t_cylinder *cyl, t_vec3 pos);
t_color			checkerboard_color(t_object *obj, t_vec3 pos);
t_intersection	cylinder_intersect(t_cylinder *cylinder, t_vec3 pos, t_vec3 dir);
t_vec3			cylinder_cap_intersect(t_cylinder *cylinder, t_vec3 pos, \
													t_vec3 dir, bool is_top);
double			cylinder_side_intersect(t_cylinder *cylinder, t_vec3 pos, \
																t_vec3 dir);
t_intersection	sphere_intersect(t_sphere *sphere, t_vec3 pos, t_vec3 dir);
t_intersection	plane_intersect(t_plane *plane, t_vec3 pos, t_vec3 dir);
void			render_scene(t_minirt *minirt);

#endif //RENDERING_H
