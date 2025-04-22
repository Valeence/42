/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 11:23:15 by vandre            #+#    #+#             */
/*   Updated: 2025/02/07 15:18:05 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ClapTrap.hpp"
#include "../include/ScavTrap.hpp"

int main()
{
    ScavTrap valence("Violence");
    ScavTrap zack("Pabil");
    ClapTrap clap("Clap");

    clap.attack(valence.getName());
    valence.attack(zack.getName());
    zack.attack(valence.getName());

    valence.takeDamage(5);
    zack.takeDamage(10);

    valence.beRepaired(3);
    zack.beRepaired(7);

    valence.attack(zack.getName());
    zack.attack(valence.getName());

    valence.takeDamage(20);
    zack.takeDamage(15);

    valence.beRepaired(10);
    zack.beRepaired(5);

    valence.guardGate();
    zack.guardGate();

    valence.takeDamage(100); // Devrait mettre Valence à 0 HP
    valence.beRepaired(50);  // Devrait ne pas fonctionner car Valence est à 0 HP
    valence.attack("Pabil"); // Devrait ne pas fonctionner car Valence est à 0 HP

    return 0;
}