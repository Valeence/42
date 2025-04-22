/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 23:36:45 by vandre            #+#    #+#             */
/*   Updated: 2024/10/28 23:37:03 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	free_map_data(t_map_data *map)
{
	if (map->input_fd && !map->finished_reading_file)
	{
		ft_free_ptr((void *)&map->line);
		map->line = get_next_line(map->input_fd);
		while (map->line)
		{
			ft_free_ptr((void *)&map->line);
			map->line = get_next_line(map->input_fd);
		}
		ft_free_ptr((void *)&map->line);
	}
	close(map->input_fd);
	ft_free_ptr((void *)&map->texture_paths[NO]);
	ft_free_ptr((void *)&map->texture_paths[SO]);
	ft_free_ptr((void *)&map->texture_paths[EA]);
	ft_free_ptr((void *)&map->texture_paths[WE]);
	ft_free_ptr((void *)&map->line);
	ft_free_arr((void *)&map->map);
	return ;
}

void	free_data(t_data *data)
{
	int	i;

	free_map_data(&data->map_data);
	i = -1;
	if (data->ray.texture)
	{
		while (++i < NB_OF_TEXTURES)
			ft_free_ptr((void *)&data->ray.texture[i]);
		ft_free_ptr((void *)&data->ray.texture);
	}
	if (data->map_data.line)
		ft_free_ptr((void *)data->map_data.line);
	return ;
}
