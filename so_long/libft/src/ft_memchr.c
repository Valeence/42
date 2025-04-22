/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 12:40:43 by vandre            #+#    #+#             */
/*   Updated: 2023/10/19 14:33:30 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;

	str = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (str[i] == (unsigned char )c)
			return (str + i);
		i++;
	}
	return (NULL);
}
/*
int	main(void)
{
	char str[] = "Hello Words";
	size_t len = sizeof(str);
	char *result = ft_memchr(str, 'W', len);

	printf("%s, %zu, %c\n", str, len, *result);
	return (0);
}*/