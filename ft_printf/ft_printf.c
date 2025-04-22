/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 23:27:57 by vandre            #+#    #+#             */
/*   Updated: 2023/11/18 16:54:12 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	check_args(const char *str)
{
	while (*str)
	{
		if (ft_strchr(str, '%'))
		{
			str = ft_strchr(str, '%') + 1;
			if (!ft_strchr("%cspdiuxX", *str))
				return (0);
		}
		str++;
	}
	return (1);
}

void	my_printf(const char *str, va_list arg, size_t *len)
{
	while (*str)
	{
		if (*str == '%')
		{
			if (*++str == 'c')
				*len += len_putchar(va_arg(arg, int));
			else if (*str == 's')
				*len += len_putstr(va_arg(arg, char *));
			else if (*str == 'p')
				len_convertbase(va_arg(arg, unsigned long), 'p', len);
			else if (*str == 'd' || *str == 'i')
				len_putnbr(va_arg(arg, int), len);
			else if (*str == 'u')
				len_convertbase(va_arg(arg, unsigned int), 'u', len);
			else if (*str == 'x')
				len_convertbase(va_arg(arg, unsigned int), 'x', len);
			else if (*str == 'X')
				len_convertbase(va_arg(arg, unsigned int), 'X', len);
			else if (*str == '%')
				*len += len_putchar(*str);
		}
		else
			*len += len_putchar(*str);
		str++;
	}
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	size_t	len;

	len = 0;
	if (!str)
		return (-1);
	va_start(args, str);
	if (check_args(str))
		my_printf(str, args, &len);
	va_end(args);
	return (len);
}
