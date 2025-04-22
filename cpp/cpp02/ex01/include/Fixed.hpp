/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 12:02:45 by vandre            #+#    #+#             */
/*   Updated: 2024/12/11 01:38:35 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
# define FIXED_HPP

#include <iostream>
#include <cmath>

class Fixed
{
	private:
                static const int	_bits = 8;
                int		        _value;

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
                Fixed &operator=(Fixed const &other) throw();
};

std::ostream &operator<<(std::ostream &out, Fixed const &fixed);

#endif