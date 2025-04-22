/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_start.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zachamou <zachamou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 00:27:23 by zachamou          #+#    #+#             */
/*   Updated: 2024/06/28 01:46:04 by zachamou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/MiniShell.h"

bool	shr_out_in_redi(t_Token *curr)
{
	t_Token	*shr_out;

	shr_out = curr;
	while (shr_out != NULL && shr_out->next != NULL)
	{
		if (shr_out->token_str[0] == '|')
			return (true);
		if (shr_out->type == E_OUT || shr_out->type == E_APPEND)
			return (true);
		shr_out = shr_out->next;
	}
	return (false);
}

bool	search_redi(t_Token *curr)
{
	t_Token	*temp;

	temp = curr;
	if (temp->next->type == E_OUT)
		return (true);
	if (temp->next->type == E_APPEND)
		return (true);
	return (false);
}

int	check_builtins(t_data *data, t_Token *curr, char **envp)
{
	if (ft_strcmp(curr->token_str, "echo") == 1)
		ft_echo(data, curr);
	else if ((ft_strcmp(curr->token_str, "cd") == 1))
		ft_cd(curr, data);
	else if (ft_strcmp(curr->token_str, "pwd") == 1)
		ft_pwd(data);
	else if (ft_strcmp(curr->token_str, "export") == 1)
		ft_export(data, curr);
	else if (ft_strcmp(curr->token_str, "unset") == 1)
		ft_unset(data, curr);
	else if (ft_strcmp(curr->token_str, "env") == 1)
		ft_env(envp);
	else if (ft_strcmp(curr->token_str, "exit") == 1)
		ft_exit(data, curr);
	else
		return (1);
	return (0);
}

void	ft_lanch_exe(t_data *data, t_Token *list_token)
{
	int	size;

	size = ft_size_list_token(list_token);
	if (size < 1 && list_token->next == NULL)
	{
		if (check_builtins(data, list_token, data->envp) == 1)
			ft_simple_cmd(data, list_token);
	}
	else
		execute_pipeline_redirection(data, list_token);
}
