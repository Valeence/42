/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 16:18:20 by vandre            #+#    #+#             */
/*   Updated: 2024/10/26 17:25:28 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t number, size_t size)
{
	void	*result;

	if (number * size > 2147483647)
		return (NULL);
	result = malloc(number * size);
	if (result == 0)
		return (0);
	ft_memset(result, 0, number * size);
	return (result);
}
