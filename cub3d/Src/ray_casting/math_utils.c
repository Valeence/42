/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 23:28:15 by vandre            #+#    #+#             */
/*   Updated: 2024/10/28 23:28:33 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	calc_ray_side_distance_and_next_block_step(t_data *data)
{
	if (data->ray.ray_dir_x < 0)
	{
		data->ray.step_x = -1;
		data->ray.side_dist_x = (data->ray.pos_x
				- data->ray.map_x) * data->ray.delta_dist_x;
	}
	else
	{
		data->ray.step_x = 1;
		data->ray.side_dist_x = (data->ray.map_x
				+ 1.0 - data->ray.pos_x) * data->ray.delta_dist_x;
	}
	if (data->ray.ray_dir_y < 0)
	{
		data->ray.step_y = -1;
		data->ray.side_dist_y = (data->ray.pos_y
				- data->ray.map_y) * data->ray.delta_dist_y;
	}
	else
	{
		data->ray.step_y = 1;
		data->ray.side_dist_y = (data->ray.map_y
				+ 1.0 - data->ray.pos_y) * data->ray.delta_dist_y;
	}
}

void	calc_perp_wall_dist_from_camera_plane(t_data *data)
{
	if (data->ray.side == 0)
		data->ray.perp_wall_dist = (data->ray.map_x
				- data->ray.pos_x + (1 - data->ray.step_x)
				/ 2) / data->ray.ray_dir_x;
	else
		data->ray.perp_wall_dist = (data->ray.map_y
				- data->ray.pos_y + (1 - data->ray.step_y)
				/ 2) / data->ray.ray_dir_y;
}

void	dda_loop_with_check_hit(t_data *data)
{
	while (data->ray.hit == 0)
	{
		if (data->ray.side_dist_x < data->ray.side_dist_y)
		{
			data->ray.side_dist_x += data->ray.delta_dist_x;
			data->ray.map_x += data->ray.step_x;
			data->ray.side = 0;
		}
		else
		{
			data->ray.side_dist_y += data->ray.delta_dist_y;
			data->ray.map_y += data->ray.step_y;
			data->ray.side = 1;
		}
		if (data->map_data.map[data->ray.map_x][data->ray.map_y] == '1')
			data->ray.hit = 1;
	}
}
