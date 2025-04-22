/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zachamou <zachamou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 03:14:52 by zachamou          #+#    #+#             */
/*   Updated: 2024/06/28 01:05:03 by zachamou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/MiniShell.h"

void	ft_redi_here_doc(t_data *data)
{
	printf("%s", data->str_here);
	free(data->str_here);
	close_fd_out(data);
	free_token(data->curr_here_tmp);
	ft_free_tabtab(data->envp);
	free(data->home);
	exit(EXIT_SUCCESS);
}

void	exe_bull(t_data *data)
{
	free_for_exe(data, data->list_token_tmp);
	close_fd_out(data);
	ft_free_tabtab(data->envp);
	free(data->home);
	exit(EXIT_SUCCESS);
}

void	get_get(t_data *data, t_Token *curr)
{
	data->path_exe = ft_get_reading(data, curr);
	if (data->path_exe == NULL)
	{	
		free(data->data2->output_fd);
		ft_no_patch(data);
	}
}

void	erro_exe(t_data *data, t_Token *curr)
{
	(void)curr;
	close_fd_out(data);
	free_token(data->list_token_tmp);
	exit(127);
}

pid_t	fork_process_redi_out(t_data *data, t_Token *curr)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		data->data2->output_fd = malloc(data->data2->nb_file_out * sizeof(int));
		if (data->redi_out_bf_pipe == 1)
		{
			dup2(data->input_fd, STDIN_FILENO);
			close(data->input_fd);
		}
		if (data->data2->redi_and_here == false)
			get_get(data, curr);
		data->data2->output_fd = creat_fd_out(data, curr);
		dup2(data->data2->output_fd[data->data2->nb_file_out - 1],
			STDOUT_FILENO);
		if (data->data2->redi_and_here == true)
			ft_redi_here_doc(data);
		if (check_builtins(data, curr, data->envp) == 0)
			exe_bull(data);
		if (execve(data->path_exe, data->cmd, data->envp) == -1)
			erro_exe(data, data->list_token_tmp);
		free_for_exe(data, curr);
	}
	return (pid);
}
