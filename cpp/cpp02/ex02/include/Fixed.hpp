/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 12:02:45 by vandre            #+#    #+#             */
/*   Updated: 2024/12/09 00:46:58 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
# define FIXED_HPP

# include <iostream>
# include <cmath>


class Fixed
{
	private:
                static const int	_bits = 8;
                int		        _value;
                int _nb;
                static const int espilon = 1;

	public:
                Fixed();
                Fixed(int const k);
                Fixed(float const f);
				Fixed(Fixed const &copy);
                ~Fixed();
                
                int getRawBits(void) const;
                void setRawBits( int const raw );
                
                float toFloat( void ) const;
                int toInt( void ) const;
                
                Fixed&  operator = (const Fixed &a);

                bool    operator == (const Fixed &other) const;
                bool    operator != (const Fixed &other) const;
                bool    operator < (const Fixed &other) const;
                bool    operator > (const Fixed &other) const;
                bool    operator <= (const Fixed &other) const;
                bool    operator >= (const Fixed &other) const;
        
                Fixed   operator + (const Fixed &other) const;
                Fixed   operator - (const Fixed &other) const;
                Fixed   operator * (const Fixed &other) const;
                Fixed   operator / (const Fixed &other) const;

                Fixed&  operator++();
                Fixed&  operator--();
                Fixed   operator++(int);
                Fixed   operator--(int);

                const       Fixed& max(Fixed &fixed_a, Fixed &fixed_b);
                static const Fixed& max(Fixed const &fixed_a, Fixed const &fixed_b);
                const       Fixed& min(Fixed &fixed_a, Fixed &fixed_b);
                static const Fixed& min(Fixed const &fixed_a, Fixed const &fixed_b);
};

std::ostream &operator<<(std::ostream &out, Fixed const &fixed);

#endif