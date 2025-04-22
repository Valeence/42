/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zachamou <zachamou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 01:14:59 by vandre            #+#    #+#             */
/*   Updated: 2024/06/27 23:22:37 by zachamou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/MiniShell.h"

void	copy_word(const char *substring, int len, char **result, int *k)
{
	result[*k] = malloc(len + 1);
	if (!result[*k])
		return ;
	strncpy(result[*k], substring, len);
	result[*k][len] = '\0';
	(*k)++;
}

int	process_word(const char *s, int i, char **result, int *k)
{
	int		in_s_qotes;
	int		in_d_qotes;
	int		j;

	in_s_qotes = 0;
	in_d_qotes = 0;
	j = i;
	while (s[j] && (in_d_qotes || in_s_qotes || (s[j] != ' ')))
	{
		if (s[j] == '"' && !in_s_qotes)
			in_d_qotes = !in_d_qotes;
		else if (s[j] == '\'' && !in_d_qotes)
			in_s_qotes = !in_s_qotes;
		j++;
	}
	copy_word(&s[i], j - i, result, k);
	return (j);
}

char	**allocate_result_array(char const *s)
{
	char	**result;

	result = malloc((strlen(s) / 2 + 2) * sizeof(char *));
	if (!result)
		return (NULL);
	return (result);
}

char	**ft_split_quoted(char const *s)
{
	char	**result;
	int		i;
	int		k;

	result = allocate_result_array(s);
	if (!result)
		return (NULL);
	i = 0;
	k = 0;
	while (s[i])
	{
		while (s[i] == ' ')
			i++;
		if (s[i])
			i = process_word(s, i, result, &k);
	}
	result[k] = NULL;
	return (result);
}
