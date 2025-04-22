/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 12:48:16 by vandre            #+#    #+#             */
/*   Updated: 2023/11/12 14:56:08 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	len_s1;
	size_t	len_s2;

	if (!s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, len_s1 + 1);
	ft_strlcat(str + len_s1, s2, len_s2 + 1);
	if (s1)
		free((char *)s1);
	return (str);
}
/*
int	main(void)
{
	char s1[] = "Hello";
	char s2[] = "World";
	char	*str;

	str = ft_strjoin(s1, s2);
	if (!str)
		return (1);

	printf("%s\n", str);
	return (0);
}*/
