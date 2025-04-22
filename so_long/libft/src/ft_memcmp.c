/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 01:44:15 by vandre            #+#    #+#             */
/*   Updated: 2023/10/19 14:33:35 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	char	*str1;
	char	*str2;
	size_t	i;

	str1 = (char *)s1;
	str2 = (char *)s2;
	i = 0;
	while (i < n)
	{
		if (str1[i] != str2[i])
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
		i++;
	}
	return (0);
}
/*
int main() {
   char str1[15];
   char str2[15];
   int result;

   strcpy(str1, "abcdef");
   strcpy(str2, "ABCDEF");

   result = memcmp(str1, str2, 6);

   if(result > 0) {
      printf("str1 est plus grand que str2.\n");
   } else if(result < 0) {
      printf("str1 est plus petit que str2.\n");
   } else {
      printf("str1 et str2 sont égaux.\n");
   }

   return 0;
}*/