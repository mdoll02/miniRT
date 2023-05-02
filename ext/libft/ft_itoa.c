/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kschmidt@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 10:02:25 by kschmidt          #+#    #+#             */
/*   Updated: 2022/12/13 17:13:05 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <limits.h>

int	ft_numsize(int n)
{
	unsigned char	size;

	size = 0;
	while (n != 0)
	{
		n /= 10;
		size++;
	}
	return (size);
}

char	*test(int n)
{
	if (n == INT_MIN)
		return (ft_strdup("-2147483648"));
	else if (n == INT_MAX)
		return (ft_strdup("2147483647"));
	else if (!n)
		return (ft_strdup("0"));
	return (0);
}

char	*ft_itoa(int n)
{
	char	*p;
	char	*cur;
	char	neg;
	char	size;

	p = test(n);
	if (p)
		return (p);
	neg = n < 0;
	size = ft_numsize(n);
	p = malloc((neg + size + 1) * sizeof(char));
	cur = p;
	if (neg)
	{
		*cur++ = '-';
		n *= -1;
	}
	cur += size - 1;
	while (n)
	{
		*cur-- = n % 10 + '0';
		n /= 10;
	}
	*(cur + size + 1) = '\0';
	return (p);
}
