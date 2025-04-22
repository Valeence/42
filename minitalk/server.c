/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 03:57:20 by vandre            #+#    #+#             */
/*   Updated: 2023/12/18 15:28:37 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#define END_TRANSMISSION '\0'

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	long	nbr;

	nbr = n;
	if (nbr < 0)
	{
		ft_putchar_fd('-', fd);
		nbr = -nbr;
	}
	if (nbr > 9)
		ft_putnbr_fd(nbr / 10, fd);
	ft_putchar_fd(nbr % 10 + '0', fd);
}

void	handle_signal(int signal, siginfo_t *info, void *context)
{
	static unsigned char	current_char;
	static int				bit_index;

	(void)context;
	current_char |= (signal == SIGUSR1);
	bit_index++;
	if (bit_index == 8)
	{
		if (current_char == END_TRANSMISSION)
		{
			write(1, "\n", 1);
			kill(info->si_pid, SIGUSR1);
		}
		else
			write(1, &current_char, 1);
		bit_index = 0;
		current_char = 0;
	}
	else
		current_char <<= 1;
}

int	main(void)
{
	struct sigaction	act;

	act.sa_sigaction = handle_signal;
	act.sa_flags = SA_SIGINFO;
	sigemptyset(&act.sa_mask);
	write(1, "PID: ", 5);
	ft_putnbr_fd(getpid(), 1);
	write(1, "\n", 1);
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	while (1)
		pause();
	return (0);
}
