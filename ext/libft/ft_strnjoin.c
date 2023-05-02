/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 08:57:36 by kschmidt          #+#    #+#             */
/*   Updated: 2023/02/18 08:57:51 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>
#include <stdlib.h>

char	*ft_strnjoin(int n, ...)
{
	va_list	ap;
	char	*str;
	char	*tmp;
	char	*tmp2;
	int		i;

	va_start(ap, n);
	str = ft_strdup(va_arg(ap, char *));
	i = 1;
	while (i < n)
	{
		tmp = str;
		tmp2 = va_arg(ap, char *);
		str = ft_strjoin(str, tmp2);
		free(tmp);
		i++;
	}
	va_end(ap);
	return (str);
}
