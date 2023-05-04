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

static int	iterate_file(char *file_content, t_world *world)
{
	int				i;
	t_lexed_line	lexed_line;
	t_elements		elements;

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

int	parse_rt_file(char	*file, t_world *world)
{
	int				fd;
	char			*file_content;
	ssize_t			file_size;

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
	if (iterate_file(file_content, world))
		return (4);
	free(file_content);
	return (0);
}
