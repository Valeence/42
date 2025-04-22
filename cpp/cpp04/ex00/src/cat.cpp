/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:57:44 by vandre            #+#    #+#             */
/*   Updated: 2024/09/12 11:16:52 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Cat.hpp"

Cat::Cat()
{
	_type = "Chat";
	std::cout << "constructor cat called" << std::endl;
}

Cat::Cat(const Cat &cat) : Animal(cat)
{
	std::cout << _type << "Copy constructor cat called" << std::endl;
}

Cat &Cat::operator=(const Cat &cat)
{
	_type = cat._type;
	std::cout << "Assignation operator cat called" << std::endl;
	return (*this);
}

Cat::~Cat()
{
	std::cout << "destructor cat called" << std::endl;
} 

void Cat::makeSound() const
{
	std::cout << "Miaouuu" << std::endl;
}