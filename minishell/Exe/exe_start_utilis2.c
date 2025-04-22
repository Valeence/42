/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_start_utilis2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zachamou <zachamou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 00:34:20 by zachamou          #+#    #+#             */
/*   Updated: 2024/06/27 23:27:15 by zachamou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/MiniShell.h"
#define MAX_PIDS 100

void	push_position(t_Token **curr, int grab_hd)
{
	int	i;

	i = 0;
	while (*curr != NULL)
	{
		if ((*curr)->type == E_HEREDOC)
			i += 1;
		if (i == grab_hd)
			break ;
		if ((*curr)->next == NULL || (*curr)->next->type == E_PIPE
			|| search_redi((*curr)))
			break ;
		else
			(*curr) = (*curr)->next;
	}
}

bool	shr_out_in_here(t_Token *lst)
{
	t_Token	*shr_out;

	shr_out = lst;
	while (shr_out != NULL && shr_out->next != NULL)
	{
		if (shr_out->token_str[0] == '|' || shr_out->type == E_IN)
			return (false);
		if (shr_out->type == E_OUT || shr_out->type == E_APPEND)
			return (true);
		shr_out = shr_out->next;
	}
	return (false);
}

int	cont_nb_out(t_Token *curr)
{
	t_Token	*shr_out;
	int		i;

	i = 0;
	shr_out = curr;
	while (shr_out != NULL && shr_out->next != NULL)
	{
		if (shr_out->token_str[0] == '|' || shr_out->type == E_IN)
			return (i);
		if (shr_out->type == E_OUT || shr_out->type == E_APPEND)
			i++;
		shr_out = shr_out->next;
	}
	return (i);
}

int	cont_nb_in(t_Token *curr)
{
	t_Token	*shr_out;
	int		i;

	i = 0;
	shr_out = curr;
	while (shr_out != NULL && shr_out->next != NULL)
	{
		if (shr_out->token_str[0] == '|' || shr_out->type == E_OUT
			|| shr_out->type == E_APPEND)
			return (i);
		if (shr_out->type == E_IN)
			i++;
		shr_out = shr_out->next;
	}
	return (i);
}

void	execute_pipeline_redirection(t_data *data, t_Token *list_token)
{
	t_Token	*curr;
	pid_t	pid[MAX_PIDS];

	data->last = data->nb_cmd;
	curr = list_token;
	data->index = 0;
	while (curr != NULL)
	{
		if (check_here(curr))
			execute_double_in_1(data, &curr);
		else if (check_here_2(curr))
			execute_double_in_1(data, &curr);
		if (check_in(curr))
			execute_in(data, &curr, pid);
		if (check_out(curr))
			execute_redi_out_and_append(data, &curr, pid);
		if (check_pipe(curr))
			execute_pipe(data, &curr, pid);
		if (curr == NULL)
			break ;
		curr = curr->next;
	}
	wait_for_children(data, data->index, pid);
}
