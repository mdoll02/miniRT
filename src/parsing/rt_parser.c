/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoll <mdoll@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 13:47:04 by mdoll             #+#    #+#             */
/*   Updated: 2023/05/03 10:28:17 by mdoll            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "definitions.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "parsing.h"
#include "stdio.h"

static char	*set_type(char	*line, t_lexed_line *lexed_line, t_elements *elements)
{
	char	*cur;

	line = skip_spaces(line);
	cur = get_word_end(line);
	if (cur - line > 2)
		return (NULL);
	if (cur - line == 1)
	{
		if (*line != 'A' && *line != 'C' && *line != 'L')
			return (NULL);
	}
	else
	{
		if (*line < 'a' || *line > 'z' || *line + 1 < 'a' || *line + 1 > 'z')
			return (NULL);
	}
	lexed_line->obj_name = malloc(cur - line + 1);
	if (!lexed_line->obj_name)
		return (NULL);
	ft_strlcpy(lexed_line->obj_name, line, cur - line + 1);
	if (!ft_strcmp(lexed_line->obj_name, "A"))
	{
		if (elements->ambient)
			return (NULL);
		elements->ambient = true;
	}
	else if (!ft_strcmp(lexed_line->obj_name, "C"))
	{
		if (elements->camera)
			return (NULL);
		elements->camera = true;
	}
	else if (!ft_strcmp(lexed_line->obj_name, "L"))
	{
		if (elements->light)
			return (NULL);
		elements->light = true;
	}
	return (cur);
}

static int	set_value(char *line, t_lexed_line *lexed_line, int end, int i)
{
	char	*tmp;

	tmp = ft_substr(line, 0, end);
	if (!tmp)
		return (1);
	lexed_line->values[i] = ft_atof(tmp);
	free(tmp);
	return (0);
}

static int	lex_line(char *line, t_lexed_line *lexed_line, t_elements *elements)
{
	char	*cur;
	int		i;

	line = set_type(line, lexed_line, elements);
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
		if (set_value(line, lexed_line, (int)(cur - line), i))
			return (3);
		i++;
		cur++;
	}
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

static int	check_file_ending(char const *file)
{
	int	i;

	i = 0;
	while (file[i])
		i++;
	if (file[i - 1] != 't' || file[i - 2] != 'r' || file[i - 3] != '.')
	{
		printf("Wrong file ending\n");
		return (1);
	}
	return (0);
}

int	parse_rt_file(char	*file, t_world *world)
{
	t_lexed_line	lexed_line;
	int				fd;
	char			*file_content;
	ssize_t			file_size;
	int				i;
	t_elements		elements;

	if (check_file_ending(file))
		return (1);
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
	file_content[file_size] = '\0';
	i = 0;
	elements = (t_elements){false, false, false};
	while (file_content[i])
	{
		while (file_content[i] == '\n' && file_content[i])
			i++;
		if (lex_line(file_content + i, &lexed_line, &elements))
			return (4);
		if (put_lexed_line(&lexed_line, world))
			return (5);
		free_lexed_line(&lexed_line);
		while (file_content[i] != '\n' && file_content[i])
			i++;
		if (file_content[i])
			i++;
	}
	return (0);
}

// TODO: error handling, shortening of code and implementation of ft_atof