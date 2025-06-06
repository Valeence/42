/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 13:18:16 by vandre            #+#    #+#             */
/*   Updated: 2024/10/26 17:30:58 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	const char	*p;

	p = NULL;
	while (*str)
	{
		if (*str == (char)c)
			p = str;
		str++;
	}
	if (*str == (char)c)
		return ((char *)str);
	else
		return ((char *)p);
}
