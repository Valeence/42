/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:43:31 by vandre            #+#    #+#             */
/*   Updated: 2024/06/11 04:56:26 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/MiniShell.h"

int	ft_pwd(t_data *data)
{
	char	path[1024];

	(void)data;
	if (getcwd(path, sizeof(path)) != NULL)
		printf("%s\n", path);
	else
	{
		perror("getcwd() error");
		return (0);
	}
	return (1);
}
