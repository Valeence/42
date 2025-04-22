/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 12:01:59 by vandre            #+#    #+#             */
/*   Updated: 2024/12/11 01:45:14 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Fixed.hpp"

Fixed::Fixed() 
{
    std::cout << "Default constructor called" << std::endl;
    Fixed::_value = 0;
}

Fixed::Fixed(int const k)
{
    std::cout << "Int constructor called" << std::endl;
    this->_value = k * (1 << _bits); // << k * 256  8bits
}

Fixed::Fixed(float const f)
{ 
    std::cout << "Float constructor called" << std::endl;
    this->_value = roundf(f * (1 << _bits)); // arrondir 
    
}

Fixed::Fixed(Fixed const &copy) 
{
    std::cout << "Copy constructor called" << std::endl;
   *this = copy;
}

Fixed::~Fixed()
{
    std::cout << "Destructor called" << std::endl;
}

float Fixed::toFloat(void) const
{
    return static_cast<float>(this->_value) / (1 << _bits);
}

int Fixed::toInt( void ) const
{

        return (this->_value / (1 << _bits));
}

int Fixed::getRawBits(void) const
{
    return this->_value;
}

void Fixed::setRawBits(int const raw) 
{
    this->_value = raw;
    std::cout << this->_value << std::endl;
}

Fixed &Fixed::operator=(const Fixed &other) throw() 
{
    std::cout << "Copy assignment operator called" << std::endl;
    if (this != &other)
        this->_value = other.getRawBits();
    return *this;  
}

std::ostream &operator<<(std::ostream &out, Fixed const &fixed)
{
    out << fixed.toFloat();
    return out;
}