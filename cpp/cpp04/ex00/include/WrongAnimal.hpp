/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 17:16:28 by vandre            #+#    #+#             */
/*   Updated: 2024/09/11 17:32:26 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

class WrongAnimal
{
	public:
		WrongAnimal();
		WrongAnimal(const WrongAnimal &wrongAnimal);
		WrongAnimal &operator=(const WrongAnimal &wrongAnimal);
		~WrongAnimal();
		void makeSound() const;
		std::string getType() const;
	protected:
		std::string _type;
};