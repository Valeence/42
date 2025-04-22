/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zack <zack@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 01:13:12 by zachamou          #+#    #+#             */
/*   Updated: 2024/06/19 17:21:56 by zack             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/MiniShell.h"

void	ft_strcpy(char *dst, char *src)
{
	while (*src)
		*dst++ = *src++;
	*dst = '\0';
}

char	*read_until_delimiter(t_here *here)
{
	char	*line;

	while (1)
	{
		line = readline(">");
		if (ft_strcmp(line, here->delim[0]) == 1)
		{
			free(line);
			break ;
		}
		return (line);
	}
	return (NULL);
}

int	concatenate_lines(t_data *data, char *line)
{
	size_t	len;
	char	*new_str;

	len = ft_strlen(data->str) + ft_strlen(line) + 1;
	new_str = (char *)ft_calloc(len + 1, sizeof(char));
	if (new_str == NULL)
	{
		free(data->str);
		free(line);
		return (-1);
	}
	ft_strcpy(new_str, data->str);
	free(data->str);
	data->str = new_str;
	ft_strcat(data->str, line);
	ft_strcat(data->str, "\n");
	return (0);
}

void	close_or_not(t_data *data, pid_t pid)
{
	close(data->here_fd[0]);
	if (data->data2->redi_and_here == false)
		write(data->here_fd[1], data->str, ft_strlen(data->str));
	else
		data->str_here = ft_strndup(data->str, ft_strlen(data->str));
	close(data->here_fd[1]);
	waitpid(pid, 0, 0);
}
