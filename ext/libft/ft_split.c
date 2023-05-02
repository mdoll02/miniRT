/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kschmidt@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 09:40:58 by kschmidt          #+#    #+#             */
/*   Updated: 2022/12/13 17:23:36 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	**split_rec(const char *cur, char c, int depth)
{
	char	*start;
	char	*end;
	char	*next;
	char	**p;

	start = (char *) cur;
	end = start;
	while (*end && *end != c)
		end++;
	next = end;
	while (*next == c)
		next++;
	if (*end && *next)
		p = split_rec(next, c, depth + 1);
	else
	{
		p = malloc((depth + 2) * sizeof(char *));
		p[depth + 1] = 0;
	}
	p[depth] = ft_substr(start, 0, end - start);
	return (p);
}

char	**ft_split(const char *s, char c)
{
	char	**res;

	if (!s)
		return (0);
	while (*s == c && c)
		s++;
	if (!*s)
	{
		res = malloc(sizeof(char *));
		res[0] = 0;
	}
	else
		res = split_rec(s, c, 0);
	return (res);
}
