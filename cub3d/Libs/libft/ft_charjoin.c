/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_charjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 16:18:22 by vandre            #+#    #+#             */
/*   Updated: 2024/10/26 17:25:43 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_charjoin(const char *str, const char c)
{
	int		i;
	char	*joined_str;

	if (!str)
		return (NULL);
	joined_str = malloc((ft_strlen(str) + 1 + 1) * sizeof(char));
	if (!joined_str)
		return (NULL);
	i = -1;
	while (str[++i])
		joined_str[i] = str[i];
	joined_str[i] = c;
	joined_str[++i] = '\0';
	ft_free_ptr((void *)&str);
	return (joined_str);
}
