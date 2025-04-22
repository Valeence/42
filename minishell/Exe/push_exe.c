/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_exe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zachamou <zachamou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 00:50:33 by zachamou          #+#    #+#             */
/*   Updated: 2024/06/28 00:40:41 by zachamou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/MiniShell.h"

void	push_in(t_Token **curr)
{
	if ((*curr) != NULL && (*curr)->next != NULL && (*curr)->next->next != NULL
		&& (*curr)->next->next->next != NULL
		&& (*curr)->next->next->next->type == E_PIPE)
		(*curr) = (*curr)->next->next->next;
	else if ((*curr) != NULL && (*curr)->next != NULL
		&& (*curr)->next->next != NULL && (*curr)->next->next->next != NULL
		&& (*curr)->next->next != NULL && ((*curr)->type == E_WORD
			&& (*curr)->next->type == E_IN
			&& (*curr)->next->next->type == E_FILE))
		(*curr) = (*curr)->next->next->next->next;
	else if ((*curr) != NULL && (*curr)->next != NULL
		&& (*curr)->next->next != NULL && ((*curr)->type == E_IN
			&& (*curr)->next->type == E_FILE
			&& (*curr)->next->next->type == E_WORD))
		(*curr) = (*curr)->next->next->next;
	else
		(*curr) = (*curr)->next->next;
}

void	push_exe(t_Token **curr, t_data *data)
{
	if (data->data2->redi_and_here == true)
		free(data->str_here);
	(*curr) = (*curr)->next;
	while ((*curr) != NULL)
	{
		if ((*curr)->type == E_WORD || (*curr)->next == NULL
			|| (*curr)->type == E_PIPE)
			break ;
		else
			(*curr) = (*curr)->next;
	}
}
