/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 11:23:15 by vandre            #+#    #+#             */
/*   Updated: 2025/02/07 15:25:57 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ClapTrap.hpp"
#include "../include/ScavTrap.hpp"
#include "../include/FragTrap.hpp"


int main() {

    std::cout << "\n=== Création des FragTraps ===" << std::endl;
    FragTrap frag1("Fraggy");
    FragTrap frag2("Fragger");

    std::cout << "\n=== Test des capacités des FragTraps ===" << std::endl;
    frag1.attack(frag2.getName());
    frag1.takeDamage(20);
    frag1.beRepaired(10);
    frag1.highFivesGuys();

    std::cout << "\n=== Test de l'assignation ===" << std::endl;
    FragTrap frag3("AnotherFrag");
    frag3 = frag1;

    std::cout << "\n=== Test des limites ===" << std::endl;
    frag1.takeDamage(100); // Devrait mettre Fraggy à 0 HP
    frag1.attack("target"); // Devrait ne pas fonctionner car Fraggy est à 0 HP
    frag1.beRepaired(50);  // Devrait ne pas fonctionner car Fraggy est à 0 HP

    std::cout << "\n=== Fin du programme ===" << std::endl;
    return 0;
}