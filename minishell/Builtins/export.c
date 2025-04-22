/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zachamou <zachamou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:43:28 by vandre            #+#    #+#             */
/*   Updated: 2024/06/27 23:27:15 by zachamou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/MiniShell.h"

int	update_existing_var(t_data *data, char *str, int name_len)
{
	int	j;

	j = 0;
	while (data->envp[j])
	{
		if (ft_strncmp(data->envp[j], str, name_len) == 0
			&& data->envp[j][name_len] == '=')
		{
			free(data->envp[j]);
			data->envp[j] = ft_strdup(str);
			if (!data->envp[j])
				return (-1);
			return (1);
		}
		j++;
	}
	return (0);
}

int	find_name_len(char *str)
{
	int	name_len;

	name_len = 0;
	while (str[name_len] && str[name_len] != '=')
		name_len++;
	return (name_len);
}

int	check_str(char *str)
{
	int	i;

	i = 0;
	if (ft_strchr(str, '=') == NULL)
		return (ft_printf(2, "export: `%s': not a valid identifier\n", str), 0);
	if (str[i] == '=')
		return (ft_printf(2, "export: `%s': not a valid identifier\n", str), 0);
	if (ft_isdigit(str[0]))
		return (ft_printf(2, "export: `%s': not a valid identifier\n", str), 0);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum_env(str[i]) && str[i] != '=')
		{
			ft_printf(2, "export: `%s': not a valid identifier\n", str);
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_export_utils(char **tokens, int i, t_data *data)
{
	int		res;
	int		name_len;
	char	*token_without_quotes;

	while (tokens[i])
	{
		if (check_str(tokens[i]) == 0)
			return (free_tokens(tokens, NULL), -1);
		name_len = find_name_len(tokens[i]);
		token_without_quotes = remove_quotes(tokens[i]);
		res = update_existing_var(data, token_without_quotes, name_len);
		if (res == 0)
		{
			if (add_new_var(data, token_without_quotes) != 0)
				return (free_tokens(tokens, token_without_quotes), -1);
		}
		else if (res == -1)
			return (free_tokens(tokens, token_without_quotes), -1);
		free(token_without_quotes);
		i++;
	}
	free_tokens(tokens, NULL);
	return (1);
}

int	ft_export(t_data *data, t_Token *curr)
{
	char	**tokens;
	int		i;

	tokens = ft_split_quoted(curr->token_str);
	if (!tokens)
		return (-1);
	i = 1;
	ft_export_utils(tokens, i, data);
	return (1);
}
