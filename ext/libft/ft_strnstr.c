/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kschmidt@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:05:38 by kschmidt          #+#    #+#             */
/*   Updated: 2022/12/13 17:28:54 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	nlen;
	size_t	i;

	if (!haystack || !needle)
		return (0);
	nlen = ft_strlen(needle);
	if (!nlen)
		return ((char *) haystack);
	if (len <= 0)
		return (0);
	i = 0;
	while (haystack[i] && i <= len - nlen)
	{
		if (!ft_strncmp(haystack + i, needle, nlen))
			return ((char *) haystack + i);
		i++;
	}
	return (0);
}
