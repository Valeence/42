/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 17:31:54 by vandre            #+#    #+#             */
/*   Updated: 2023/06/13 14:35:25 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	start;
	size_t	end;

	if (!s1)
		return (NULL);
	end = ft_strlen(s1);
	start = 0;
	while (ft_strchr(set, s1[start]))
		start++;
	while (ft_strchr(set, s1[end]))
		end--;
	str = ft_substr(s1, start, end - start + 1);
	return (str);
}

// int	main()
// {
// 	char *s1 = "  bonjour a tous comment ca va  ";
// 	char *set = " ";
// 	printf("%s\n", ft_strtrim(s1, set));
// }