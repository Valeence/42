/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 16:08:29 by vandre            #+#    #+#             */
/*   Updated: 2024/01/12 16:39:31 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	flood_fill(t_game *game, int x, int y)
{
	if (game->map[y][x] == '1' || game->map[y][x] == 'V'
			|| x >= game->width || y >= game->height
			|| x < 0 || y < 0)
		return (0);
	if (game->map[y][x] == 'E' && game->check_exit == 0)
	{
		game->check_exit++;
	}
	if (game->map[y][x] == 'E' && game->check_exit == 1)
		return (0);
	if (game->map[y][x] == 'C')
		game->check_coin++;
	game->map[y][x] = 'V';
	if (flood_fill(game, x + 1, y) || flood_fill(game, x - 1, y)
		|| flood_fill(game, x, y + 1) || flood_fill(game, x, y - 1))
		return (1);
	return (0);
}

void	check_path(t_game *game)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (game->map[j])
	{
		i = 0;
		while (game->map[j][i])
		{
			if (game->map[j][i] == 'P')
			{
				game->pos_x = i;
				game->pos_y = j;
			}
			if (game->map[j][i] == 'E')
			{
				game->exit_x = i;
				game->exit_y = j;
			}
			i++;
		}
	j++;
	}
	flood_fill(game, game->pos_x, game->pos_y);
}
