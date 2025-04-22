/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:57:10 by vandre            #+#    #+#             */
/*   Updated: 2024/04/29 21:23:26 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	len_putnbrbase(unsigned long nb, char *base, size_t *len, int fd)
{
	size_t	base_len;

	base_len = ft_strlen(base);
	if (nb >= base_len)
	{
		len_putnbrbase(nb / base_len, base, len, fd);
	}
	*len += len_putchar(base[nb % base_len], fd);
}

void	len_convertbase(unsigned long nb, char index, size_t *len, int fd)
{
	char	*base[3];

	base[0] = "0123456789";
	base[1] = "0123456789abcdef";
	base[2] = "0123456789ABCDEF";
	if (index == 'u')
		len_putnbrbase(nb, base[0], len, fd);
	else if (index == 'x')
		len_putnbrbase(nb, base[1], len, fd);
	else if (index == 'X')
		len_putnbrbase(nb, base[2], len, fd);
	else if (index == 'p')
	{
		if (!nb)
		{
			*len += write(1, "(nil)", 5);
			return ;
		}
		*len += write(1, "0x", 2);
		len_putnbrbase(nb, base[1], len, fd);
	}
}

size_t	len_putchar(char c, int fd)
{
	write(fd, &c, 1);
	return (1);
}

void	len_putnbr(int nb, size_t *len, int fd)
{
	long	n;

	n = nb;
	if (n < 0)
	{
		*len += len_putchar('-', fd);
		n = -n;
	}
	if (n > 9)
	{
		len_putnbr(n / 10, len, fd);
	}
	*len += len_putchar(n % 10 + 48, fd);
}

size_t	len_putstr(char *str, int fd)
{
	if (!str)
		str = "(null)";
	write(fd, str, ft_strlen(str));
	return (ft_strlen(str));
}
