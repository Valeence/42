/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 21:30:37 by vandre            #+#    #+#             */
/*   Updated: 2024/10/28 22:56:28 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	find_longest_line_length(char **map)
{
	int	max_length;
	int	line_length;
	int	i;

	max_length = 0;
	i = -1;
	while (map[++i])
	{
		line_length = (int) ft_strlen(map[i]);
		if (line_length > max_length)
			max_length = line_length;
	}
	return (max_length);
}
