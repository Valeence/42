/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:41:20 by vandre            #+#    #+#             */
/*   Updated: 2025/02/05 17:49:55 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ScavTrap.hpp"

ScavTrap::ScavTrap()
{
	_name = "Default ScavTrap";
	_hit = 100;
	_energy = 50;
	_attack = 20;
	std::cout << "Default ScavTrap create" << std::endl;
}

ScavTrap::ScavTrap(std::string name)
{
	_name = name;
	_hit = 100;
	_energy = 50;
	_attack = 20;
	std::cout << "ScavTrap " << _name << " create" << std::endl;
}


ScavTrap::ScavTrap(const ScavTrap &cpy)
    : ClapTrap(cpy)
{
    std::cout << "ScavTrap " << cpy._name << " created by copy" << std::endl;
}

ScavTrap &ScavTrap::operator= (const ScavTrap &cpy)
{
	if (this != &cpy)
	{
		_name = cpy._name;
		_hit = cpy._hit;
		_energy = cpy._energy;
		_attack = cpy._attack;
	}
	std::cout << "ScavTrap " << cpy._name << " create by operator" << std::endl;
	return *this;
}

ScavTrap::~ScavTrap()
{
	std::cout << "ScavTrap " << ScavTrap::_name << " destructed" << std::endl;
}

void ScavTrap::attack(const std::string &target)
{
    if(_energy <= 0)
    {
        std::cout << "ScavTrap : (" <<this->_name << ") has no energy to attack" << std::endl;
        return;
    }
    else if (this->_hit <= 0)
    {
        std::cout << "ScavTrap : (" << this->_name << "), DEAD !!! " << std::endl;
        return;
    }
    else
    {
        this->_energy -= 1;
        std::cout << "ScavTrap : (" << this->_name << "), ATTACK (" << target << ") causing " << this->_hit << " points of damage he has left " << this->_energy << " energy points" << std::endl;
        return;
    }
}

void ScavTrap::guardGate()
{
    if(_energy <= 0)
    {
        std::cout << this->_name << "has no energy to guard" << std::endl;
        return;
    }
    else if(this->_hit <= 0)
    {
        std::cout << "ScavTrap : (" << this->_name << "), 0 points of life for guard" << std::endl;
        return;
    }
    std::cout << "ScavTrap : (" << this->_name << "), Guard !!!" << std::endl;
    this->_energy -= 1;


}