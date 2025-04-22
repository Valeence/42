/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 16:25:39 by vandre            #+#    #+#             */
/*   Updated: 2024/10/26 17:27:22 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *b, int c, size_t len)
{
	size_t	index;

	index = 0;
	while (index < len)
	{
		if (((unsigned char *)b)[index] == (unsigned char)c)
			return ((unsigned char *)b + index);
		index++;
	}
	return (0);
}
