/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zachamou <zachamou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:43:18 by vandre            #+#    #+#             */
/*   Updated: 2024/06/27 23:27:15 by zachamou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/MiniShell.h"

int	check_home(char *str, char *home)
{
	int		i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == 'c' && str[i + 1] == 'd')
	{
		i += 2;
		while (str[i] == ' ')
			i++;
		if (str[i] == '\0' || str[i] == '~')
		{
			if (chdir(home) != 0)
			{
				perror("chdir");
				return (0);
			}
			return (1);
		}
	}
	return (0);
}

int	*find_path_cd(char *str, char *home)
{
	int	*tab;
	int	i;

	i = 0;
	tab = malloc(sizeof(int) * 2);
	if (!tab)
		return (NULL);
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		if (str[i] == 'c' && str[i + 1] == 'd')
		{
			if (check_home(str, home) == 1)
			{
				tab[0] = -1;
				return (tab);
			}
			tab = fill_tab(str, i, tab);
			return (tab);
		}
		i++;
	}
	free(tab);
	return (NULL);
}

char	*fill_path(char *str, int j, int x)
{
	char	*path;
	int		i;

	if (!str)
		return (NULL);
	path = malloc(sizeof(char) * x + 1);
	if (!path)
		return (0);
	i = 0;
	while (i < x)
	{
		path[i] = str[j];
		i++;
		j++;
	}
	path[i] = '\0';
	return (path);
}

int	change_directory(const char *path)
{
	if (chdir(path) != 0)
	{
		perror("cd");
		return (0);
	}
	return (1);
}

int	ft_cd(t_Token *curr, t_data *data)
{
	char	*path;
	int		*tab;
	int		j;

	if (ft_strcmp(curr->token_str, "cd") == 0)
		return (change_directory(data->home));
	tab = find_path_cd(curr->token_str, data->home);
	if (!tab)
		return (0);
	if (tab[0] == -1)
		return (free(tab), 0);
	j = tab[0] - tab[1];
	path = fill_path(curr->token_str, j, tab[1]);
	if (!path || !change_directory(path))
	{
		free(tab);
		free(path);
		return (0);
	}
	free(tab);
	free(path);
	return (1);
}
