/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:50:43 by vandre            #+#    #+#             */
/*   Updated: 2024/09/12 19:23:35 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Animal.hpp"

Animal::Animal()
{
	Animal::_type = "animal";
	std::cout << "constructor animal called" << std::endl;
}

Animal::Animal(const Animal &animal)
{
	Animal::_type = animal._type;
	std::cout << "Copy constructor animal called" << std::endl;
}

Animal &Animal::operator=(const Animal &animal)
{
	Animal::_type = animal._type;
	std::cout << "Assignation operator animal called" << std::endl;
	return (*this);
}

Animal::~Animal()
{
	std::cout << "destructor animal called" << std::endl;
}

std::string Animal::getType() const
{
    return (this->_type);
}