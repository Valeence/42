/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_utilis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zachamou <zachamou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 23:21:45 by zachamou          #+#    #+#             */
/*   Updated: 2024/06/28 00:49:38 by zachamou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/MiniShell.h"

bool	shr_out_in_redi_in_for_stop(t_Token *curr)
{
	t_Token	*tmp;
	int		flag;
	int		flag2;

	tmp = curr;
	flag = 0;
	flag2 = 0;
	while (tmp && tmp->next)
	{
		if (tmp->type == E_PIPE)
		{
			flag++;
			while (tmp && tmp->next)
			{
				if (tmp->type == E_OUT || tmp->type == E_APPEND
					|| tmp->type == E_IN)
					flag2++;
				if (flag > 0 && flag2 > 0)
					return (true);
				tmp = tmp->next;
			}
		}
		tmp = tmp->next;
	}
	return (false);
}

bool	shr_out_in_redi_3(t_Token *curr)
{
	t_Token	*shr_out;

	shr_out = curr;
	while (shr_out)
	{
		if (shr_out->type == E_PIPE)
			return (false);
		if (shr_out->type == E_OUT || shr_out->type == E_APPEND)
			return (true);
		shr_out = shr_out->next;
	}
	return (false);
}

void	free_for_exe(t_data *data, t_Token *curr)
{
	(void)curr;
	if (data->data2->nb_file_out != -1)
		close_fd_out(data);
	if (data->data2->nb_file_in != -1)
		close_fd_in(data);
	if (data->cmd[0] != NULL && data->cmd[0][0] != '\0')
		ft_free_tabtab(data->cmd);
	if (data->cmd[0] && data->cmd[0][0] != '\0')
		ft_free_tabtab(data->cmd);
	ft_free_tabtab(data->envp);
	free(data->home);
	free(data->path_exe);
	free_token(data->list_token_tmp);
}

void	close_fd_in(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->data2->nb_file_in)
	{
		close(data->data2->in_fd[i]);
		i++;
	}
	free(data->data2->in_fd);
}

void	ft_redi_out_bf_pipe(t_data *data)
{
	close(data->pipe_fd[1]);
	dup2(data->pipe_fd[0], STDIN_FILENO);
	close(data->pipe_fd[0]);
}
