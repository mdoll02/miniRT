/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kschmidt@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 18:51:50 by kschmidt          #+#    #+#             */
/*   Updated: 2022/12/13 17:30:58 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strtrim(const char *s1, const char *set)
{
	char	*p;
	char	*start;
	char	*end;

	if (!s1 || !set)
		return (0);
	if (!*s1)
		return (ft_strdup(""));
	start = (char *) s1;
	end = (char *)s1 + ft_strlen(s1) - 1;
	while (ft_strchr(set, *start) && start < end)
		start++;
	while (ft_strchr(set, *end) && end > start)
		end--;
	if (start == end && ft_strchr(set, *start))
		return (ft_strdup(""));
	p = malloc(end - start + 2);
	ft_strlcpy(p, start, end - start + 2);
	return (p);
}
