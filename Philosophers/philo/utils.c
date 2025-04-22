/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 07:34:44 by vandre            #+#    #+#             */
/*   Updated: 2024/03/10 04:48:34 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_odd(t_data *data)
{
	if (data->time_eat >= data->time_sleep)
		usleep((data->time_eat - data->time_sleep) * 1000);
	usleep(500);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_iswhitespace(char c)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		if (c == " \t\n\v\f\r"[i])
			return (1);
		i++;
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	long long	rs;
	int			sg;
	int			num;

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
	num = (sg * rs);
	return (num);
}
