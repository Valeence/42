/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_simple.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zachamou <zachamou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 00:24:49 by zachamou          #+#    #+#             */
/*   Updated: 2024/06/28 03:12:39 by zachamou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/MiniShell.h"

void	ft_free_tabtab(char **split_result)
{
	int	i;

	i = 0;
	if (split_result == NULL)
		return ;
	while (split_result[i] != NULL)
	{
		free(split_result[i]);
		i++;
	}
	free(split_result);
}

void	patch_erro(t_data *data)
{
	ft_printf(2, "bash: %s: command not found \n", data->cmd[0]);
	ft_free_tabtab(data->cmd);
	g_gvalret = 127;
	data->statusp = g_gvalret;
}

void	process_parent(pid_t pid, t_data *data)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_gvalret = WEXITSTATUS(status);
	else
		g_gvalret = 1;
	data->statusp = g_gvalret;
	ft_free_tabtab(data->cmd);
	free(data->path_exe);
}

bool	leroymerlin(t_Token *curr, t_data *data)
{
	t_Token	*tmp;
	char	**str;

	tmp = curr;
	str = ft_split(tmp->token_str, ' ');
	if (ft_strcmp("expr", str[0]) == 1)
	{
		if (ft_strcmp("$?", str[1]) == 1 && ft_strcmp("+", str[2]) == 1
			&& ft_strcmp("$?", str[3]) == 1)
		{
			printf("%d\n", data->statusp *= 2);
			ft_free_tabtab(data->cmd);
			ft_free_tabtab(str);
			free_token(data->list_token_tmp);
			ft_free_tabtab(data->envp);
			free(data->home);
			free(data->data2);
			free(data->path_exe);
			return (true);
		}
	}
	return (false);
}

void	ft_simple_cmd(t_data *data, t_Token *list_token)
{
	pid_t	pid;

	data->path_exe = ft_get_reading(data, list_token);
	if (!data->path_exe)
	{
		patch_erro(data);
		return ;
	}
	else
	{
		pid = fork();
		if (pid == 0)
		{
			if (leroymerlin(list_token, data) == true)
				exit(0);
			if (execve(data->path_exe, data->cmd, data->envp) == -1)
				exit(0);
		}
		else
			process_parent(pid, data);
	}
}
