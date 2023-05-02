/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kschmidt@42wolfsburg.de>                    +#+  +:+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 13:47:05 by kschmidt          #+#    #+#             */
/*   Updated: 2022/12/13 17:17:53 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int chr, size_t n)
{
	unsigned char	c;
	size_t			i;
	unsigned char	*s;

	if (!str || !n)
		return (0);
	i = 0;
	c = (unsigned char) chr;
	s = (unsigned char *) str;
	while (i < n)
	{
		if (s[i] == c)
			return (s + i);
		i++;
	}
	return (0);
}
