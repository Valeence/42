/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 21:30:35 by vandre            #+#    #+#             */
/*   Updated: 2024/10/28 22:56:08 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	find_player_starting_position(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (data->map_data.map[++i])
	{
		j = -1;
		while (data->map_data.map[i][++j])
			if (ft_strchr(STARTING_CHARS, data->map_data.map[i][j]))
				break ;
		if (data->map_data.map[i][j]
			&& ft_strchr(STARTING_CHARS, data->map_data.map[i][j]))
			break ;
	}
	data->map_data.starting_position.line = i;
	data->map_data.starting_position.col = j;
	data->map_data.starting_pos_char = data->map_data.map[i][j];
	data->map_data.map[i][j] = '0';
	return ;
}

int	check_for_inflection_point(int i, int j, t_data *data)
{
	int	in;
	int	out;

	if (data->map_data.map[i - 1][j] == 'x')
		in = UP;
	else
		in = DOWN;
	while (data->map_data.map[i][++j] == 'x')
		continue ;
	if (data->map_data.map[i - 1][j - 1] == 'x')
		out = UP;
	else
		out = DOWN;
	if (in != out)
		return (1);
	return (0);
}

void	check_player_is_inside_map(t_data *data)
{
	int	i;
	int	j;
	int	intersection_count;

	intersection_count = 0;
	i = data->map_data.starting_position.line;
	j = data->map_data.starting_position.col;
	while (data->map_data.map[i][++j])
	{
		if (data->map_data.map[i][j] != 'x')
			continue ;
		if (data->map_data.map[i][j] == 'x'
			&& data->map_data.map[i][j + 1] != 'x')
			intersection_count++;
		else
		{
			intersection_count += check_for_inflection_point(i, j, data);
			while (data->map_data.map[i][++j] == 'x')
				continue ;
		}
	}
	if (intersection_count % 2 == 0)
		print_err_exit(PLAYER_OFF_MAP, data);
	return ;
}

void	revert_contour_chars_to_walls(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (data->map_data.map[++i])
	{
		j = -1;
		while (data->map_data.map[i][++j])
			if (data->map_data.map[i][j] == 'x')
				data->map_data.map[i][j] = '1';
	}
}

void	check_player_position(t_data *data)
{
	find_player_starting_position(data);
	check_player_is_inside_map(data);
	revert_contour_chars_to_walls(data);
	return ;
}
