/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 14:43:30 by marvin            #+#    #+#             */
/*   Updated: 2024/10/26 17:31:16 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_gnl(char const *s1, char const *s2)
{
	char	*str;
	size_t	len_s1;
	size_t	len_s2;

	if (!s2)
		return (NULL);
	len_s1 = ft_strlen_gnl(s1);
	len_s2 = ft_strlen_gnl(s2);
	str = (char *)ft_calloc_gnl(sizeof(char), (len_s1 + len_s2 + 1));
	if (!str)
		return (NULL);
	ft_strlcpy_gnl(str, s1, len_s1 + 1);
	ft_strlcat_gnl(str + len_s1, s2, len_s2 + 1);
	if (s1)
		free((char *)s1);
	return (str);
}

size_t	ft_strlen_gnl(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

size_t	ft_strlcpy_gnl(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (!src)
		return (0);
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

size_t	ft_strlcat_gnl(char *dst, const char *src, size_t n)
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
	return (i + ft_strlen_gnl(src));
}

void	*ft_calloc_gnl(size_t count, size_t size)
{
	char	*ptr;
	size_t	total;
	size_t	i;

	i = 0;
	total = count * size;
	if (count != 0 && total / count != size)
		return (NULL);
	ptr = (char *)malloc(total);
	if (!ptr)
		return (NULL);
	while (i < total)
		ptr[i++] = '\0';
	return (ptr);
}
