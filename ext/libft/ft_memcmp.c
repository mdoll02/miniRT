/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kschmidt@42wolfsburg.de>                    +#+  +:+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 13:46:43 by kschmidt          #+#    #+#             */
/*   Updated: 2022/12/13 17:19:37 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			pos;
	unsigned char	*s1_c;
	unsigned char	*s2_c;

	if (n < 1)
		return (0);
	pos = 0;
	s1_c = (unsigned char *) s1;
	s2_c = (unsigned char *) s2;
	while (pos < n)
	{
		if (s1_c[pos] != s2_c[pos])
			return (s1_c[pos] - s2_c[pos]);
		pos++;
	}
	pos--;
	return (s1_c[pos] - s2_c[pos]);
}
