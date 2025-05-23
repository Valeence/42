/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 21:30:28 by vandre            #+#    #+#             */
/*   Updated: 2024/10/28 22:54:00 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	check_for_valid_path(t_data *data)
{
	int	i;
	int	fd;

	if (data->map_data.texture_paths[get_direction_index
			(data->map_data.line[0])] == NULL)
		(data->map_data.params_count)++;
	else
		print_err_exit(REDUNDANT_PARAMETER_FOUND, data);
	i = 2 + jump_spaces(&(data->map_data.line[2]));
	fd = open(&(data->map_data.line[i]), O_RDONLY);
	if (fd == -1)
		print_err_exit(SYSCALL_ERROR, data);
	close(fd);
	data->map_data.texture_paths[get_direction_index(data->map_data.line[0])] = \
		ft_strdup(&(data->map_data.line[i]));
	return ;
}

void	check_duplicate_parameter(t_data *data)
{
	if (data->map_data.colours_rgb[get_colour_index
			(data->map_data.line[0])][0] == -42)
		(data->map_data.params_count)++;
	else
		print_err_exit(REDUNDANT_PARAMETER_FOUND, data);
	return ;
}

void	check_colour_params_count(char **colours_array,
	t_data *data)
{
	int	comma_count;
	int	params_count;
	int	i;

	comma_count = 0;
	i = -1;
	while (data->map_data.line[++i])
		if (data->map_data.line[i] == ',')
			comma_count++;
	if (comma_count != 2)
	{
		ft_free_arr((void *)&colours_array);
		print_err_exit(INVALID_COLOUR_PARAM, data);
	}
	params_count = 0;
	i = -1;
	while (colours_array[++i])
		params_count++;
	if (params_count != 3)
	{
		ft_free_arr((void *)&colours_array);
		print_err_exit(INVALID_COLOUR_PARAM, data);
	}
	return ;
}

void	check_for_valid_colour(t_data *data)
{
	int		i;
	int		colour_code;
	char	**colours_array;

	check_duplicate_parameter(data);
	colours_array = ft_split(&(data->map_data.line[1]), ',');
	check_colour_params_count(colours_array, data);
	i = -1;
	while (colours_array[++i])
	{
		colour_code = convert_colour_to_int(colours_array[i]);
		if (colour_code == -1)
		{
			ft_free_arr((void *)&colours_array);
			print_err_exit(INVALID_COLOUR_PARAM, data);
		}
		data->map_data.colours_rgb[get_colour_index(data->map_data.line[0])][i] \
			= colour_code;
	}
	ft_free_arr((void *)&colours_array);
	return ;
}
