/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 20:48:20 by vandre            #+#    #+#             */
/*   Updated: 2024/09/01 21:59:29 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_H
# define ZOMBIE_H

# include <iostream>
# include <string>


class Zombie
{
public:
	Zombie();
	Zombie(std::string name);
	~Zombie();
	void announce(void);
private:
	std::string name;
};

Zombie* newZombie( std::string name );
void randomChump( std::string name );

#endif
