/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 14:11:06 by vandre            #+#    #+#             */
/*   Updated: 2024/01/18 14:32:37 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	game_print_right(t_game *game)
{
	game->mlx_map[game->pos_y][game->pos_x] = '0';
	game->mlx_map[game->pos_y][game->pos_x + 1] = 'P';
	print_img(game, '0', game->pos_x, game->pos_y);
	print_img(game, 'P', game->pos_x + 1, game->pos_y);
	game->pos_x++;
	game->move++;
	ft_printf("move = %d\n", game->move);
}

void	game_print_left(t_game *game)
{
	game->mlx_map[game->pos_y][game->pos_x] = '0';
	game->mlx_map[game->pos_y][game->pos_x - 1] = 'P';
	print_img(game, '0', game->pos_x, game->pos_y);
	print_img(game, 'P', game->pos_x - 1, game->pos_y);
	game->pos_x--;
	game->move++;
	ft_printf("move = %d\n", game->move);
}

void	game_print_up(t_game *game)
{
	game->mlx_map[game->pos_y][game->pos_x] = '0';
	game->mlx_map[game->pos_y - 1][game->pos_x] = 'P';
	print_img(game, '0', game->pos_x, game->pos_y);
	print_img(game, 'P', game->pos_x, game->pos_y - 1);
	game->pos_y--;
	game->move++;
	ft_printf("move = %d\n", game->move);
}

void	game_print_down(t_game *game)
{
	game->mlx_map[game->pos_y][game->pos_x] = '0';
	game->mlx_map[game->pos_y + 1][game->pos_x] = 'P';
	print_img(game, '0', game->pos_x, game->pos_y);
	print_img(game, 'P', game->pos_x, game->pos_y + 1);
	game->pos_y++;
	game->move++;
	ft_printf("move = %d\n", game->move);
}

void	free_map(t_game *game)
{
	int	y;

	y = 0;
	while (y < game->free_height)
	{
		if (game->mlx_map[y])
			free(game->mlx_map[y]);
		if (game->map[y])
			free(game->map[y]);
		y++;
	}
	free(game->mlx_map);
	free(game->map);
	exit(1);
}
