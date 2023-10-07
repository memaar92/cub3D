/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:46:05 by mamesser          #+#    #+#             */
/*   Updated: 2023/05/18 16:41:11 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*ret;
	t_list	*new_node;

	ret = NULL;
	while (lst)
	{
		new_node = malloc(sizeof(*new_node));
		if (!new_node)
		{
			ft_lstclear(&ret, (*del));
			return (NULL);
		}
		new_node->content = (*f)(lst->content);
		new_node->next = NULL;
		ft_lstadd_back(&ret, new_node);
		lst = lst->next;
	}
	return (ret);
}
