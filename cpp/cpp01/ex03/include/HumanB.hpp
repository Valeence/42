/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 12:22:00 by vandre            #+#    #+#             */
/*   Updated: 2024/09/03 00:29:55 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.hpp"

class HumanB
{
    public:
		HumanB();
		HumanB(std::string name);
		void setWeapon(Weapon &weapon);
		void attack();
    private:
		std::string B_name;
		Weapon *B_weapon;
};
