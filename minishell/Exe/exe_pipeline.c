/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_pipeline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zack <zack@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 00:21:23 by zachamou          #+#    #+#             */
/*   Updated: 2024/06/19 17:22:02 by zack             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/MiniShell.h"
#include <fcntl.h>

void	create_pipe(int pipe_fd[2], int i, int last)
{
	if (i < (last - 1))
	{
		if (pipe(pipe_fd) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
	}
}

void	close_pipes_in_parent(int i, t_data *data, int *input_fd)
{
	if (i != data->first)
		close(*input_fd);
	if (i < data->last)
	{
		close(data->pipe_fd[1]);
		*input_fd = data->pipe_fd[0];
	}
}

void	exe_pipe(t_data *data, t_Token *curr)
{
	data->path_exe = ft_get_reading(data, curr);
	if (!data->path_exe)
		ft_no_patch(data);
	if (execve(data->path_exe, data->cmd, data->envp) == -1)
		free_for_exe_exit(data, data->list_token_tmp);
	free_for_exe(data, data->list_token_tmp);
}

void	pipe_fd(t_data *data, int val)
{
	if (val == 1)
	{
		dup2(data->pipe_fd[0], STDIN_FILENO);
		close(data->pipe_fd[1]);
		close(data->pipe_fd[0]);
	}
	else
	{
		dup2(data->pipe_fd[1], STDOUT_FILENO);
		close(data->pipe_fd[0]);
		close(data->pipe_fd[1]);
	}
}

pid_t	fork_process_pipe(int i, t_data *data, t_Token *curr)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (data->data2->pipe_bf_redi == 1)
			pipe_fd(data, 1);
		else if ((i != data->first))
		{
			dup2(data->input_fd, STDIN_FILENO);
			close(data->input_fd);
		}
		if (i < data->last)
			pipe_fd(data, 2);
		if (check_builtins(data, curr, data->envp) == 0)
		{
			free_token(data->list_token_tmp);
			exit(0);
		}
		exe_pipe(data, curr);
		free_for_exe(data, curr);
	}
	return (pid);
}
