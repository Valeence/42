/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_gnl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:14:00 by vandre            #+#    #+#             */
/*   Updated: 2023/11/14 15:59:46 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

size_t	count_gnl(char *path)
{
	int		fd;
	char	*line;
	size_t	count;

	count = 0;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (0);
	line = get_next_line(fd);
	while (line != NULL)
	{
		line = get_next_line(fd);
		count++;
		free(line);
	}
	close(fd);
	return (count);
}

// int main()
// {
// 	size_t nb_gnl;

// 	nb_gnl = count_gnl("../../map.ber");
// 	printf("%zu\n", nb_gnl);
// }
