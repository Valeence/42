/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 20:51:20 by vandre            #+#    #+#             */
/*   Updated: 2024/12/04 02:47:52 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Zombie.hpp"

int main(void)
{
    std::cout << "============= stackZombies =============" << std::endl;
    Zombie    zombie1("Zombie1");
    zombie1.announce();
    std::cout << std::endl;
    randomChump("randomChumpZ");
    std::cout << std::endl;
    std::cout << "============= heapZombies ==============" << std::endl;
    Zombie    *heapZ;
    heapZ = newZombie("HeapZombie");
    heapZ->announce();
    delete(heapZ);

    return (0);
}