/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:45:52 by vandre            #+#    #+#             */
/*   Updated: 2024/09/11 17:13:32 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"

class Dog : public Animal
{
	public:
        Dog();
		Dog(const Dog &dog);
		Dog &operator=(const Dog &dog);
		~Dog();
	    virtual void makeSound() const;
};