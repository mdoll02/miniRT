/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kschmidt@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 16:40:23 by kschmidt          #+#    #+#             */
/*   Updated: 2022/12/13 17:15:40 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 
#include <stdlib.h>

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*begin;
	t_list	*head;

	if (!lst || !f || !del)
		return (0);
	begin = malloc(sizeof(t_list));
	if (!begin)
		return (0);
	head = begin;
	while (1)
	{
		ft_memcpy(head, lst, sizeof(t_list));
		head->content = f(head->content);
		lst = lst->next;
		if (!lst)
			break ;
		head->next = malloc(sizeof(t_list));
		if (!head->next)
		{
			ft_lstclear(&begin, del);
			return (0);
		}
		head = head->next;
	}
	return (begin);
}
