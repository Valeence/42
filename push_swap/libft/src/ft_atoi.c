/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 00:49:02 by vandre            #+#    #+#             */
/*   Updated: 2024/02/01 14:38:16 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

bool	ft_atoi(const char *str, int *num)
{
	long long	rs;
	int			sg;

	rs = 0;
	sg = 1;
	while (ft_iswhitespace(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sg = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		rs = rs * 10 + (*str++ - '0');
		if ((sg == 1 && rs > 2147483647LL)
			|| (sg == -1 && sg * rs < -2147483648LL))
			return (false);
	}
	*num = (int)(sg * rs);
	return (true);
}
