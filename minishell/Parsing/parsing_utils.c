/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zachamou <zachamou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 02:39:44 by zachamou          #+#    #+#             */
/*   Updated: 2024/06/27 23:29:02 by zachamou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/MiniShell.h"

int	parentheses_check(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '(' || str[i] == ')')
			return (ft_printf(2, "Syntax error\n"), 0);
		i++;
	}
	return (1);
}
