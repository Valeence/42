/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 00:53:22 by vandre            #+#    #+#             */
/*   Updated: 2024/06/11 01:14:34 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/MiniShell.h"

int	*fill_tab(char *str, int i, int *tab)
{
	int	j;

	i += 2;
	j = 0;
	if (!str || !tab)
		return (NULL);
	while (str[i] == ' ')
		i++;
	while (str[i] != ' ' && str[i] != '\0')
	{
		i++;
		j++;
	}
	tab[0] = i;
	tab[1] = j;
	return (tab);
}
