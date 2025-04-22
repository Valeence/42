/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 16:25:41 by vandre            #+#    #+#             */
/*   Updated: 2024/10/26 17:27:28 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *b1, const void *b2, size_t len)
{
	size_t	index;

	index = 0;
	while (index < len)
	{
		if (((unsigned char *)b1)[index] != ((unsigned char *)b2)[index])
			return (((unsigned char *)b1)[index] -
					((unsigned char *)b2)[index]);
		index++;
	}
	return (0);
}
