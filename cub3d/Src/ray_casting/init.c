/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 23:22:35 by vandre            #+#    #+#             */
/*   Updated: 2024/10/28 23:27:33 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	initial_calculation(t_data *data, int x)
{
	data->ray.camera_x = 2 * x / (double)WIDTH - 1;
	data->ray.ray_dir_x = data->ray.dir_x
		+ data->ray.plane_x * data->ray.camera_x;
	data->ray.ray_dir_y = data->ray.dir_y
		+ data->ray.plane_y * data->ray.camera_x;
	data->ray.map_x = (int)data->ray.pos_x;
	data->ray.map_y = (int)data->ray.pos_y;
	data->ray.delta_dist_x = fabs(1 / data->ray.ray_dir_x);
	data->ray.delta_dist_y = fabs(1 / data->ray.ray_dir_y);
	data->ray.hit = 0;
}
