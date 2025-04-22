/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zachamou <zachamou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:41:48 by vandre            #+#    #+#             */
/*   Updated: 2024/06/28 01:42:25 by zachamou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/MiniShell.h"
#define MAX_ARGS 128

int	check_flag(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '-')
	{
		i++;
		while (str[i] == 'n')
			i++;
		if (str[i] == ' ' || str[i] == '\t' || str[i] == '\0')
			return (1);
	}
	return (0);
}

int	ft_echo(t_data *data, t_Token *curr)
{
	char	**args;
	int		i;
	int		flag;

	args = ft_split_quoted_echo(curr->token_str);
	if (!args)
		return (-1);
	flag = 0;
	if (args[1])
		flag = check_flag(args[1]);
	i = 1 + flag;
	while (args[i])
	{
		process_arg(args[i], data);
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!flag)
		write(1, "\n", 1);
	i = 0;
	while (args[i])
		free(args[i++]);
	free(args);
	return (1);
}
