/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:54:14 by vandre            #+#    #+#             */
/*   Updated: 2025/02/05 17:44:45 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/FragTrap.hpp"

FragTrap::FragTrap()
{
	_name = "Default FragTrap";
    _hit = 100;
    _energy = 100;
    _attack = 30; 
    std::cout << "Default FragTrap created" << std::endl;

}

FragTrap::FragTrap(std::string name) 
{
    _name = name;
    _hit = 100;
    _energy = 100;
    _attack = 30; 
    std::cout << "FragTrap : (" << name << ") created" << std::endl;
}

FragTrap::FragTrap(const FragTrap &cpy) 
    : ClapTrap(cpy)
{
    std::cout << "FragTrap created by copy" << std::endl;
}

FragTrap &FragTrap::operator= (const FragTrap &cpy) 
{
    if (this != &cpy) 
    {
        _name = cpy._name;
        _hit = cpy._hit;
        _energy = cpy._energy;
        _attack = cpy._attack;
    }
    std::cout << "FragTrap created by operator" << std::endl;
    return *this;
}

FragTrap::~FragTrap() 
{
    std::cout << "FragTrap destroyed" << std::endl;
}

void FragTrap::attack(const std::string &target)
{
    if(_energy <= 0)
    {
        std::cout << "FlagTrap : (" <<this->_name << ") has no energy to attack" << std::endl;
        return;
    }
    else if (this->_hit <= 0)
    {
        std::cout << "FlagTrap : (" << this->_name << "), DEAD !!! " << std::endl;
        return;
    }
    else
    {
        this->_energy -= 1;
        std::cout << "FlagTrap : (" << this->_name << "), ATTACK (" << target << ") causing " << this->_hit << " points of damage he has left " << this->_energy << " energy points" << std::endl;
        return;
    }
}

void FragTrap::highFivesGuys(void) {
    std::string highfive;
    std::cout << "do you accept the high five ? " << std::endl;
    std::cin >> highfive; 

    if(highfive == "yes") 
        std::cout << "nice you accepted the highfive" << std::endl;
    else if (highfive == "no") 
        std::cout << "you refused the highfive..." << std::endl;
    else 
        std::cout << "you reply is wrong" << std::endl;
}