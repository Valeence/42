/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 01:33:16 by vandre            #+#    #+#             */
/*   Updated: 2024/09/02 01:37:41 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Zombie.hpp"

Zombie::Zombie()
{
	Zombie::name = "default";
}

Zombie::Zombie(std::string name)
{
	Zombie::name = name;
}

Zombie::~Zombie()
{
	std::cout << Zombie::name << " is dead" << std::endl;
}

void Zombie::announce(void)
{
	std::cout << Zombie::name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}