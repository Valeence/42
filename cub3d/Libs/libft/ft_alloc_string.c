/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 16:18:12 by vandre            #+#    #+#             */
/*   Updated: 2024/10/26 17:24:22 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_alloc_string(int str_size, int init_value)
{
	char	*str;
	int		i;

	str = malloc((str_size + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = -1;
	while (++i < str_size)
		str[i] = init_value;
	str[i] = '\0';
	return (str);
}
