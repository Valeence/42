/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 11:50:03 by vandre            #+#    #+#             */
/*   Updated: 2023/10/20 02:14:13 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;

	if (!s || start > ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, (char *)s + start, len + 1);
	return (str);
}

// int main(void)
// {
//     char *str = "Hello, world!";
//     char *sub = ft_substr(str, 13, 5);
//     printf("%s\n", sub); // Output: "world"
//     free(sub);
//     return 0;
// }
