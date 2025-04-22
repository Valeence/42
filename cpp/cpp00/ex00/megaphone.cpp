/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megaphone.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 00:15:13 by vandre            #+#    #+#             */
/*   Updated: 2024/11/30 15:14:03 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

int	main(int argc, char **argv)
{
	int i = 1;

	if (argc <= 1)
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE * " << std::endl;
	else
	{
		while (argv[i])
		{
			int j = 0;
			while (argv[i][j] != '\0')
			{
				if (islower(argv[i][j]))
					argv[i][j] = toupper(argv[i][j]);
				std::cout << argv[i][j];
				j++;
			}
			i++;
		}
	}
	return (0);
}
