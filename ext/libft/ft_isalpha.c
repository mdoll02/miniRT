/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kschmidt@42wolfsburg.de>                    +#+  +:        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 13:51:49 by kschmidt          #+#    #+#             */
/*   Updated: 2022/12/13 17:10:32 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	unsigned char	uc;

	uc = (unsigned char)c;
	return ((uc >= 'A' && uc <= 'Z') || (uc >= 'a' && uc <= 'z'));
}
