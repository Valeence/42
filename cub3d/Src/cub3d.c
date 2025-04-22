/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.C                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 23:01:00 by vandre            #+#    #+#             */
/*   Updated: 2024/10/28 23:01:24 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_data(t_data *data)
{
	null_mallocable_pointers(data);
	init_map_data(&data->map_data);
}

int	main(int argc, char **argv)
{
	t_data	data;

	init_data(&data);
	validate_args(argc, argv, &data);
	validate_input_file(&data);
	init_mlx_struct(&data);
	init_ray_param(&data);
	init_tex_param(&data);
	load_textures(&data);
	open_window(&data);
	set_hooks(&data);
	mlx_loop(data.mlx.pointer);
	free_data(&data);
	return (0);
}
