/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 12:20:46 by vandre            #+#    #+#             */
/*   Updated: 2024/12/06 02:05:28 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.hpp"

class HumanA
{
    public:
		HumanA(std::string name , Weapon &weapon);
		~HumanA();
		void attack();
    private:
		std::string A_name;
		Weapon &A_weapon;
};