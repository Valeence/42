/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 23:21:09 by vandre            #+#    #+#             */
/*   Updated: 2024/10/28 23:29:00 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	render(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			data->mlx.img.data[i * WIDTH + j] = data->ray.buf[i][j];
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(data->mlx.pointer,
		data->mlx.window, data->mlx.img.pointer, 0, 0);
}

int	raycasting(t_data *data)
{
	calc_raycasting(data, 0);
	render(data);
	return (0);
}
