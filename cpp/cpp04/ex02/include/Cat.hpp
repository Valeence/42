/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:44:41 by vandre            #+#    #+#             */
/*   Updated: 2024/09/12 19:20:35 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "Animal.hpp"
#include "Brain.hpp"

class Cat : public Animal
{
	public:
		Cat();
		Cat(const Cat &cat);
		Cat &operator=(const Cat &cat);
		~Cat();
        virtual void makeSound() const;
		Brain* getBrain() const;
	private:
		Brain* _brain;
};