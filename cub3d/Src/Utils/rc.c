/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 23:31:21 by vandre            #+#    #+#             */
/*   Updated: 2024/10/28 23:31:47 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	set_facing_direction_vector(t_data *data)
{
	if (data->map_data.starting_pos_char == 'N')
	{
		data->ray.dir_x = -1;
		data->ray.dir_y = 0;
	}
	if (data->map_data.starting_pos_char == 'S')
	{
		data->ray.dir_x = 1;
		data->ray.dir_y = 0;
	}
	if (data->map_data.starting_pos_char == 'E')
	{
		data->ray.dir_x = 0;
		data->ray.dir_y = 1;
	}
	if (data->map_data.starting_pos_char == 'W')
	{
		data->ray.dir_x = 0;
		data->ray.dir_y = -1;
	}
}

void	set_camera_plane_vector(t_data *data)
{
	if (data->map_data.starting_pos_char == 'N')
	{
		data->ray.plane_x = 0;
		data->ray.plane_y = 0.66;
	}
	if (data->map_data.starting_pos_char == 'S')
	{
		data->ray.plane_x = 0;
		data->ray.plane_y = -0.33;
	}
	if (data->map_data.starting_pos_char == 'E')
	{
		data->ray.plane_x = 0.33;
		data->ray.plane_y = 0;
	}
	if (data->map_data.starting_pos_char == 'W')
	{
		data->ray.plane_x = -0.66;
		data->ray.plane_y = 0;
	}
}
