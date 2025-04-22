/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 23:03:11 by vandre            #+#    #+#             */
/*   Updated: 2024/10/28 23:03:26 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	rotate_camera_direction(double old_dir_x, t_data *data, char dir)
{
	if (dir == 'R')
	{
		data->ray.dir_x = data->ray.dir_x * cos(-data->ray.rot_speed)
			- data->ray.dir_y * sin(-data->ray.rot_speed);
		data->ray.dir_y = old_dir_x * sin(-data->ray.rot_speed)
			+ data->ray.dir_y * cos(-data->ray.rot_speed);
	}
	if (dir == 'L')
	{
		data->ray.dir_x = data->ray.dir_x * cos(data->ray.rot_speed)
			- data->ray.dir_y * sin(data->ray.rot_speed);
		data->ray.dir_y = old_dir_x * sin(data->ray.rot_speed)
			+ data->ray.dir_y * cos(data->ray.rot_speed);
	}
}

static void	rotate_camera_plane(double old_plane_x, t_data *data, char dir)
{
	if (dir == 'R')
	{
		data->ray.plane_x = data->ray.plane_x * cos(-data->ray.rot_speed)
			- data->ray.plane_y * sin(-data->ray.rot_speed);
		data->ray.plane_y = old_plane_x * sin(-data->ray.rot_speed)
			+ data->ray.plane_y * cos(-data->ray.rot_speed);
	}
	if (dir == 'L')
	{
		data->ray.plane_x = data->ray.plane_x * cos(data->ray.rot_speed)
			- data->ray.plane_y * sin(data->ray.rot_speed);
		data->ray.plane_y = old_plane_x * sin(data->ray.rot_speed)
			+ data->ray.plane_y * cos(data->ray.rot_speed);
	}
}

void	rotate_view(int keycode, t_data *data)
{
	double	old_dir_x;
	double	old_plane_x;

	if (keycode == XK_Right)
	{
		old_dir_x = data->ray.dir_x;
		rotate_camera_direction(old_dir_x, data, 'R');
		old_plane_x = data->ray.plane_x;
		rotate_camera_plane(old_plane_x, data, 'R');
	}
	if (keycode == XK_Left)
	{
		old_dir_x = data->ray.dir_x;
		rotate_camera_direction(old_dir_x, data, 'L');
		old_plane_x = data->ray.plane_x;
		rotate_camera_plane(old_plane_x, data, 'L');
	}
}
