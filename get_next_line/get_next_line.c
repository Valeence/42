/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 14:43:32 by marvin            #+#    #+#             */
/*   Updated: 2023/10/16 14:32:13 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	in_line(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

void	cut_line(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return ;
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\n')
		i++;
	line[i] = '\0';
}

void	swap_buffer(char *buffer)
{
	int		i;
	int		l;
	char	tmp;

	i = 0;
	l = 0;
	if (!buffer)
		return ;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	while (buffer[i++])
	{
		tmp = buffer[i];
		buffer[l] = tmp;
		l++;
	}
	buffer[l] = '\0';
}

char	*init_line(char *line, char *buffer)
{
	int	i;

	i = 0;
	if (!buffer)
		return (NULL);
	if (!line)
		line = (char *)malloc((ft_strlen(buffer) + 1) * sizeof(char));
	if (!line)
		return (NULL);
	while (buffer[i] != '\0')
	{
		line[i] = buffer[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	buffer[BUFFER_SIZE + 1];
	int			bytes_read;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 1024)
		return (NULL);
	if (buffer[0] != '\0')
		line = init_line(line, buffer);
	while (!in_line(buffer))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (NULL);
		buffer[bytes_read] = '\0';
		if (bytes_read == 0)
			break ;
		line = ft_strjoin(line, buffer);
		if (!line)
			return (NULL);
	}
	cut_line(line);
	swap_buffer(buffer);
	return (line);
}

// int		main(void)
// {
// 	int		fd;
// 	char	*line;

// 	fd = open("test.txt", O_RDONLY);
// 	line = get_next_line(fd);
// 	printf("%s\n", line);
// }
