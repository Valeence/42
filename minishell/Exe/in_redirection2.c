/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_redirection2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zachamou <zachamou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 03:02:08 by zachamou          #+#    #+#             */
/*   Updated: 2024/06/27 21:14:38 by zachamou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/MiniShell.h"

bool	in_file(t_Token *curr)
{
	if (curr != NULL && curr->next != NULL && curr->next->next != NULL
		&& curr->type == E_IN && curr->next->type == E_FILE
		&& curr->next->next->type == E_WORD)
		return (true);
	return (false);
}

bool	in_file_2(t_Token *curr)
{
	if (curr != NULL && curr->next != NULL && curr->next->next != NULL
		&& curr->type == E_IN && curr->next->type == E_FILE
		&& curr->next->next->type == E_WORD)
		return (true);
	return (false);
}

void	bye_bye_in(t_data *data, t_Token *curr)
{
	(void)curr;
	if (data->data2->nb_file_out != 0)
		close_fd_out(data);
	close_fd_in(data);
	if (data->cmd[0] != NULL && data->cmd[0][0] != '\0')
		ft_free_tabtab(data->cmd);
	free(data->path_exe);
	ft_free_tabtab(data->envp);
	free(data->home);
	free_token(data->list_token_tmp);
}
