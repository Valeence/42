/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zachamou <zachamou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 05:12:46 by vandre            #+#    #+#             */
/*   Updated: 2024/06/27 23:22:55 by zachamou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/MiniShell.h"

char	*getenv_from_envp(const char *name, char **envp)
{
	int	i;
	int	len;

	len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

static void	expand_variable(const char *var_name, t_data *data)
{
	char	*var_value;

	var_value = getenv_from_envp(var_name, data->envp);
	if (var_value)
		write(1, var_value, ft_strlen(var_value));
}

static char	*extract_var_name(const char *arg, int start, int *end)
{
	int	j;

	j = start;
	while (arg[j] && (isalnum(arg[j]) || arg[j] == '_'))
		j++;
	*end = j;
	return (ft_strndup(arg + start, j - start));
}

static void	handle_quote(char c, int *in_d_qotes, int *in_s_qotes)
{
	if (c == '"' && !(*in_s_qotes))
		*in_d_qotes = !(*in_d_qotes);
	else if (c == '\'' && !(*in_d_qotes))
		*in_s_qotes = !(*in_s_qotes);
}

void	process_arg(char *arg, t_data *data)
{
	char	*var_name;
	int		i;
	int		in_d_qotes;
	int		in_s_qotes;
	int		end;

	i = 0;
	in_d_qotes = 0;
	in_s_qotes = 0;
	while (arg[i])
	{
		handle_quote(arg[i], &in_d_qotes, &in_s_qotes);
		if (arg[i] == '$' && !in_s_qotes && arg[i + 1] == '?')
			return (aff_exit_code(data));
		else if (arg[i] == '$' && !in_s_qotes)
		{
			var_name = extract_var_name(arg, i + 1, &end);
			expand_variable(var_name, data);
			free(var_name);
			i = end - 1;
		}
		else if (arg[i] != '"' && arg[i] != '\'')
			write(1, &arg[i], 1);
		i++;
	}
}
