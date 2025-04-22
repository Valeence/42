/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zachamou <zachamou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 03:25:43 by zachamou          #+#    #+#             */
/*   Updated: 2024/06/28 00:14:59 by zachamou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/MiniShell.h"

void	wait_for_children(t_data *data, int last, pid_t pid[])
{
	int	j;
	int	status;

	j = 0;
	while (j < last)
	{
		waitpid(pid[j], &status, 0);
		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status) != 0 && g_gvalret == 0)
				g_gvalret = WEXITSTATUS(status);
			else
				g_gvalret = status;
		}
		j++;
	}
	data->statusp = g_gvalret;
}

char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	while (dest[i] != '\0')
		i++;
	j = 0;
	while (src[j] != '\0')
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}

void	*ft_realloc(void *ptr, size_t newsize)
{
	char	*newptr;
	size_t	cursize;

	if (ptr == 0)
		return (malloc(newsize));
	cursize = sizeof(ptr);
	if (newsize <= cursize)
		return (ptr);
	newptr = malloc(newsize);
	ft_memcpy(ptr, newptr, cursize);
	free(ptr);
	return (newptr);
}

char	**copy_array_arrays(char **src)
{
	int		count;
	char	**dest;
	int		i;

	if (!src)
		return (NULL);
	count = count_strings(src);
	dest = allocate_dest_array(count);
	i = 0;
	while (i < count)
	{
		copy_string(dest, src[i], i);
		i++;
	}
	dest[count] = NULL;
	return (dest);
}

void	free_for_exe_exit(t_data *data, t_Token *curr)
{
	(void)curr;
	if (data->cmd[0] != NULL && data->cmd[0][0] != '\0')
		ft_free_tabtab(data->cmd);
	free(data->path_exe);
	free_token(data->list_token_tmp);
	ft_free_tabtab(data->envp);
	free(data->home);
	g_gvalret = 127;
	exit(127);
}
