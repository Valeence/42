/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:17:53 by vandre            #+#    #+#             */
/*   Updated: 2023/11/12 14:49:35 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size > 0)
	{
		while (src[i] != '\0' && i < size - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	while (src[i] != '\0')
		i++;
	return (i);
}
/*int main(void)
{
    char dst[6];
    const char *src = "bonsoir";
    size_t len;

    len = ft_strlcpy(dst, src, sizeof(dst));
    printf("src = \"%s\", dst = \"%s\", len = %zu\n", src, dst, len);

    return 0;
}*/
