/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 18:11:53 by vandre            #+#    #+#             */
/*   Updated: 2024/01/23 16:40:09 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	init_mlx(t_game *game)
{
	game->img.floor = mlx_xpm_file_to_image(game->mlx, "./Asset/grass.xpm",
			&game->width, &game->height);
	game->img.wall = mlx_xpm_file_to_image(game->mlx, "./Asset/treegrass.xpm",
			&game->width, &game->height);
	game->img.coin = mlx_xpm_file_to_image(game->mlx, "./Asset/coin.xpm",
			&game->width, &game->height);
	game->img.exit = mlx_xpm_file_to_image(game->mlx, "./Asset/exit.xpm",
			&game->width, &game->height);
	game->img.player = mlx_xpm_file_to_image(game->mlx, "./Asset/player.xpm",
			&game->width, &game->height);
	if (!game->img.floor || !game->img.wall || !game->img.coin
		|| !game->img.exit || !game->img.player)
	{
		ft_printf("Error\nImage not init\n");
		close_game(game);
		exit (1);
	}
}

void	print_img(t_game *game, char c, int x, int y)
{
	if (c == '0')
		mlx_put_image_to_window(game->mlx, game->win, game->img.floor,
			x * 64, y * 64);
	if (!game->img.floor)
		exit (1);
	if (c == '1')
		mlx_put_image_to_window(game->mlx, game->win, game->img.wall,
			x * 64, y * 64);
	if (!game->img.wall)
		exit (1);
	if (c == 'C')
		mlx_put_image_to_window(game->mlx, game->win, game->img.coin,
			x * 64, y * 64);
	if (!game->img.coin)
		exit (1);
	if (c == 'E')
		mlx_put_image_to_window(game->mlx, game->win, game->img.exit,
			x * 64, y * 64);
	if (!game->img.exit)
		exit (1);
	if (c == 'P')
		mlx_put_image_to_window(game->mlx, game->win, game->img.player,
			x * 64, y * 64);
	if (!game->img.player)
		exit (1);
}

void	print_mlx(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (game->mlx_map[y])
	{
		while (game->mlx_map[y][x])
		{
			if (game->mlx_map[y][x] == 'P')
				print_img(game, 'P', x, y);
			if (game->mlx_map[y][x] == '0')
				print_img(game, '0', x, y);
			if (game->mlx_map[y][x] == '1')
				print_img(game, '1', x, y);
			if (game->mlx_map[y][x] == 'C')
				print_img(game, 'C', x, y);
			if (game->mlx_map[y][x] == 'E')
				print_img(game, 'E', x, y);
		x++;
		}
	x = 0;
	y++;
	}
}

void	free_image(t_game *game)
{
	if (game->img.floor)
		mlx_destroy_image(game->mlx, game->img.floor);
	if (game->img.wall)
		mlx_destroy_image(game->mlx, game->img.wall);
	if (game->img.coin)
		mlx_destroy_image(game->mlx, game->img.coin);
	if (game->img.exit)
		mlx_destroy_image(game->mlx, game->img.exit);
	if (game->img.player)
		mlx_destroy_image(game->mlx, game->img.player);
}

void	close_game(t_game *game)
{
	int	y;

	if (game == NULL)
		return ;
	y = 0;
	while (y < game->free_height)
	{
		if (game->mlx_map[y])
			free(game->mlx_map[y]);
		if (game->map[y])
			free(game->map[y]);
		y++;
	}
	free_image(game);
	mlx_clear_window(game->mlx, game->win);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	free(game->mlx_map);
	free(game->map);
}
