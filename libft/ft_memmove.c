/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 02:21:52 by vandre            #+#    #+#             */
/*   Updated: 2023/05/28 00:47:42 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*d;
	const char	*s;
	size_t		i;

	if (!dest || !src)
		return (NULL);
	d = (char *)dest;
	s = (const char *)src;
	if (d > s)
	{
		i = n;
		while (i--)
			d[i] = s[i];
	}
	else
	{
		i = 0;
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
	}
	return (dest);
}

// int main(void)
// {
//    char str1[] = "Hello World!";
//    char str2[] = "Goodbye";

//    printf("Before memmove str1 = %s, str2 = %s\n", str1, str2);

//    /* Copie les5 premiers caractères de str1 dans str2 */
//    ft_memmove(str2, str1, 7);

//    printf("After memmove str1 = %s, str2 = %s\n", str1, str2);
//    return (0);
// }
