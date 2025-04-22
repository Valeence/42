/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zachamou <zachamou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 23:22:19 by zachamou          #+#    #+#             */
/*   Updated: 2024/06/28 00:38:09 by zachamou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/MiniShell.h"

void	error_exe_in(char *filename, t_data *data)
{
	(void)data;
	close_fd_in(data);
	printf("bash: %s: no such file or directoryx\n", filename);
	if (data->cmd[0] != NULL && data->cmd[0][0] != '\0')
		ft_free_tabtab(data->cmd);
	ft_free_tabtab(data->envp);
	free(data->home);
	free(data->path_exe);
	free_token(data->list_token_tmp);
	free(data->data2);
	g_gvalret = 1;
	exit(126);
}

void	creat_fd_in_if(t_data *data, t_Token *curr, int i)
{
	t_Token	*tmp;

	tmp = curr;
	tmp->next->file = ft_split(tmp->next->token_str, ' ');
	data->data2->in_fd[i] = open(tmp->next->file[0], O_RDONLY);
	if (data->data2->in_fd[i] == -1)
		error_exe_in(tmp->next->file[0], data);
	if (tmp->next->file[1] && tmp->next->file[1][0] != '\0')
		data->cmd = copy_array_arrays(tmp->next->file);
	ft_free_tabtab(tmp->next->next->file);
}

void	creat_fd_in_else(t_data *data, t_Token *curr, int i)
{
	t_Token	*tmp;

	tmp = curr;
	tmp->next->next->file = ft_split(tmp->next->next->token_str, ' ');
	data->data2->in_fd[i] = open(tmp->next->next->file[0], O_RDONLY);
	if (data->data2->in_fd[i] == -1)
		error_exe_in(tmp->next->next->file[0], data);
	if (tmp->next->next->file[1] && tmp->next->next->file[1][0] != '\0')
		data->cmd = copy_array_arrays(tmp->next->next->file);
	ft_free_tabtab(tmp->next->next->file);
}

void	creat_fd_in_no_cmd(t_data *data, t_Token *curr, int i)
{
	t_Token	*tmp;

	tmp = curr;
	tmp->next->file = ft_split(tmp->next->token_str, ' ');
	data->data2->in_fd[i] = open(tmp->next->file[0], O_RDONLY);
	if (data->data2->in_fd[i] == -1)
		error_exe_in(tmp->next->file[0], data);
}

int	*creat_fd_in(t_data *data, t_Token *curr)
{
	int		i;
	t_Token	*tmp;

	tmp = curr;
	i = 0;
	while (i < data->data2->nb_file_in)
	{
		if (tmp->next->type == E_FILE)
		{
			creat_fd_in_no_cmd(data, tmp, i);
			i++;
		}
		else if (tmp->next->next->type == E_WORD)
		{
			creat_fd_in_if(data, tmp, i);
			i++;
		}
		else if (tmp->next->next->type == E_FILE)
		{
			creat_fd_in_else(data, tmp, i);
			i++;
		}
		tmp = tmp->next->next;
	}
	return (data->data2->in_fd);
}
