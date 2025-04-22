/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 20:51:27 by vandre            #+#    #+#             */
/*   Updated: 2024/09/01 22:28:27 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Zombie.hpp"

Zombie::Zombie()
{
	Zombie::name = "Default";
	std::cout << name << " has been created" << std::endl;
}

Zombie::Zombie(std::string name) : name(name)
{
	std::cout << "Zombie " << name << " has been created" << std::endl;
}

Zombie::~Zombie()
{
	std::cout << "Zombie : " << name << " has been destroyed" << std::endl;
}

void Zombie::announce(void)
{
	std::cout << name << ": " << "BraiiiiiiinnnzzzZ..." << std::endl;
}