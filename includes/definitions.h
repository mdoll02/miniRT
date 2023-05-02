/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   definitions.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 09:59:30 by kschmidt          #+#    #+#             */
/*   Updated: 2023/05/02 23:39:45 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINITIONS_H
# define DEFINITIONS_H

# include <X11/X.h>
# include <X11/keysym.h>

# define WIDTH 1280
# define HEIGHT 720

typedef void*		t_mlx_context;
typedef void*		t_mlx_window;
typedef void*		t_mlx_image_ptr;

typedef struct s_mlx_image
{
	t_mlx_image_ptr	img;
	char			*addr;
	int				bbp;
	int				line_length;
	int				endian;
}	t_mlx_image;

typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}	t_vec3;

typedef struct s_color
{
	float	r;
	float	g;
	float	b;
}	t_color;

struct				s_object;

typedef t_vec3(		*t_f_check_intersect)(struct s_object* obj,
										t_vec3 pos,
										t_vec3 dir);
typedef t_color(	*t_f_sample_color)(struct s_object* obj, t_vec3 pos);

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

typedef union s_any_object {
	t_object	obj;
	t_plane		plane;
	t_sphere	sphere;
	t_cylinder	cylinder;
}	t_any_object;

typedef struct s_ambient
{
	float	brightness;
	t_color	color;
}	t_ambient;

typedef struct s_camera
{
	t_vec3	pos;
	t_vec3	dir;
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
	t_ambient	ambient;
	t_camera	camera;
	t_light		light;
	t_object	*objects;
}	t_world;

typedef struct s_minirt
{
	t_mlx_context	ctx;
	t_mlx_window	win;
	t_world			world;
	t_mlx_image		img;
}	t_minirt;

typedef struct s_lexed_line
{
	char	*obj_name;
	float	*values;
	int		nb_of_values;
}	t_lexed_line;

#endif //DEFINITIONS_H
