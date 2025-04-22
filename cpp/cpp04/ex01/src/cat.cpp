/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:57:44 by vandre            #+#    #+#             */
/*   Updated: 2025/02/07 18:52:58 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Cat.hpp"

Cat::Cat() {
	_type = "Cat";
	_brain = new Brain();
	std::cout << "Constructor cat called" << std::endl;
}

Cat::Cat(const Cat& cat) : Animal(cat) {
	_brain = new Brain(*cat._brain); //deep copy
	std::cout << "Copy constructor cat called" << std::endl;
}

Cat& Cat::operator=(const Cat& cat) {
	if (this != &cat) {
		Animal::operator=(cat);
		delete _brain;
		_brain = new Brain(*cat._brain);
	}
	std::cout << "Assignment operator cat called" << std::endl;
	return *this;
}

Cat::~Cat() {
	std::cout << "Destructor cat called" << std::endl;
	delete _brain;
}

void Cat::makeSound() const {
	std::cout << "Miaou Miaou" << std::endl;
}

Brain* Cat::getBrain() const {
	return _brain;
}
