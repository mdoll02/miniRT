/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kschmidt@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:04:54 by kschmidt          #+#    #+#             */
/*   Updated: 2022/12/13 17:29:28 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int chr)
{
	char			*last;
	unsigned char	c;

	if (!s)
		return (0);
	c = (unsigned char)chr;
	last = (char *) s + ft_strlen(s);
	while (last != s - 1)
	{
		if (*last == c)
			return (last);
		last--;
	}
	return (0);
}
