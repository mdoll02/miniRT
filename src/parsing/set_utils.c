/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoll <mdoll@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:54:12 by mdoll             #+#    #+#             */
/*   Updated: 2023/05/04 13:54:17 by mdoll            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"
#include <stdlib.h>

char	*set_type(char	*line, t_lexed_line *lexed_line, t_elements *elements)
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
	if (!check_elements(elements, lexed_line->obj_name))
		return (NULL);
	return (cur);
}

int	set_value(char *line, t_lexed_line *lexed_line, int end, int i)
{
	char	*tmp;

	tmp = ft_substr(line, 0, end);
	if (!tmp)
		return (1);
	lexed_line->values[i] = ft_atof(tmp);
	free(tmp);
	return (0);
}
