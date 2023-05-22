/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoll <mdoll@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 09:57:28 by mdoll             #+#    #+#             */
/*   Updated: 2023/05/22 13:22:01 by mdoll            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"
#include "rendering.h"
#include <stdlib.h>
#include <stdio.h>

typedef const struct s_func_pair{
	char	*name;
	void	*func;
}	t_func_pair;

static const struct{
	char	*name;
	void	*func;
}s_intersect_funcs[] = {
{"sp", (t_f_check_intersect) & sphere_intersect},
{"pl", (t_f_check_intersect) & plane_intersect},
{"cy", (t_f_check_intersect) & cylinder_intersect},
{0, 0}
};

static const struct{
	char	*name;
	void	*func;
}s_normal_funcs[] = {
{"sp", (t_f_get_normal) & sphere_normal},
{"pl", (t_f_get_normal) & plane_normal},
{"cy", (t_f_get_normal) & cylinder_normal},
{0, 0}
};

static const struct{
	char	*name;
	void	*func;
}s_sample_funcs[] = {
{"sp", (t_f_sample_color) & sphere_sample_color},
{"pl", (t_f_sample_color) & plane_sample_color},
{"cy", (t_f_sample_color) & cylinder_sample_color},
{0, 0}
};

void	append_object(t_object **objects, t_object *new_obj)
{
	t_object	*cur;

	if (!*objects)
	{
		*objects = new_obj;
		return ;
	}
	cur = *objects;
	while (cur && cur->next)
		cur = cur->next;
	cur->next = new_obj;
	new_obj->next = 0;
}

int	add_object(t_lexed_line *lex, t_object **objects)
{
	t_any_object	*obj;

	obj = malloc(sizeof(t_any_object));
	if (!obj)
		return (1);
	if ((!ft_strcmp(lex->obj_name, "sp") && lex->nb_of_values != 7)
		|| (!ft_strcmp(lex->obj_name, "pl") && lex->nb_of_values != 9)
		|| (!ft_strcmp(lex->obj_name, "cy") && lex->nb_of_values != 11))
	{
		printf("Error: Wrong number of arguments for object %s\n", \
			lex->obj_name);
		free(obj);
		return (1);
	}
	set_support_functions(lex->obj_name, (t_object *)obj);
	ft_memcpy(((char *)obj) + sizeof(t_object), lex->values, \
			sizeof(double) * lex->nb_of_values);
	obj->obj.next = 0;
	append_object(objects, (t_object *)obj);
	return (0);
}

void	*get_function_by_name(const t_func_pair *pairs, const char *name)
{
	int	i;

	i = 0;
	while (pairs[i].name)
	{
		if (!ft_strcmp(pairs[i].name, name))
			return (pairs[i].func);
		i++;
	}
	return (0);
}

void	set_support_functions(const char *type, t_object *obj)
{
	obj->f_intersect = get_function_by_name((t_func_pair *)s_intersect_funcs,
			type);
	obj->f_get_normal = get_function_by_name((t_func_pair *)s_normal_funcs,
			type);
	obj->f_sample_color = get_function_by_name((t_func_pair *)s_sample_funcs,
			type);
}

int	allocate_flt_array(double **num_arr, char *line)
{
	int		nb_of_args;

	nb_of_args = 0;
	while (*line && *line != '\n')
	{
		line = skip_spaces(line);
		while ((ft_isdigit(*line) || *line == '.' || *line == '-') && *line)
			line++;
		if (*line == '/')
			break ;
		if (*line != ',' && *line != '\n' && skip_spaces(line) == line && *line)
			return (0);
		nb_of_args++;
		line++;
	}
	if (!nb_of_args)
		return (0);
	*num_arr = malloc(sizeof(double) * nb_of_args);
	if (!*num_arr)
		return (0);
	return (nb_of_args);
}
