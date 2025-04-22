/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zachamou <zachamou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 01:13:43 by zachamou          #+#    #+#             */
/*   Updated: 2024/06/27 21:10:41 by zachamou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/MiniShell.h"

void	exe_cmd(t_data *data, t_Token *lst_tok)
{
	(void)lst_tok;
	if (execve(data->path_exe, data->cmd, data->envp) == -1)
	{
		ft_free_tabtab(data->cmd);
		free_token(data->list_token_tmp);
		free(data->path_exe);
		free(data->str);
		exit(127);
	}
	ft_free_tabtab(data->cmd);
	free_token(data->list_token_tmp);
	free(data->path_exe);
}

void	erro_in_child(t_data *data, t_Token *curr)
{
	(void)curr;
	ft_printf(2, "bash: %s: command not found \n", data->cmd[0]);
	ft_free_tabtab(data->cmd);
	free_token(data->list_token_tmp);
	free(data->str);
	g_gvalret = 127;
}

void	here_fd_and_exe(t_data *data, t_Token *curr)
{
	close(data->here_fd[1]);
	dup2(data->here_fd[0], STDIN_FILENO);
	close(data->here_fd[0]);
	data->path_exe = ft_get_reading(data, curr);
}

pid_t	execute_command_in_child(t_data *data, t_Token *curr)
{
	pid_t	pid;

	pipe(data->here_fd);
	pid = fork();
	if (pid == 0)
	{
		here_fd_and_exe(data, curr);
		if (!data->path_exe)
		{
			erro_in_child(data, curr);
			g_gvalret = 127;
			return (100);
		}
		exe_cmd(data, curr);
		free(data->str);
	}
	else
		close_or_not(data, pid);
	return (pid);
}

int	fork_here(t_Token *curr, t_data *data, t_here *here)
{
	char	*line;

	data->str = malloc(1);
	data->str[0] = '\0';
	line = NULL;
	while (1)
	{
		line = read_until_delimiter(here);
		if (line == NULL)
			break ;
		concatenate_lines(data, line);
		free(line);
	}
	if (here->exe == 1)
	{
		if (execute_command_in_child(data, curr) == 100)
		{
			g_gvalret = 127;
			return (2);
		}
	}
	free(data->str);
	return (0);
}
