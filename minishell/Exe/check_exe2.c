/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_exe2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zachamou <zachamou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 21:07:46 by zachamou          #+#    #+#             */
/*   Updated: 2024/06/27 21:08:10 by zachamou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/MiniShell.h"

bool	check_here(t_Token *curr)
{
	if (curr->type == E_WORD && curr->next != NULL
		&& curr->next->type == E_HEREDOC && curr->next->next != NULL
		&& curr->next->next->type == E_OEF_HERE)
		return (true);
	return (false);
}
