/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 23:30:43 by vandre            #+#    #+#             */
/*   Updated: 2023/11/18 15:44:55 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

int		ft_printf(const char *str, ...);
size_t	len_putchar(char c);
size_t	len_putstr(char *str);
void	len_convertbase(unsigned long nb, char index, size_t *len);
void	len_putnbr(int nb, size_t *len);
char	*ft_strchr(const char *str, int c);
size_t	ft_strlen(const char *str);

#endif