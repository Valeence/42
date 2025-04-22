/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:07:06 by vandre            #+#    #+#             */
/*   Updated: 2024/01/18 14:33:15 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*p;
	size_t			i;

	if (!s)
		return ;
	p = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		*p = 0;
		i++;
		p++;
	}
}
