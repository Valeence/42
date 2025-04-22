/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 12:14:38 by vandre            #+#    #+#             */
/*   Updated: 2024/09/12 19:01:29 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Brain.hpp"

Brain::Brain()
{
    for (int i = 0; i < 100; ++i) {
        ideas[i] = "default idea";
    }
    std::cout << "Constructor Brain called" << std::endl;
}

Brain::~Brain()
{
    std::cout << "Destructor Brain called" << std::endl;
}

Brain::Brain(const Brain& other)
{
    for (int i = 0; i < 100; ++i) {
        ideas[i] = other.ideas[i];
    }
    std::cout << "Copy constructor Brain called" << std::endl;
}

Brain& Brain::operator=(const Brain& other)
{
	if (this != &other)
	{
		for (int i = 0; i < 100; ++i)
            ideas[i] = other.ideas[i];
    }
    std::cout << "operator= Brain called" << std::endl;
    return *this;
}

void Brain::setIdea(int index, std::string idea)
{
    if (index >= 0 && index < 100) {
        ideas[index] = idea;
    }
}

std::string Brain::getIdea(int index) const
{
    if (index >= 0 && index < 100) {
        return this->ideas[index];
    }
    return "";
}