/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:57:10 by vandre            #+#    #+#             */
/*   Updated: 2023/11/18 16:04:14 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	len_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

void	len_putnbr(int nb, size_t *len)
{
	long	n;

	n = nb;
	if (n < 0)
	{
		*len += len_putchar('-');
		n = -n;
	}
	if (n > 9)
	{
		len_putnbr(n / 10, len);
	}
	*len += len_putchar(n % 10 + 48);
}

size_t	len_putstr(char *str)
{
	if (!str)
		str = "(null)";
	write(1, str, ft_strlen(str));
	return (ft_strlen(str));
}

static void	len_putnbrbase(unsigned long nb, char *base, size_t *len)
{
	size_t	base_len;

	base_len = ft_strlen(base);
	if (nb >= base_len)
	{
		len_putnbrbase(nb / base_len, base, len);
	}
	*len += len_putchar(base[nb % base_len]);
}

void	len_convertbase(unsigned long nb, char index, size_t *len)
{
	char	*base[3];

	base[0] = "0123456789";
	base[1] = "0123456789abcdef";
	base[2] = "0123456789ABCDEF";
	if (index == 'u')
		len_putnbrbase(nb, base[0], len);
	else if (index == 'x')
		len_putnbrbase(nb, base[1], len);
	else if (index == 'X')
		len_putnbrbase(nb, base[2], len);
	else if (index == 'p')
	{
		if (!nb)
		{
			*len += write(1, "(nil)", 5);
			return ;
		}
		*len += write(1, "0x", 2);
		len_putnbrbase(nb, base[1], len);
	}
}
