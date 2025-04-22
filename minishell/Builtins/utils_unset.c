/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zachamou <zachamou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 01:22:11 by vandre            #+#    #+#             */
/*   Updated: 2024/06/27 23:39:20 by zachamou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/MiniShell.h"

void	aff_exit_code(t_data *data)
{
	char	*str;

	str = NULL;
	str = ft_itoa(data->statusp);
	write(1, str, ft_strlen(str));
	free(str);
}

char	**create_new_env(int env_size)
{
	char	**new_env;

	new_env = malloc(sizeof(char *) * env_size);
	if (!new_env)
		return (NULL);
	return (new_env);
}

int	*init_vars(void)
{
	int	*vars;

	vars = malloc(5 * sizeof(int));
	if (!vars)
		return (NULL);
	vars[0] = 0;
	vars[1] = 0;
	vars[2] = 0;
	vars[3] = 0;
	vars[4] = 0;
	return (vars);
}
