/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoli.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 16:18:16 by vandre            #+#    #+#             */
/*   Updated: 2024/10/26 17:25:02 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long int	ft_atoli(const	char *str)
{
	long int	result;
	long int	signal;
	int			index;

	index = 0;
	result = 0;
	signal = 1;
	while ((str[index] >= '\t' && str[index] <= '\r') || str[index] == ' ')
		index++;
	if (str[index] == '-' || str[index] == '+')
	{
		if (str[index] == '-')
			signal = -1;
		index++;
	}
	while (ft_isdigit(str[index]))
	{
		result = result * 10 + str[index] - '0';
		index++;
	}
	return (result * signal);
}
