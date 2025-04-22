/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 19:52:21 by vandre            #+#    #+#             */
/*   Updated: 2023/05/31 15:45:36 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	size_t	i;

	i = 0;
	if (!s)
		return ;
	while (s[i] != '\0')
	{
		f(i, &s[i]);
		i++;
	}
}

// int     main(void)
// {
//     char    str[] = "Hello World!";

//     /* Applique la fonction ft_test() à chaque caractère de la chaîne */
//     ft_striteri(str, &ft_test);

//     /* Affiche la chaîne de caractères modifiée */
//     printf("%s\n", str);

//     return (0);
// }