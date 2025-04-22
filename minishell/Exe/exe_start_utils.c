/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_start_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zachamou <zachamou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 00:48:50 by zachamou          #+#    #+#             */
/*   Updated: 2024/06/27 21:13:51 by zachamou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/MiniShell.h"

void	execute_double_in_1(t_data *data, t_Token **curr)
{
	int	grab_hd;

	grab_hd = cont_nb_here(*curr);
	data->data2->redi_and_here = shr_out_in_here(*curr);
	lanch_her(*curr, data);
	push_position(curr, grab_hd);
}

void	execute_in(t_data *data, t_Token **curr, pid_t *pid)
{
	if ((*curr)->next->next->next != NULL && (*curr)->type == E_PIPE
		&& (*curr)->next->type == E_WORD && (*curr)->next->next->type == E_IN
		&& (*curr)->next->next->next->type == E_FILE)
		(*curr) = (*curr)->next;
	data->data2->nb_file_in = cont_nb_in(*curr);
	if (verif_pipe(*curr) == true)
	{
		pid[data->index] = -1;
		data->redi_out_bf_pipe = 1;
		create_pipe(data->pipe_fd, data->index, data->last);
		pid[data->index] = fork_process_redi_in(data, (*curr));
		close_pipes_in_parent(data->index, data, &data->input_fd);
		data->index++;
	}
	else
	{
		pid[data->index] = -1;
		pid[data->index] = fork_process_redi_in(data, (*curr));
		data->index++;
	}
	push_in(curr);
}

void	execute_redi_out_and_append(t_data *data, t_Token **curr, pid_t *pid)
{
	if (((*curr)->type == E_PIPE && (*curr)->next->type == E_WORD
			&& search_redi((*curr)->next))
		&& (*curr)->next->next->next->type == E_FILE)
		(*curr) = (*curr)->next;
	data->data2->nb_file_out = cont_nb_out(*curr);
	if (verif_pipe(*curr) == true)
	{
		data->redi_out_bf_pipe = 1;
		pid[data->index] = -1;
		create_pipe(data->pipe_fd, data->index, data->last);
		pid[data->index] = fork_process_redi_out(data, (*curr));
		close_pipes_in_parent(data->index, data, &data->input_fd);
		data->index++;
		data->data2->pipe_bf_redi = 0;
	}
	else
	{
		pid[data->index] = -1;
		pid[data->index] = fork_process_redi_out(data, (*curr));
		data->index++;
	}
	push_exe(curr, data);
}

void	execute_pipe(t_data *data, t_Token **curr, pid_t *pid)
{
	data->curr_here_tmp = *curr;
	if ((*curr) != NULL && (*curr)->type == E_PIPE && (*curr)->next != NULL
		&& (*curr)->next->type == E_WORD && (*curr)->next->next == NULL)
		(*curr) = (*curr)->next;
	pid[data->index] = -1;
	create_pipe(data->pipe_fd, data->index, data->last);
	pid[data->index] = fork_process_pipe(data->index, data, (*curr));
	close_pipes_in_parent(data->index, data, &data->input_fd);
	data->index++;
	if ((curr != NULL && (*curr)->next != NULL && (*curr)->next->next != NULL
			&& (*curr)->next->next->next != NULL)
		&& ((*curr)->next->next->next->type == E_OUT
			|| (*curr)->next->next->next->type == E_APPEND))
		data->data2->pipe_bf_redi = 1;
	data->redi_out_bf_pipe = 0;
}
