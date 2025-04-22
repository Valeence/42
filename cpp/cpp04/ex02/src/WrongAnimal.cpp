/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 17:17:25 by vandre            #+#    #+#             */
/*   Updated: 2024/09/12 11:48:18 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/WrongAnimal.hpp"

WrongAnimal::WrongAnimal()
{
	_type = "wrong animal";
	std::cout << "constructor wrong animal called" << std::endl;
}

WrongAnimal::WrongAnimal(const WrongAnimal &wrongAnimal)
{
	_type = wrongAnimal._type;
	std::cout << "Copy constructor wrong animal called" << std::endl;
}

WrongAnimal &WrongAnimal::operator=(const WrongAnimal &wrongAnimal)
{
	_type = wrongAnimal._type;
	std::cout << "Assignation operator wrong animal called" << std::endl;
	return (*this);
}

WrongAnimal::~WrongAnimal()
{
	std::cout << "destructor wrong animal called" << std::endl;
}

void WrongAnimal::makeSound() const
{
	std::cout << "Grzgrzzz wrong animal..." << std::endl;
}

std::string WrongAnimal::getType() const
{
    return (this->_type);
}