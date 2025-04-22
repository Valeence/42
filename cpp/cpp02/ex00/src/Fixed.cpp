/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 12:01:59 by vandre            #+#    #+#             */
/*   Updated: 2024/12/09 19:14:27 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/Fixed.hpp"

Fixed::Fixed() 
{
    std::cout << "Default constructor called" << std::endl;
    Fixed::_value = 0;
}

Fixed::Fixed(Fixed const &copy) 
{
    std::cout << "Copy constructor called" << std::endl;
   *this = copy;
}

Fixed &Fixed::operator=(const Fixed &other)
{
    std::cout << "Copy assignment operator called" << std::endl;
    if (this != &other)
        this->_value = other.getRawBits();
    return *this;  
}

Fixed::~Fixed()
{
    std::cout << "Destructor called" << std::endl;
}
int Fixed::getRawBits(void) const
{
    std::cout << "getRawBits member function called" << std::endl;
    return this->_value;
}

void Fixed::setRawBits(int const raw) 
{
    this->_value = raw;
    std::cout << this->_value << std::endl;
}
