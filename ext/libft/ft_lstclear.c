/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kschmidt@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 16:25:24 by kschmidt          #+#    #+#             */
/*   Updated: 2022/12/13 17:14:12 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*next;
	t_list	*head;

	if (!lst || !*lst || !del)
		return ;
	head = *lst;
	while (head)
	{
		next = head->next;
		ft_lstdelone(head, del);
		head = next;
	}
	*lst = 0;
}
