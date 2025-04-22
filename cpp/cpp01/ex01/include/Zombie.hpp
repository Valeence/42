/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 01:33:35 by vandre            #+#    #+#             */
/*   Updated: 2024/09/02 01:53:18 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP

# include <iostream>
# include <string>

class Zombie
{
public:
	Zombie();
	Zombie(std::string name);
	~Zombie();
	void announce();
private:
	std::string name;
};

Zombie* ZombieHorde(int N, std::string name);

#endif