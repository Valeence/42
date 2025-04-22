/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:30:12 by vandre            #+#    #+#             */
/*   Updated: 2024/10/26 17:30:19 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_sep(char *s, char c)
{
	if (c == *s)
		return (1);
	return (0);
}

int	word_count(char *s, char c)
{
	int		i;
	int		word;

	i = 0;
	word = 0;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if ((s[i] != c && s[i + 1] == '\0') || (s[i] != c && s[i + 1] == c))
		{
			word++;
			i++;
		}
		else
			i++;
	}
	return (word);
}

int	ft_len(char *s, unsigned int i, char c)
{
	int		len;

	len = 0;
	while (!is_sep(&s[i], c) && s[i])
	{
		i++;
		len++;
	}
	return (len);
}

void	free_newstr(char **newstr, int i)
{
	int	j;

	j = 0;
	if (!newstr)
		return ;
	while (i > j)
	{
		free(newstr[i]);
		j++;
	}
	free(newstr);
}

char	**ft_split(char const *s, char c)
{
	char			**newstr;
	int				nb_words;
	unsigned int	i;
	int				start;

	i = 0;
	if (!s)
		return (NULL);
	nb_words = word_count((char *)s, c);
	newstr = (char **)malloc(sizeof(char *) * (nb_words + 1));
	if (!newstr)
		return (NULL);
	start = 0;
	while (nb_words--)
	{
		while (is_sep((char *)&s[start], c))
			start++;
		newstr[i] = ft_substr(s, start, ft_len((char *)s, start, c));
		start += ft_len((char *)s, start, c);
		if (!newstr[i])
			free_newstr(newstr, i);
		i++;
	}
	newstr[i] = 0;
	return (newstr);
}
