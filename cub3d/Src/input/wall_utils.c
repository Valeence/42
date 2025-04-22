/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 21:30:40 by vandre            #+#    #+#             */
/*   Updated: 2024/10/28 22:57:16 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool	check_tile_locale(t_position next_move, char **map)
{
	int		i;
	int		j;

	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
			if (map[(next_move.line - 1) + i][(next_move.col - 1) + j] == ' ')
				return (true);
	}
	return (false);
}

bool	is_valid_move_direction(t_position position, char **map)
{
	if (map[position.line][position.col] != '1')
		return (false);
	return (check_tile_locale(position, map));
}

t_position	find_next_move(t_position *curr_pos, int direction)
{
	if (direction == NO)
		return (t_poss_create_tuple(curr_pos->line - 1, curr_pos->col));
	else if (direction == EA)
		return (t_poss_create_tuple(curr_pos->line, curr_pos->col + 1));
	else if (direction == SO)
		return (t_poss_create_tuple(curr_pos->line + 1, curr_pos->col));
	else
		return (t_poss_create_tuple(curr_pos->line, curr_pos->col - 1));
}

bool	has_neighbouring_one(t_position pos, char **map)
{
	return (map[pos.line - 1][pos.col] == '1'
		|| map[pos.line][pos.col + 1] == '1'
		|| map[pos.line + 1][pos.col] == '1'
		|| map[pos.line][pos.col - 1] == '1');
}

t_position	find_x_pos(t_position curr_pos, char **map)
{
	if (map[curr_pos.line - 1][curr_pos.col] == 'x')
		return (t_poss_create_tuple(curr_pos.line - 1, curr_pos.col));
	if (map[curr_pos.line][curr_pos.col + 1] == 'x')
		return (t_poss_create_tuple(curr_pos.line, curr_pos.col + 1));
	if (map[curr_pos.line + 1][curr_pos.col] == 'x')
		return (t_poss_create_tuple(curr_pos.line + 1, curr_pos.col));
	if (map[curr_pos.line][curr_pos.col - 1] == 'x')
		return (t_poss_create_tuple(curr_pos.line, curr_pos.col - 1));
	return (t_poss_create_tuple(0, 0));
}
