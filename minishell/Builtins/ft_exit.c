/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zachamou <zachamou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 22:40:48 by vandre            #+#    #+#             */
/*   Updated: 2024/06/28 02:11:30 by zachamou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/MiniShell.h"

bool	is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < 48 || str[i] > 57)
			return (false);
		i++;
	}
	return (true);
}

void	exit_code_atoi(t_data *data, char **str)
{
	int	code;

	code = ft_atoi(str[1]);
	if (code > 255)
		code = 255;
	data->statusp = code;
}

void	exit_code_atoi_2(t_data *data)
{
	int	code;

	ft_printf(2, "bash: exit: too many argument");
	code = 1;
	data->statusp = code;
}

void	ft_exit(t_data *data, t_Token *curr)
{
	char	**str;

	ft_printf(2, "exit\n");
	str = ft_split(curr->token_str, ' ');
	if (str != NULL && str[1] != NULL && str[2] == NULL)
	{
		if (is_digit(str[1]) == false)
		{
			ft_printf(2, "bash: exit: %s: numeric argument required", str[1]);
			data->statusp = 2;
		}
	}
	else if (str != NULL && str[1] != NULL)
		exit_code_atoi(data, str);
	else if (str[0] != NULL && str[1] != NULL && str[2] != NULL)
		exit_code_atoi_2(data);
	free_token(data->list_token_tmp);
	ft_free_tabtab(data->envp);
	free(data->home);
	ft_free_tabtab(str);
	free(data->data2);
	exit(data->statusp);
}
