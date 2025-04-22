/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 13:31:00 by vandre            #+#    #+#             */
/*   Updated: 2024/10/26 17:30:26 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*str;
	size_t	i;

	str = (char *)malloc(sizeof(char) * ft_strlen(s) + 1);
	i = ft_strlen(s);
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, s, i + 1);
	return (str);
}
