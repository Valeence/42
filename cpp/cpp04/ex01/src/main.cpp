/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:01:49 by vandre            #+#    #+#             */
/*   Updated: 2025/02/07 18:42:50 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Brain.hpp"
#include "../include/Animal.hpp"
#include "../include/Dog.hpp"
#include "../include/Cat.hpp"
#include "../include/WrongCat.hpp"
#include "../include/Brain.hpp"

#define NUM_ANIMALS 4

int main()
{
    std::cout << "\n=== Construction d'un tableau d'Animaux ===" << std::endl;

    Animal* animals[NUM_ANIMALS];

    for (int i = 0; i < NUM_ANIMALS / 2; ++i) {
        animals[i] = new Dog();
    }
    for (int i = NUM_ANIMALS / 2; i < NUM_ANIMALS; ++i) {
        animals[i] = new Cat();
    }

    std::cout << "\n=== Test des comportements des animaux ===" << std::endl;

    for (int i = 0; i < NUM_ANIMALS; ++i) {
        animals[i]->makeSound();
    }
    Dog testDog;
    for (int i = 0; i < 100; ++i) {
        testDog.getBrain()->setIdea(i, "hello");
    }
    for (int i = 0; i < 100; ++i) {
        std::cout << "Assigned Dog idea[" << i << "]: " << testDog.getBrain()->getIdea(i) << std::endl;
    }
    
    std::cout << "\n=== Destruction des Animaux ===" << std::endl;
    for (int i = 0; i < NUM_ANIMALS; ++i) {
        delete animals[i];
    }
    return 0;
}