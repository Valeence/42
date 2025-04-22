/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zachamou <zachamou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 02:48:32 by zachamou          #+#    #+#             */
/*   Updated: 2024/06/28 01:05:46 by zachamou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/MiniShell.h"

void	else_for_dup_redi_inin_and_out(t_data *data, t_Token *curr)
{
	push_to(curr, data);
	data->data2->output_fd = creat_fd_out_in_in(data, curr);
	dup2(data->data2->in_fd[data->data2->nb_file_in - 1], STDIN_FILENO);
	dup2(data->data2->output_fd[data->data2->nb_file_out - 1], STDOUT_FILENO);
}

void	exe_bull_in(t_data *data, t_Token *curr)
{
	(void)curr;
	if (data->cmd[0] != NULL && data->cmd[0][0] != '\0')
		ft_free_tabtab(data->cmd);
	free(data->path_exe);
	free_token(data->list_token_tmp);
	ft_free_tabtab(data->envp);
	free(data->home);
	exit(0);
}

void	ft_else_in(t_data *data, t_Token *curr)
{
	data->data2->in_fd = malloc(data->data2->nb_file_in * sizeof(int));
	data->data2->in_fd = creat_fd_in(data, curr);
	if (curr != NULL && curr->next != NULL && (curr->type == E_IN
			&& curr->next->type == E_FILE))
		dup2(data->input_fd, STDIN_FILENO);
	if (shr_out_in_redi_in_for_stop(curr) == true)
	{
		bye_bye_in(data, curr);
		exit(0);
	}
	else if (shr_out_in_redi_3(curr) == true)
		else_for_dup_redi_inin_and_out(data, curr);
	else
		dup2(data->data2->in_fd[data->data2->nb_file_in - 1], STDIN_FILENO);
}

pid_t	fork_process_redi_in(t_data *data, t_Token *curr)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (in_file(curr))
			data->path_exe = ft_get_reading(data, curr->next->next);
		else if (in_file_2(curr) || curr->type == E_WORD)
			data->path_exe = ft_get_reading(data, curr);
		if (!data->path_exe)
		{
			free(data->data2->in_fd);
			ft_no_patch(data);
		}
		if (data->redi_out_bf_pipe == 1 && !shr_out_in_redi_in_for_stop(curr))
			ft_redi_out_bf_pipe(data);
		else
			ft_else_in(data, curr);
		if (!check_builtins(data, curr, data->envp))
			exe_bull_in(data, curr);
		if (execve(data->path_exe, data->cmd, data->envp) == -1)
			free_for_exe_exit(data, curr);
		free_for_exe(data, curr);
	}
	return (pid);
}
