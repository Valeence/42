/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 23:03:47 by vandre            #+#    #+#             */
/*   Updated: 2024/10/28 23:38:25 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	open_window(t_data *data)
{
	data->mlx.window = mlx_new_window(data->mlx.pointer, WIDTH,
			HEIGHT, "CUBE3D");
	if (data->mlx.window == NULL)
		print_err_exit(MLX_ERROR, data);
}

void	set_hooks(t_data *data)
{
	mlx_hook(data->mlx.window, DestroyNotify, NoEventMask, destroy, data);
	mlx_hook(data->mlx.window, KeyPress, KeyPressMask, \
											keystrokes_management, data);
	mlx_loop_hook(data->mlx.pointer, &raycasting, data);
	return ;
}
