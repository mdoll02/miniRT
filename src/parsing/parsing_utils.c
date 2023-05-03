/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoll <mdoll@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 09:43:09 by mdoll             #+#    #+#             */
/*   Updated: 2023/05/03 09:43:21 by mdoll            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

char	*skip_spaces(char *line)
{
	char	*cur;

	cur = line;
	while ((*cur == ' ' || *cur == '\t') && *cur)
		cur++;
	return (cur);
}

char	*get_word_end(char *line)
{
	char	*cur;

	cur = line;
	while (*cur != ' ' && *cur != '\t' && *cur != '\n' && *cur)
		cur++;
	return (cur);
}

ssize_t	get_file_size(char *file)
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

void	free_lexed_line(t_lexed_line *lexed_line)
{
	if (lexed_line->obj_name)
		free(lexed_line->obj_name);
	if (lexed_line->values)
		free(lexed_line->values);
}
