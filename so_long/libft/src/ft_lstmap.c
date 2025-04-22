/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 01:42:34 by vandre            #+#    #+#             */
/*   Updated: 2023/10/19 14:33:13 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*tmp;
	t_list	*ptr;

	if (!lst || !f || !del)
		return (NULL);
	tmp = ft_lstnew(f(lst->content));
	if (!tmp)
		return (NULL);
	ptr = tmp;
	lst = lst->next;
	while (lst)
	{
		tmp->next = ft_lstnew(f(lst->content));
		if (!tmp->next)
		{
			ft_lstclear(&tmp, del);
			return (NULL);
		}
		lst = lst->next;
		tmp = tmp->next;
	}
	tmp->next = NULL;
	return (ptr);
}
