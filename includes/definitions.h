/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   definitions.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 09:59:30 by kschmidt          #+#    #+#             */
/*   Updated: 2023/05/02 13:37:02 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINITIONS_H
# define DEFINITIONS_H

# include <X11/X.h>
# include <X11/keysym.h>

typedef void*		t_mlx_context;
typedef void*		t_mlx_window;

typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}	t_vec3;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef t_color(	*t_f_check_intersect)(struct s_object obj,
										t_vec3 pos1,
										t_vec3 pos2);
typedef t_vec3(		*t_f_sample_color)(struct s_object obj, t_vec3 pos);

typedef struct s_minirt
{
	t_mlx_context	ctx;
	t_mlx_window	win;
}	t_minirt;

typedef struct s_object
{
	struct s_object		*next;
	t_f_check_intersect	f_intersect;
	t_f_sample_color	f_sample_color;
}	t_object;

typedef struct s_plane
{
	t_object	obj;
	t_vec3		pos;
	t_vec3		normal;
	t_color		color;
}	t_plane;

typedef struct s_sphere
{
	t_object	obj;
	t_vec3		pos;
	float		radius;
	t_color		color;
}	t_sphere;

typedef struct s_cylinder
{
	t_object	obj;
	t_vec3		pos;
	t_vec3		axis;
	float		radius;
	float		height;
	t_color		color;
}	t_cylinder;

typedef struct s_camera
{
	t_vec3	pos;
	t_vec3	normal;
	float	fov;
}	t_camera;

typedef struct s_light
{
	t_vec3	pos;
	float	brightness;
	t_vec3	color;
}	t_light;

typedef struct world
{
	t_camera	camera;
	t_light		light;
	t_object	*objects;
}	t_world;

#endif //DEFINITIONS_H
