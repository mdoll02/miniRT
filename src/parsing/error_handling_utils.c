/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoll <mdoll@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:40:08 by mdoll             #+#    #+#             */
/*   Updated: 2023/05/04 13:40:08 by mdoll            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdio.h>
#include "libft.h"

int	check_file_ending(char const *file)
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

bool	check_elements(t_elements *elements, char *obj_name)
{
	if (!ft_strcmp(obj_name, "A"))
	{
		if (elements->ambient)
			return (false);
		elements->ambient = true;
	}
	else if (!ft_strcmp(obj_name, "C"))
	{
		if (elements->camera)
			return (false);
		elements->camera = true;
	}
	else if (!ft_strcmp(obj_name, "L"))
	{
		if (elements->light)
			return (false);
		elements->light = true;
	}
	return (true);
}
