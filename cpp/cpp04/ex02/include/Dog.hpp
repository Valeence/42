/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:45:52 by vandre            #+#    #+#             */
/*   Updated: 2024/09/12 19:20:42 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "Animal.hpp"
#include "Brain.hpp"

class Dog : public Animal
{
	public:
        Dog();
		Dog(const Dog &dog);
		Dog &operator=(const Dog &dog);
		~Dog();
		
		virtual void makeSound() const;
		Brain* getBrain() const;
	
	private:
		Brain* _brain;
};