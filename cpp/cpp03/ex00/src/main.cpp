/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 11:23:15 by vandre            #+#    #+#             */
/*   Updated: 2024/09/09 14:28:37 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ClapTrap.hpp"
#include <sstream>

int main() {
    std::cout << "=== Création des ClapTraps ===" << std::endl;

    ClapTrap clap1;                        // Constructeur par défaut
    ClapTrap clap2("Clappy");              // Constructeur paramétré
    ClapTrap clap3(clap2);                 // Constructeur de recopie

    std::cout << "\n=== Test de l'opérateur d'affectation ===" << std::endl;
    ClapTrap clap4;
    clap4 = clap2;

    std::cout << "\n=== Test des actions ===" << std::endl;

    // Attack test
    clap2.attack("Dummy Target");          // ClapTrap Clappy attaque Dummy Target
    clap2.takeDamage(4);                   // ClapTrap Clappy perd 4 HP
    clap2.beRepaired(6);                   // ClapTrap Clappy regagne 6 HP

    // Overdamage
    clap2.takeDamage(100);                 // ClapTrap Clappy subit des dégâts qui réduisent ses HP à 0
    clap2.attack("Another Target");        // ClapTrap Clappy tente d'attaquer sans HP

    std::cout << "\n=== Test de la limite de réparation ===" << std::endl;

    ClapTrap clap5("Medic");
    clap5.beRepaired(60);                  // Devrait se limiter à un maximum de 50 HP

    std::cout << "\n=== Test de l'énergie ===" << std::endl;

    ClapTrap clap6("Exhausted");
	ClapTrap clap7("TargetClap");
	std::cout << std::endl;

    for (int i = 0; i < 12; ++i) {
        std::cout << "Attaque " << (i + 1) << " : ";
        clap6.attack(clap7.getName());     // clap6 attaque TargetClap (nom récupéré via getName)
    }
    std::cout << "\n=== Fin du programme et destruction ===" << std::endl;

    return 0;
}
