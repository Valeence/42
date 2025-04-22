/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_out.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zachamou <zachamou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 23:27:24 by zachamou          #+#    #+#             */
/*   Updated: 2024/06/27 23:27:15 by zachamou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/MiniShell.h"

void	handle_open_error(int fd, char *filename)
{
	if (fd == -1)
	{
		printf("bash: %s: Permission denied\n", filename);
		g_gvalret = 1;
		exit(1);
	}
}

int	open_append_fd(t_data *data, t_Token *tmp)
{
	if (data->flag_qote == 0)
		return (open(tmp->next->next->file[0], O_CREAT | O_WRONLY | O_TRUNC,
				0644));
	else
		return (open(tmp->next->next->token_str, O_CREAT | O_WRONLY | O_TRUNC,
				0644));
}

int	open_output_fd(t_data *data, t_Token *tmp)
{
	if (data->flag_qote == 0)
		return (open(tmp->next->next->file[0], O_CREAT | O_WRONLY | O_APPEND,
				0644));
	else
		return (open(tmp->next->next->token_str, O_CREAT | O_WRONLY | O_APPEND,
				0644));
}

int	*creat_fd_out(t_data *data, t_Token *curr)
{
	int		i;
	t_Token	*tmp;

	i = 0;
	tmp = curr;
	while (i < data->data2->nb_file_out)
	{
		if (tmp->next->next->type == E_FILE)
		{
			tmp->next->next->file = ft_split(tmp->next->next->token_str, ' ');
			if (tmp->next->type == E_OUT)
				data->data2->output_fd[i] = open_append_fd(data, tmp);
			if (tmp->next->type == E_APPEND)
				data->data2->output_fd[i] = open_output_fd(data, tmp);
			if (data->data2->output_fd[i] == -1)
				handle_open_error(data->data2->output_fd[i],
					tmp->next->next->file[0]);
			if (tmp->next->next->file[1] != NULL
				&& tmp->next->next->file[1][0] != '\0' && data->flag_qote == 0)
				data->cmd = copy_array_arrays(tmp->next->next->file);
			i++;
		}
		tmp = tmp->next->next;
	}
	return (data->data2->output_fd);
}

int	*creat_fd_out_in_in(t_data *data, t_Token *curr)
{
	int		i;
	t_Token	*tmp;

	tmp = curr;
	i = 0;
	while (i < data->data2->nb_file_out)
	{
		if (tmp->next->next->type == E_FILE)
		{
			tmp->next->next->file = ft_split(tmp->next->next->token_str, ' ');
			if (tmp->next->type == E_OUT)
				data->data2->output_fd[i] = open_append_fd(data, tmp);
			if (tmp->next->type == E_APPEND)
				data->data2->output_fd[i] = open_output_fd(data, tmp);
			if (data->data2->output_fd[i] == -1)
				handle_open_error(data->data2->output_fd[i],
					tmp->next->next->file[0]);
			if (tmp->next->next->file[1] != NULL
				&& tmp->next->next->file[1][0] != '\0' && data->flag_qote == 0)
				data->cmd = copy_array_arrays(tmp->next->next->file);
			i++;
		}
		tmp = tmp->next->next;
	}
	return (data->data2->output_fd);
}
