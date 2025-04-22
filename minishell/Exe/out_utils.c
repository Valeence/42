/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zachamou <zachamou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 03:18:53 by zachamou          #+#    #+#             */
/*   Updated: 2024/06/27 21:30:07 by zachamou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/MiniShell.h"

void	close_fd_out(t_data *data)
{
	int	i;

	i = 0;
	while (data->data2->output_fd[i] != -1)
	{
		close(data->data2->output_fd[i]);
		i++;
	}
	free(data->data2->output_fd);
}

void	push_to(t_Token *tmp, t_data *data)
{
	data->data2->output_fd = malloc(data->data2->nb_file_out * sizeof(int));
	while (search_redi(tmp) == false)
		tmp = tmp->next;
}
