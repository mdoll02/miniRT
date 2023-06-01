/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoll <mdoll@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 10:38:33 by mdoll             #+#    #+#             */
/*   Updated: 2023/05/04 10:38:41 by mdoll            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "math.h"
#include "libft.h"

static void	skip_whitespaces(char *str)
{
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
}

float	ft_atof(char *str)
{
	float	sign;
	float	result;
	int		i;

	if (!str)
		return (0);
	skip_whitespaces(str);
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	result = 0;
	i = 0;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (float)*str - '0';
		str++;
		i++;
	}
	if (*str == '.')
		result += (float)ft_atof(str + 1) / (float)pow(10, ft_strlen(str + 1));
	return (result * sign);
}
