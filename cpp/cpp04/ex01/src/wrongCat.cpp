/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrongCat.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:57:44 by vandre            #+#    #+#             */
/*   Updated: 2024/09/12 11:48:04 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/WrongCat.hpp"

WrongCat::WrongCat()
{
	_type = "Mauvais Chat";
	std::cout << "Wrong Cat create" << std::endl;
}

WrongCat::~WrongCat()
{
	std::cout << "Wrong Cat destroy" << std::endl;
} 

WrongCat::WrongCat(const WrongCat &wrongCat) : WrongAnimal(wrongCat)
{
	std::cout << _type << "Copy constructor wrong cat called" << std::endl;
}

WrongCat &WrongCat::operator=(const WrongCat &wrongCat)
{
	_type = wrongCat._type;
	std::cout << "Assignation operator wrong cat called" << std::endl;
	return (*this);
}

void WrongCat::makeSound() const
{
	std::cout << "Miahooo wrong cat" << std::endl;
}