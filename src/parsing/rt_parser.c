/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoll <mdoll@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 13:47:04 by mdoll             #+#    #+#             */
/*   Updated: 2023/05/02 23:07:33 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "definitions.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "rendering.h"

static const struct {
	char				*name;
	t_f_check_intersect	func;
} s_intersect_funcs[] = {
	{"sp", (t_f_check_intersect) & sphere_intersect},
	{"pl", (t_f_check_intersect) & plane_intersect},
	{"cy", (t_f_check_intersect) & cylinder_intersect},
	{0, 0}
};

static const struct {
	char				*name;
	t_f_sample_color	func;
} s_sample_funcs[] = {
	{"sp", (t_f_sample_color) & sphere_sample_color},
	{"pl", (t_f_sample_color) & plane_sample_color},
	{"cy", (t_f_sample_color) & cylinder_sample_color},
	{0, 0}
};

static char	*skip_spaces(char *line)
{
	char	*cur;

	cur = line;
	while ((*cur == ' ' || *cur == '\t') && *cur)
		cur++;
	return (cur);
}

static char	*get_word_end(char *line)
{
	char	*cur;

	cur = line;
	while (*cur != ' ' && *cur != '\t' && *cur != '\n' && *cur)
		cur++;
	return (cur);
}

static char	*set_type(char	*line, t_lexed_line *lexed_line)
{
	char	*cur;

	line = skip_spaces(line);
	cur = get_word_end(line);
	if (cur == line)
		return (0);
	lexed_line->obj_name = malloc(cur - line + 1);
	if (!lexed_line->obj_name)
		return (0);
	ft_strlcpy(lexed_line->obj_name, line, cur - line + 1);
	return (cur);
}

static int	allocate_flt_array(float **num_arr, char *line)
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
	*num_arr = malloc(sizeof(float) * nb_of_args);
	if (!*num_arr)
		return (0);
	return (nb_of_args);
}

static int	lex_line(char *line, t_lexed_line *lexed_line)
{
	char	*cur;
	char	*tmp;
	int		i;

	line = set_type(line, lexed_line);
	if (!line)
		return (1);
	lexed_line->nb_of_values = allocate_flt_array(&lexed_line->values, line);
	if (!lexed_line->nb_of_values)
		return (2);
	cur = line;
	i = 0;
	while (*cur && *cur != '\n')
	{
		cur = skip_spaces(cur);
		line = cur;
		if (*line == '/')
			break ;
		while ((ft_isdigit(*cur) || *cur == '.' || *cur == '-') && *cur)
			cur++;
		tmp = ft_substr(line, 0, cur - line);
		lexed_line->values[i] = atof(tmp);
		i++;
		cur++;
	}
	return (0);
}

static ssize_t	get_file_size(char *file)
{
	int		fd;
	ssize_t	total_size;
	ssize_t	size;
	char	text[100];

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (1);
	total_size = 0;
	while (1)
	{
		size = read(fd, &text, 100);
		total_size += size;
		if (size <= 0)
			break ;
	}
	close(fd);
	return (total_size);
}

static void	append_object(t_object **objects, t_object *new_obj)
{
	t_object	*cur;

	if (!*objects)
	{
		*objects = new_obj;
		return ;
	}
	cur = *objects;
	while (cur->next)
		cur = cur->next;
	cur->next = new_obj;
	new_obj->next = 0;
}

static void	set_support_functions(const char *type, t_object *obj)
{
	int		i;

	i = 0;
	while (s_intersect_funcs[i].name)
	{
		if (!ft_strcmp(s_intersect_funcs[i].name, type))
		{
			obj->f_intersect = s_intersect_funcs[i].func;
			break ;
		}
		i++;
	}
	if (i == sizeof(s_intersect_funcs) / sizeof(s_intersect_funcs[0]))
		obj->f_intersect = 0;
	i = 0;
	while (s_sample_funcs[i].name)
	{
		if (!ft_strcmp(s_sample_funcs[i].name, type))
		{
			obj->f_sample_color = s_sample_funcs[i].func;
			return ;
		}
		i++;
	}
	obj->f_sample_color = 0;
}

static int	add_object(t_lexed_line *lex, t_object **objects)
{
	t_any_object	*obj;

	obj = malloc(sizeof(t_any_object));
	if (!obj)
		return (1);
	if ((!ft_strcmp(lex->obj_name, "sp") && lex->nb_of_values != 7)
		|| (!ft_strcmp(lex->obj_name, "pl") && lex->nb_of_values != 9)
		|| (!ft_strcmp(lex->obj_name, "cy") && lex->nb_of_values != 11))
	{
		printf("Error: Wrong number of arguments for object %s\n",
			lex->obj_name);
		free(obj);
		return (1);
	}
	set_support_functions(lex->obj_name, (t_object *)obj);
	ft_memcpy(((char *)obj) + sizeof(t_object), lex->values,
		sizeof(float) * lex->nb_of_values);
	append_object(objects, (t_object *)obj);
	return (0);
}

static int	put_lexed_line(t_lexed_line *lex, t_world *world)
{
	if (!ft_strcmp(lex->obj_name, "A") && lex->nb_of_values == 4)
		world->ambient = *(t_ambient *)lex->values;
	else if (!ft_strcmp(lex->obj_name, "C") && lex->nb_of_values == 7)
		world->camera = *(t_camera *)lex->values;
	else if (!ft_strcmp(lex->obj_name, "L") && lex->nb_of_values == 7)
		world->light = *(t_light *)lex->values;
	else
		return (add_object(lex, &world->objects));
	return (0);
}

int	parse_rt_file(char	*file, t_world *world)
{
	t_lexed_line	lexed_line;
	int				fd;
	char			*file_content;
	ssize_t			file_size;
	int				i;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (1);
	file_size = get_file_size(file);
	if (file_size < 0)
		return (2);
	file_content = malloc(file_size + 1);
	if (!file_content)
		return (3);
	read(fd, file_content, file_size);
	i = 0;
	while (file_content[i])
	{
		lex_line(file_content + i, &lexed_line);
		put_lexed_line(&lexed_line, world);
		if (lexed_line.obj_name)
			free(lexed_line.obj_name);
		if (lexed_line.values)
			free(lexed_line.values);
		while (file_content[i] != '\n' && file_content[i])
			i++;
		if (file_content[i])
			i++;
	}
	return (0);
}

// TODO: error handling, shortening of code and implementation of ft_atof