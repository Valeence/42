/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ZombieHorde.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 01:33:21 by vandre            #+#    #+#             */
/*   Updated: 2024/09/02 02:06:05 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Zombie.hpp"

Zombie* ZombieHorde(int n, std::string name) {
    int i = 0;
    Zombie* ZombieArr = new Zombie[n];

    while (i < n)
	{
		new (&ZombieArr[i]) Zombie(name);
		i++;
	}
		
    return ZombieArr;
}