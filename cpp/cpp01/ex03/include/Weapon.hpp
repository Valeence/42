/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:27:14 by vandre            #+#    #+#             */
/*   Updated: 2024/12/06 02:28:53 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEAPON_HPP
# define WEAPON_HPP

#include <string>
#include <iostream>

class Weapon
{
	public:
		Weapon();
		Weapon(std::string type);
		~Weapon();
		const std::string &getType(void);
		void setType(std::string type);	
	private:
        std::string w_type;
};

#endif