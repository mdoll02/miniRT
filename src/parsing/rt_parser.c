/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoll <mdoll@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 13:47:04 by mdoll             #+#    #+#             */
/*   Updated: 2023/05/02 14:32:57 by mdoll            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "definitions.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

static void	skip_spaces(char *line, int *i)
{
	while (line[*i] == ' ' && line[*i])
		(*i)++;
}

static int	set_type(char	*line, t_lexed_line *lexed_line, int *i)
{
	int		tmp;
	int		char_count;
	char	*type;

	char_count = 0;
	skip_spaces(line, i);
	tmp = *i;
	while (ft_isalpha(line[*i]) && line[*i])
	{
		char_count++;
		(*i)++;
	}
	if (char_count == 0 || char_count > 2)
		return (1);
	type = malloc(sizeof(char) * (char_count + 1));
	if (!type)
		return (1);
	ft_strlcpy(type, &line[tmp], char_count + 1);
	lexed_line->obj_name = type;
	return (0);
}

static int	allocate_array(t_lexed_line *lexed_line, char *line, int i)
{
	int		nb_of_args;

	nb_of_args = 0;
	while (line[i] != '\n' && line[i])
	{
		if (ft_isdigit(line[i]))
		{
			nb_of_args++;
			while ((ft_isdigit(line[i]) || line[i] == '.') && line[i])
				i++;
		}
		i++;
	}
	lexed_line->values = malloc(sizeof(float) * nb_of_args);
	if (!lexed_line->values)
		return (1);
	return (0);
}

static t_lexed_line	lex_line(char *line)
{
	t_lexed_line	lexed_line;
	int				i;
	int				nb_value;
	int				value_len;

	i = 0;
	set_type(line, &lexed_line, &i); // what should I return here in case of error?
	skip_spaces(line, &i);
	allocate_array(&lexed_line, line, i);
	nb_value = 0;
	while (line[i] != '\n')
	{
		if (ft_isdigit(line[i]))
		{
			value_len = i;
			while ((ft_isdigit(line[value_len]) || line[value_len] == '.') && line[value_len])
				value_len++;
			lexed_line.values[nb_value] = (float)atof(ft_substr(line, i, value_len - i));
			nb_value++;
			while ((ft_isdigit(line[i]) || line[i] == '.') && line[i])
				i++;
		}
		i++;
	}
	return (lexed_line);
}

int	parse_rt_file(char	*file, t_world *world)
{
	t_lexed_line	lexed_line;
	int				fd;
	char			*file_to_lex;
	int				i;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (1);
	file_to_lex = malloc(sizeof(char) * 10000);
	if (!file_to_lex)
		return (1);
	read(fd, &file_to_lex, 10000);
	while (file_to_lex)
	{
		lexed_line = lex_line(file_to_lex);
		// now you can use lexed_line
		free(lexed_line.obj_name);
		free(lexed_line.values);
		i = 0;
		while (file_to_lex[i])
		{
			if (file_to_lex[i] == '\n')
				break ;
			i++;
		}
		file_to_lex = &file_to_lex[i + 1];
	}
	(void)world;
	return (0);
}

// TODO: error handling, shortening of code and implementation of ft_atof