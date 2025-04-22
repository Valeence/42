/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zachamou <zachamou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 01:09:53 by zachamou          #+#    #+#             */
/*   Updated: 2024/06/28 00:33:56 by zachamou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/MiniShell.h"

char	*build_executable_path(char *cmd, char *path)
{
	char	*part_path;
	char	*exe;

	part_path = ft_strjoin(path, "/");
	exe = ft_strjoin(part_path, cmd);
	free(part_path);
	if (access(exe, F_OK | X_OK) == 0)
	{
		return (exe);
	}
	free(exe);
	return (NULL);
}

char	*find_path(char *cmd, char **ev)
{
	char	**allpaths;
	char	*exe;
	int		i;

	i = 0;
	while (ev[i])
	{
		if (ft_strnstr(ev[i], "PATH=", 5) != NULL)
			break ;
		i++;
	}
	allpaths = ft_split((ev[i] + 5), ':');
	i = 0;
	while (allpaths[i])
	{
		exe = build_executable_path(cmd, allpaths[i]);
		if (exe != NULL)
		{
			ft_free_tabtab(allpaths);
			return (exe);
		}
		i++;
	}
	ft_free_tabtab(allpaths);
	return (NULL);
}

char	*ft_get_reading(t_data *data, t_Token *curr)
{
	curr->file = NULL;
	if (curr->type == E_WORD)
		data->cmd = ft_split(curr->token_str, ' ');
	if (curr->type == E_NOT_CMD)
		data->cmd = ft_split(curr->token_str, ' ');
	if (curr->type == E_WORD)
		data->path_exe = find_path(data->cmd[0], data->envp);
	else if (curr->next != NULL && curr->next->next != NULL
		&& curr->next->next->type == E_WORD)
		data->path_exe = find_path(data->cmd[0], data->envp);
	else if (curr->type == E_NOT_CMD)
		data->path_exe = ft_strdup(data->cmd[0]);
	return (data->path_exe);
}
