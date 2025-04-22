/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 03:57:14 by vandre            #+#    #+#             */
/*   Updated: 2023/12/18 15:28:09 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	ft_atoi(const char *str)
{
	long			res;
	long			sign;
	unsigned int	i;

	res = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\r' || str[i] == '\v' || str[i] == '\f')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return ((int)(res * sign));
}

void	send_signal(int pid, unsigned char c)
{
	int				i;
	unsigned char	temp_char;

	i = 8;
	temp_char = c;
	while (i > 0)
	{
		i--;
		temp_char = c >> i;
		if (temp_char % 2 == 0)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		usleep(1000);
	}
}

void	handle_read_receipt(int signal)
{
	if (signal == SIGUSR1)
		write(1, "message received\n", 17);
}

int	main(int argc, char *argv[])
{
	const char	*str;
	int			i;

	signal(SIGUSR1, handle_read_receipt);
	signal(SIGUSR2, handle_read_receipt);
	if (argc != 3)
	{
		write(1, "Usage: ./client [pid] [string]\n", 31);
		exit(0);
	}
	str = argv[2];
	i = 0;
	while (str[i])
		send_signal(ft_atoi(argv[1]), str[i++]);
	send_signal(ft_atoi(argv[1]), '\0');
	return (0);
}
