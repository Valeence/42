/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 12:20:36 by vandre            #+#    #+#             */
/*   Updated: 2024/09/03 00:34:31 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/HumanB.hpp"

HumanB::HumanB()
	: B_name("default"), B_weapon(NULL)
{
}

HumanB::HumanB(std::string name)
	: B_name(name)
{
}

void HumanB::attack()
{
	std::cout << this->B_name << " attacks with their " << this->B_weapon->getType() << std::endl;
}

void HumanB::setWeapon(Weapon &weapon)
{
	this->B_weapon = &weapon;
}