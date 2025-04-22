/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_echo_split.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zack <zack@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 15:22:41 by vandre            #+#    #+#             */
/*   Updated: 2024/06/19 17:35:23 by zack             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/MiniShell.h"

static int	update_quote_status(char c, int *in_D_QOTES,
		int *in_S_QOTES)
{
	if (c == '"' && !(*in_S_QOTES))
		*in_D_QOTES = !(*in_D_QOTES);
	else if (c == '\'' && !(*in_D_QOTES))
		*in_S_QOTES = !(*in_S_QOTES);
	return (*in_D_QOTES || *in_S_QOTES);
}

static char	*extract_word(const char *s, int start, int end)
{
	char	*word;

	word = malloc(end - start + 1);
	if (!word)
		return (NULL);
	if (word)
	{
		strncpy(word, s + start, end - start);
		word[end - start] = '\0';
	}
	return (word);
}

static void	free_memory(char **result, int count)
{
	while (count-- > 0)
		free(result[count]);
	free(result);
}

char	**init_result(char const *s, char **result)
{
	result = NULL;
	result = malloc((strlen(s) / 2 + 2) * sizeof(char *));
	if (!result)
		return (NULL);
	return (result);
}

char	**ft_split_quoted_echo(char const *s)
{
	char	**result;
	int		*vars;

	vars = init_vars();
	result = NULL;
	result = init_result(s, result);
	while (s[vars[0]])
	{
		while (s[vars[0]] == ' ')
			vars[0]++;
		vars[1] = vars[0];
		while (s[vars[1]]
			&& (update_quote_status(s[vars[1]], &vars[3], &vars[4])
				|| s[vars[1]] != ' '))
			vars[1]++;
		result[vars[2]] = extract_word(s, vars[0], vars[1]);
		if (!result[vars[2]])
			return (free_memory(result, vars[2]), NULL);
		vars[2]++;
		vars[0] = vars[1];
	}
	result[vars[2]] = NULL;
	free(vars);
	return (result);
}
