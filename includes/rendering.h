/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 20:39:12 by kschmidt          #+#    #+#             */
/*   Updated: 2023/05/02 23:06:57 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERING_H
# define RENDERING_H

# include "definitions.h"

t_vec3	sphere_intersect(t_sphere *sphere, t_vec3 pos, t_vec3 dir);
t_color	sphere_sample_color(t_sphere *sphere, t_vec3 pos);
t_vec3	plane_intersect(t_plane *plane, t_vec3 pos, t_vec3 dir);
t_color	plane_sample_color(t_plane *plane, t_vec3 pos);
t_vec3	cylinder_intersect(t_cylinder *cylinder, t_vec3 pos, t_vec3 dir);
t_color	cylinder_sample_color(t_cylinder *cyl, t_vec3 pos);

void	render_scene(t_minirt *minirt);

#endif //RENDERING_H
