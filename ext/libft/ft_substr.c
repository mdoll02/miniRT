/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kschmidt@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 18:29:06 by kschmidt          #+#    #+#             */
/*   Updated: 2022/12/13 17:32:33 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdlib.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	slen;
	char	*p;

	slen = ft_strlen(s);
	if (len > slen)
		len = slen;
	if (start < slen)
	{
		p = malloc(len + 1);
		ft_memcpy(p, (s + start), len);
		p[len] = 0;
	}
	else
	{
		p = malloc(1);
		*p = 0;
	}
	return (p);
}
