/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 13:54:45 by vandre            #+#    #+#             */
/*   Updated: 2023/05/28 00:55:13 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t n)
{
	size_t	i;
	size_t	k;

	if (!src || !dst)
		return (0);
	i = 0;
	k = 0;
	while (dst[i] && i < n)
		i++;
	while ((src[k]) && ((i + k + 1) < n))
	{
		dst[i + k] = src[k];
		k++;
	}
	if (i != n)
		dst[i + k] = '\0';
	return (i + ft_strlen(src));
}
