/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 16:25:25 by vandre            #+#    #+#             */
/*   Updated: 2024/10/26 17:26:42 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp_element;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		tmp_element = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = tmp_element;
	}
	*lst = NULL;
}
