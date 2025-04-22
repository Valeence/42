/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Analy_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zachamou <zachamou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 04:07:00 by zachamou          #+#    #+#             */
/*   Updated: 2024/06/27 23:27:15 by zachamou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/MiniShell.h"

void	ft_analy_type_pipe(t_Token **current)
{
	(*current)->type = E_PIPE;
}

void	ft_analy_type_redi_out(t_Token **current, t_data *data)
{
	(*current)->type = E_OUT;
	if ((*current)->next != NULL)
		(*current)->next->type = E_FILE;
	(*current) = (*current)->next;
	data->data2->nb_file_out += 1;
}

void	ft_analy_type_redi_append(t_Token **current, t_data *data)
{
	(*current)->type = E_APPEND;
	if ((*current)->next != NULL)
		(*current)->next->type = E_FILE;
	(*current) = (*current)->next;
	data->data2->nb_file_out += 1;
}

void	ft_analy_type_redi_heredoc(t_Token **current)
{
	(*current)->type = E_HEREDOC;
	if ((*current)->next != NULL)
		(*current)->next->type = E_OEF_HERE;
	(*current) = (*current)->next;
}

void	free_token(t_Token *begin)
{
	t_Token	*current;
	t_Token	*next;

	current = begin;
	while (current != NULL)
	{
		next = current->next;
		if (current->type == E_FILE || current->type == E_OEF_HERE)
			if (current->file != NULL)
				ft_free_tabtab(current->file);
		free(current->token_str);
		free(current);
		current = next;
	}
}
