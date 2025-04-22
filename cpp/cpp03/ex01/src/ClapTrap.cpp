/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 11:23:13 by vandre            #+#    #+#             */
/*   Updated: 2025/02/05 17:15:06 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ClapTrap.hpp"

ClapTrap::ClapTrap() {std::cout << "ClapTrap create" << std::endl;}

ClapTrap::ClapTrap(std::string name)
{
	_name = name;
	_hit = 10;
	_energy = 10;
	_attack = 0;
	std::cout << "ClapTrap " << name << " create" << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap &cpy)
{
	_name = cpy._name;
	_hit = cpy._hit;
	_energy = cpy._energy;
	_attack = cpy._attack;
	std::cout << "ClapTrap " << cpy._name << " create by copy" << std::endl;
}

ClapTrap &ClapTrap::operator= (const ClapTrap &cpy)
{
	if (this != &cpy)
	{
		_name = cpy._name;
		_hit = cpy._hit;
		_energy = cpy._energy;
		_attack = cpy._attack;
	}
	std::cout << "ClapTrap " << cpy._name << " create by operator" << std::endl;
	return *this;
}

ClapTrap::~ClapTrap() 
{
    std::cout << "ClapTrap destroyed" << std::endl;
}

void ClapTrap::takeDamage(unsigned int amount)
{    
    
    if (this->_hit == 0)
    {
        std::cout << "ClapTrap : (" << this->_name << "), DEAD !!! " << std::endl;
        return;
    }
    if(this->_hit <= amount)
    {
        this->_hit = 0;
        std::cout << "ClapTrap : (" << this->_name << "), TAKE " << amount << ", points of damages and so he died" << std::endl;
        return;
    }
    else
    {   
        this->_hit -= amount;
        std::cout << "ClapTrap : (" << this->_name << "), TAKE " << amount << ", points of damages, he has " << this->_hit << " life points"<< std::endl;
        return;
    }
}

void ClapTrap::attack(const std::string &target)
{
    
    if(this->_hit <= 0)
    {
        std::cout << "ClapTrap : (" << this->_name << "), DEAD !!! " << std::endl;
        return;
    }
    else if(_energy <= 0)
    {
        std::cout << "ClapTrap : (" <<this->_name << ") has no energy to attack" << std::endl;
        return;
    }
    else
    {
        this->_energy -= 1;
        std::cout << "ClapTrap : (" << this->_name << "), ATTACK (" << target << ") causing " << this->_attack << " points of damage he has left " << this->_energy << " energy points" << std::endl;
        return;
    }
}


void ClapTrap::beRepaired(unsigned int amount)
{
    if (this->_hit > 0)
    {
        this->_energy -= 1;
        this->_hit += amount;
        std::cout << "ClapTrap : (" << this->_name << "), repaired " << amount << ", points of life, he has " << this->_hit << " life points"<< std::endl;

    }
    else if (this->_energy <= 0)
    {
        std::cout << "ClapTrap : (" <<this->_name << ") has no energy to repaire" << std::endl;
    }
    else
    {
        std::cout << "ClapTrap : (" << this->_name << "), DEAD !!! " << std::endl;
        return;
    }
}

std::string ClapTrap::getName() const
{
	return _name;
}
