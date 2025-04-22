/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 12:22:58 by vandre            #+#    #+#             */
/*   Updated: 2024/12/06 02:28:45 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Weapon.hpp"

Weapon::Weapon() {
    this->w_type = "un pistoulet";
}

Weapon::~Weapon()
{

}

Weapon::Weapon(std::string type)
{
	this->w_type = type;
}

const std::string &Weapon::getType(void)
{
    return this->w_type;
}

void Weapon::setType(std::string type)
{
    w_type = type;    
}