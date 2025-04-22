/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 17:16:36 by vandre            #+#    #+#             */
/*   Updated: 2024/01/23 16:41:40 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	check_chars(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (game->map[j])
	{
		while (game->map[j][i])
		{
			if (game->map[j][i] != '1' && game->map[j][i] != '0'
				&& game->map[j][i] != 'C' && game->map[j][i] != 'E'
				&& game->map[j][i] != 'P')
				return (ft_printf("Error\nMap need only 1 0 C E P\n"),
					free_map(game));
		i++;
		}
	j++;
	i = 0;
	}
}

void	check_square(t_game *game)
{
	int	j;

	j = 0;
	if (game->height < 3 || game->width < 5
		|| game->height > 15 || game->width > 29)
		return (ft_printf("Error\nSize is not correct\n"),
			free_map(game));
	while (j < game->height)
	{
		if (game->width != (int)ft_strlen_sl(game->map[j]))
			return (ft_printf("Error\nMap need to be a square\n"),
				free_map(game));
		j++;
	}
}

void	check_boundy(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (game->map[j])
	{
		while (game->map[j][i])
		{
			if (game->map[j][i] == 'E')
				game->is_exit++;
			if (game->map[j][i] == 'P')
				game->is_player++;
			if (game->map[j][i] == 'C')
				game->is_coin++;
			if (game->map[0][i] != '1' || game->map[game->height - 1][i] != '1'
				||
				game->map[j][0] != '1' || game->map[j][game->width - 1] != '1')
				return (ft_printf("Error\nWall isn't only 1\n"),
					free_map(game));
			i++;
		}
		j++;
		i = 0;
	}
}

void	check_map(t_game *game)
{
	check_square(game);
	check_chars(game);
	check_boundy(game);
	check_player(game);
	check_exit(game);
	check_coins(game);
	check_path(game);
	if (game->check_exit != 1 || game->check_coin != game->is_coin)
		return (ft_printf("Error\nExit or coins are unreachable\n"),
			free_map(game));
}

int	close_window(t_game *game)
{
	close_game(game);
	exit (1);
}
