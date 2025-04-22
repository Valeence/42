/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 22:29:18 by vandre            #+#    #+#             */
/*   Updated: 2023/06/14 18:34:57 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	len(int n)
{
	int	i;

	i = 0;
	if (n < 0)
		i++;
	if (!n)
		return (1);
	if (n == 1)
	{
		i++;
		return (i);
	}
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char		*s;
	long int	nbr;
	int			i;

	nbr = n;
	if (!n)
		return (s = malloc(sizeof(char) * 2), s[0] = '0', s[1] = '\0', s);
	i = len(n);
	s = (char *)malloc(sizeof(char) * (i + 1));
	if (!s)
		return (NULL);
	s[i] = '\0';
	i--;
	if (n < 0)
	{
		nbr *= -1;
		s[0] = '-';
	}
	while (nbr > 0)
	{
		s[i] = (nbr % 10) + '0';
		nbr /= 10;
		i--;
	}
	return (s);
}
// #include <string.h>
// int	main(void)
// {
// 	printf("%s", ft_itoa(0));
// }
