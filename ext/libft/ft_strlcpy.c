/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kschmidt@42wolfsburg.de>                    +#+  +:+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 13:57:43 by kschmidt          #+#    #+#             */
/*   Updated: 2022/12/13 17:26:24 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	srclen;
	size_t	i;

	if (!src)
		return (0);
	srclen = ft_strlen(src);
	if (!dst || !dstsize)
		return (srclen);
	i = 0;
	while (i < dstsize - 1 && i < srclen)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (srclen);
}
