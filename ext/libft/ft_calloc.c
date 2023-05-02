/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kschmidt@42wolfsburg.de>                    +#+  +:+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 13:50:02 by kschmidt          #+#    #+#             */
/*   Updated: 2022/12/13 17:09:43 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size)
{
	char	*addr;
	size_t	total;

	if (count <= 0 || size <= 0)
		return (0);
	total = size * count;
	if (total / size != count)
		return (0);
	addr = malloc(total);
	ft_bzero(addr, total);
	return (addr);
}
