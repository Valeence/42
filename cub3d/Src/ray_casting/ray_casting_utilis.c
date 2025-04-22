/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_utilis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 23:21:59 by vandre            #+#    #+#             */
/*   Updated: 2024/10/28 23:28:56 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	take_tex_num(t_data *data)
{
	if (data->ray.side == 0 && data->ray.ray_dir_x < 0)
		return (0);
	else if (data->ray.side == 0 && data->ray.ray_dir_x >= 0)
		return (2);
	else if (data->ray.side == 1 && data->ray.ray_dir_y >= 0)
		return (1);
	else if (data->ray.side == 1 && data->ray.ray_dir_y < 0)
		return (3);
	return (0);
}

void	clean_buf_with_zero(t_ray *ray)
{
	int	x;
	int	y;

	x = -1;
	while (++x < HEIGHT)
	{
		y = -1;
		while (++y < WIDTH)
			ray->buf[x][y] = 0;
	}
}
