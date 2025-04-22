/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 13:31:00 by vandre            #+#    #+#             */
/*   Updated: 2023/10/19 14:34:30 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

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
