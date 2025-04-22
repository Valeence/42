/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 12:02:45 by vandre            #+#    #+#             */
/*   Updated: 2024/12/08 23:43:42 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
# define FIXED_HPP

# include <iostream>


class Fixed
{
	private:
                static const int	_bits = 8;
                int		        _value;

	public:
                Fixed();
                Fixed(int const k);
				Fixed(Fixed const &copy);
                Fixed &operator=(Fixed const &other);
                ~Fixed();
                int getRawBits(void) const;
                void setRawBits( int const raw );
};

#endif