/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 04:36:17 by vandre            #+#    #+#             */
/*   Updated: 2024/06/11 19:08:18 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/MiniShell.h"

char	*remove_quotes(char *str)
{
	char	*new_str;
	int		len;
	int		i;
	int		j;

	len = ft_strlen(str);
	new_str = malloc(len + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != '"' && str[i] != '\'')
		{
			new_str[j] = str[i];
			j++;
		}
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}

int	ft_isalnum_env(int c)
{
	if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A'
			&& c <= 'Z') || c == '_')
	{
		return (1);
	}
	return (0);
}

void	free_tokens(char **tokens, char *str)
{
	int	i;

	i = 0;
	if (str)
		free(str);
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

int	add_new_var(t_data *data, char *str)
{
	char	**new_env;
	int		env_size;

	env_size = 0;
	while (data->envp[env_size])
		env_size++;
	new_env = malloc(sizeof(char *) * (env_size + 2));
	if (!new_env)
		return (-1);
	env_size = 0;
	while (data->envp[env_size])
	{
		new_env[env_size] = data->envp[env_size];
		env_size++;
	}
	new_env[env_size] = ft_strdup(str);
	if (!new_env[env_size])
	{
		free(new_env);
		return (-1);
	}
	new_env[env_size + 1] = NULL;
	free(data->envp);
	data->envp = new_env;
	return (0);
}
