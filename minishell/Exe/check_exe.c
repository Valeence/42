/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_exe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zachamou <zachamou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 00:35:59 by zachamou          #+#    #+#             */
/*   Updated: 2024/06/27 21:07:58 by zachamou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/MiniShell.h"

bool	check_here_2(t_Token *curr)
{
	if (curr->type == E_HEREDOC && curr->next != NULL
		&& curr->next->type == E_OEF_HERE)
		return (true);
	return (false);
}

bool	check_in(t_Token *curr)
{
	if (curr != NULL && curr->next != NULL && curr->next->next != NULL
		&& ((curr->type == E_WORD && curr->next->type == E_IN
				&& curr->next->next->type == E_FILE) || (curr->type == E_IN
				&& curr->next->type == E_FILE
				&& curr->next->next->type == E_WORD)))
		return (true);
	return (false);
}

bool	check_out(t_Token *curr)
{
	if (curr != NULL && curr->next != NULL && curr->next->next != NULL
		&& ((curr->type == E_WORD && search_redi(curr)
				&& curr->next->next->type == E_FILE) || (curr->type == E_PIPE
				&& curr->next->type == E_WORD && search_redi(curr->next)
				&& curr->next->next->next != NULL
				&& curr->next->next->next->type == E_FILE)
			|| (curr->type == E_OEF_HERE && search_redi(curr))))
		return (true);
	return (false);
}

bool	check_check_in_check(t_Token *curr)
{
	if (curr->type == E_APPEND)
		return (true);
	if (curr->type == E_OUT)
		return (true);
	if (curr->type == E_IN)
		return (true);
	return (false);
}

bool	check_pipe(t_Token *curr)
{
	if ((curr != NULL && curr->next != NULL && curr->next->next != NULL
			&& curr->type == E_WORD && curr->next->type == E_PIPE
			&& curr->next->next->type == E_WORD) || (curr != NULL
			&& curr->type == E_PIPE && curr->next != NULL
			&& curr->next->type == E_WORD && curr->next->next != NULL
			&& (check_check_in_check(curr->next->next) == true))
		|| (curr != NULL && curr->type == E_WORD && curr->next == NULL))
		return (true);
	return (false);
}
