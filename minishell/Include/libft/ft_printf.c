/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zachamou <zachamou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 23:27:57 by vandre            #+#    #+#             */
/*   Updated: 2024/06/27 22:43:07 by zachamou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

void	my_printf(const char *str, va_list arg, size_t *len, int fd)
{
	while (*str)
	{
		if (*str == '%')
		{
			if (*++str == 'c')
				*len += len_putchar(va_arg(arg, int), fd);
			else if (*str == 's')
				*len += len_putstr(va_arg(arg, char *), fd);
			else if (*str == 'p')
				len_convertbase(va_arg(arg, unsigned long), 'p', len, fd);
			else if (*str == 'd' || *str == 'i')
				len_putnbr(va_arg(arg, int), len, fd);
			else if (*str == 'u')
				len_convertbase(va_arg(arg, unsigned int), 'u', len, fd);
			else if (*str == 'x')
				len_convertbase(va_arg(arg, unsigned int), 'x', len, fd);
			else if (*str == 'X')
				len_convertbase(va_arg(arg, unsigned int), 'X', len, fd);
			else if (*str == '%')
				*len += len_putchar(*str, fd);
		}
		else
			*len += len_putchar(*str, fd);
		str++;
	}
}

int	ft_printf(int fd, const char *str, ...)
{
	va_list	args;
	size_t	len;

	len = 0;
	if (!str)
		return (-1);
	va_start(args, str);
	if (check_args(str))
		my_printf(str, args, &len, fd);
	va_end(args);
	return (len);
}
