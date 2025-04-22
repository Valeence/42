/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 01:38:48 by vandre            #+#    #+#             */
/*   Updated: 2024/09/02 02:01:36 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Zombie.hpp"

int main()
{
	Zombie* ZombieArr = ZombieHorde(5, "Zombie");
	int i = 0;

	while (i < 5)
		ZombieArr[i++].announce();
	delete[] ZombieArr;
	return 0;
}