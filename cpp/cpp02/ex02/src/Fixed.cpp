/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 12:01:59 by vandre            #+#    #+#             */
/*   Updated: 2024/12/11 02:01:41 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Fixed.hpp"

Fixed::Fixed() 
{
    Fixed::_value = 0;
}

Fixed::Fixed(int const k)
{
    this->_value = k * (1 << _bits);
}

Fixed::Fixed(float const f)
{ 
    this->_value = roundf(f * (1 << _bits));
    
}

Fixed::Fixed(Fixed const &copy) 
{
   *this = copy;
}

Fixed::~Fixed()
{
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
    //std::cout << this->_value << std::endl;
}

Fixed &Fixed::operator=(const Fixed &other)
{
    if (this != &other)
        this->_value = other.getRawBits();
    return *this;  
}

std::ostream &operator<<(std::ostream &out, Fixed const &fixed)
{
    out << fixed.toFloat();
    return out;
}

bool   Fixed::operator == (const Fixed &other) const
{
    if(this->toFloat() == other.toFloat())
        return (true);
    return (false);
}

bool   Fixed::operator != (const Fixed &other) const
{
    if(this->toFloat() != other.toFloat())
        return (true);
    return (false);
}

bool   Fixed::operator < (const Fixed &other) const
{
    if(this->toFloat() < other.toFloat())
        return (true);
    return (false);
}

bool   Fixed::operator > (const Fixed &other) const
{
    if(this->toFloat() > other.toFloat())
        return (true);
    return (false);
}

bool   Fixed::operator <= (const Fixed &other) const
{
    if(this->toFloat() <= other.toFloat())
        return (true);
    return (false);
}

bool   Fixed::operator >= (const Fixed &other) const
{
    if(this->toFloat() >= other.toFloat())
        return (true);
    return (false);
}

Fixed  Fixed::operator +(const Fixed &other) const
{
    return (this->toFloat() + other.toFloat());
}

Fixed  Fixed::operator -(const Fixed &other) const
{
    return (this->toFloat() - other.toFloat());
}

Fixed  Fixed::operator *(const Fixed &other) const
{
    return (this->toFloat() * other.toFloat());
}

Fixed  Fixed::operator /(const Fixed &other) const
{
    return (this->toFloat() / other.toFloat());
}

Fixed& Fixed::operator++()
{
    _value += espilon;   
    return(*this);
}

Fixed& Fixed::operator--()
{
    _value -= espilon;   
    return(*this);
}

Fixed Fixed::operator++(int)
{
    Fixed temp = *this;
    _value += espilon;   
    return(temp);
}

Fixed Fixed::operator--(int)
{
     Fixed temp = *this; 
    _nb -= espilon;   
    return(temp);
}

const Fixed& Fixed::max(Fixed &fixed_a, Fixed &fixed_b)
{
    if(fixed_a > fixed_b)
        return (fixed_a);
    return (fixed_b);
}


const Fixed& Fixed::max(Fixed const &fixed_a, Fixed const &fixed_b)
{
    if(fixed_a > fixed_b)
        return (fixed_a);
    return (fixed_b);
}

const Fixed& Fixed::min(Fixed &fixed_a, Fixed &fixed_b)
{
    if(fixed_a < fixed_b)
        return (fixed_a);
    return (fixed_b);
}

const Fixed& Fixed::min(Fixed const &fixed_a, Fixed const &fixed_b)
{
    if(fixed_a < fixed_b)
        return (fixed_a);
    return (fixed_b);
}