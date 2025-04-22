/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 12:20:23 by vandre            #+#    #+#             */
/*   Updated: 2024/12/06 02:05:38 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/HumanA.hpp"

HumanA::HumanA(std::string name, Weapon &weapon) : A_name(name), A_weapon(weapon)
{
}

HumanA::~HumanA()
{
}

void HumanA::attack()
{
	std::cout << this->A_name << " attacks with their " << this->A_weapon.getType() << std::endl;
}
