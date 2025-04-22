/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 16:18:37 by vandre            #+#    #+#             */
/*   Updated: 2024/10/26 17:26:26 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	intlen(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		i++;
	while (n != 0)
	{
		i++;
		n /= 10;
	}
	return (i);
}

static int	isabs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

static void	revalue(char *number)
{
	size_t	start;
	size_t	end;
	char	aux;

	start = 0;
	end = ft_strlen(number) - 1;
	while (number[start] && start < end)
	{
		aux = number[start];
		number[start] = number[end];
		number[end] = aux;
		end--;
		start++;
	}
}

char	*ft_itoa(int n)
{
	size_t	size;
	char	*string;
	size_t	is_n;

	is_n = (n < 0);
	if (n == 0)
		return (ft_strdup("0"));
	string = ft_calloc(sizeof(char), ((intlen(n) + is_n) + 1));
	if (!string)
		return (NULL);
	size = 0;
	while (n != 0)
	{
		string[size++] = '0' + isabs(n % 10);
		n /= 10;
	}
	if (is_n)
		string[size] = '-';
	revalue(string);
	return (string);
}
