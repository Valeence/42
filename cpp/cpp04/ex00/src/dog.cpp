/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:58:06 by vandre            #+#    #+#             */
/*   Updated: 2024/09/12 11:16:35 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Dog.hpp"

Dog::Dog()
{
	_type = "Chien";
	std::cout << "constructor dog called" << std::endl;
}

Dog::Dog(const Dog &dog) : Animal(dog)
{
	std::cout << _type << "Copy constructor dog called" << std::endl;
}

Dog &Dog::operator=(const Dog &dog)
{
	_type = dog._type;
	std::cout << "Assignation operator dog called" << std::endl;
	return (*this);
}

Dog::~Dog()
{
	std::cout << "destructor dog called" << std::endl;
}
void Dog::makeSound() const
{
	std::cout << "Ouaf Ouaf" << std::endl;
}