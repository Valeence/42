/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:16:06 by vandre            #+#    #+#             */
/*   Updated: 2024/09/12 19:24:21 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMAL_HPP
# define ANIMAL_HPP

#include <iostream>

class Animal
{
	public:
		Animal();
		Animal(const Animal &animal);
		Animal &operator=(const Animal &animal);
		virtual ~Animal();
		virtual void makeSound() const = 0;
		std::string getType() const;
	protected:
		std::string _type;
};

#endif