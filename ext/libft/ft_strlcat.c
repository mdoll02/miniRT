/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kschmidt@42wolfsburg.de>                    +#+  +:+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 13:58:07 by kschmidt          #+#    #+#             */
/*   Updated: 2022/12/13 17:25:45 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dstlen;

	if (!dst && !src)
		return (0);
	if (!dst || !dstsize)
		return (ft_strlen(src));
	dstlen = ft_strlen(dst);
	if (dstlen > dstsize)
		dstlen = dstsize;
	if (!src)
		return (dstlen);
	if (dstsize > dstlen)
		ft_strlcpy(dst + dstlen, src, dstsize - dstlen);
	return (dstlen + ft_strlen(src));
}
