/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 18:07:04 by vandre            #+#    #+#             */
/*   Updated: 2024/10/28 22:50:48 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	destroy(t_data *data)
{
	printf("Closing the game...\n");
	mlx_loop_end(data->mlx.pointer);
	mlx_clear_window(data->mlx.pointer, data->mlx.window);
	mlx_destroy_image(data->mlx.pointer, data->mlx.img.pointer);
	mlx_destroy_window(data->mlx.pointer, data->mlx.window);
	mlx_destroy_display(data->mlx.pointer);
	free(data->mlx.pointer);
	free_data(data);
	exit (0);
}
