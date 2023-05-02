/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kschmidt@42wolfsburg.de>                    +#+  +:+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 13:59:07 by kschmidt          #+#    #+#             */
/*   Updated: 2022/12/13 17:23:59 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int chr)
{
	unsigned char	c;

	if (!s)
		return (0);
	c = (unsigned char)chr;
	while (*s)
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	if (!c)
		return ((char *)s);
	return (0);
}
