/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:22:46 by vandre            #+#    #+#             */
/*   Updated: 2023/05/28 00:52:56 by vandre           ###   ########.fr       */
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
/*
int	main(void)
{
	char	s1[] = "bonjour";
	char	s2[] = "bonjour";
	unsigned int n = 4;

	printf("%d", ft_strncmp(s1, s2, n));
}*/
