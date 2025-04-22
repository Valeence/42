/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 23:35:24 by vandre            #+#    #+#             */
/*   Updated: 2024/10/28 23:35:51 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static char	*get_error_message(int errcode)
{
	static char	*error_messages[] = {\
		RED "Undefined error message" RESET, \
		"Run: " RED "./CUBE3D " RESET RED "PATH_TO_MAP" RESET, \
		"File extension must be " RED ".cub" RESET, \
		"Invalid texture parameter. Must be either " RED "NO" RESET ", " \
			RED "SO" RESET ", " RED "EA" RESET ", " RED "WE" RESET \
			", " RED "F" RESET " or " RED "C" RESET \
			", followed by a space and the path to the texture file.", \
		"Missing parameter. Provide " RED "4 texture file paths" RESET \
			" and " RED "2 colours." RESET, \
		"Redundant parameter found. Parameter duplicates not allowed.", \
		"Invalid colour format. Use: " RED "R, G, B" RESET \
			", each value ranging from 0 to 255.", \
		"Invalid map.", \
		"Error allocating memory. Ran out of RAM?", \
		"Map has invalid char. Valid chars are: " RED VALID_CHARS RESET, \
		"Invalid map size.", \
		"No starting position character found. Valid chars are: " \
			RED "N" RESET ", " RED "S" RESET ", " RED "E" RESET \
			", " RED "W" RESET ".", \
		"Multiple starting position characters found. Only one allowed.", \
		"Player starting position is outside the map.", \
		"MLX error"};

	return (error_messages[errcode]);
}

void	print_err_exit(int errcode, t_data *data)
{
	free_data(data);
	printf(RED "ERROR " RESET "\n");
	if (errcode)
		printf("%s\n", get_error_message(errcode));
	else
		perror(NULL);
	exit(errcode + errno);
}
