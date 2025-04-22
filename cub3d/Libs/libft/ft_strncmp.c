/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:22:46 by vandre            #+#    #+#             */
/*   Updated: 2024/10/26 17:30:51 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t	i;

	i = 0;
	while ((*str1 || *str2) && (i < n))
	{
		if ((unsigned char)*str1 > (unsigned char)*str2)
			return (1);
		if ((unsigned char)*str1 < (unsigned char)*str2)
			return (-1);
		str1++;
		str2++;
		i++;
	}
	return (0);
}
