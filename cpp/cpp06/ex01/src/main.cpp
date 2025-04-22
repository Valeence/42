/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:47:43 by vandre            #+#    #+#             */
/*   Updated: 2024/10/12 06:47:32 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Bureaucrat.hpp"
#include "../include/Form.hpp"

int main() {
    std::cout << "=== Test: Création de Bureaucrat et Form ===" << std::endl;

    try {
        Bureaucrat b1("Alice", 10);
        Form f1("Form1", 15, 20);
        std::cout << b1;
        std::cout << f1;
    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }

    std::cout << "\n=== Test: Création avec des grades invalides ===" << std::endl;

    try {
        std::cout << std::endl;
        Bureaucrat b2("Bob", 0); // Trop haut
    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }

    try {
        Bureaucrat b3("Charlie", 151); // Trop bas
    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }

    try {
        Form f2("Form2", 0, 10); // Trop haut pour le grade de signature
    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }

    try {
        Form f3("Form3", 20, 160); // Trop bas pour le grade d'exécution
    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }

    std::cout << "\n=== Test: Signature de formulaire ===" << std::endl;

    try {
        std::cout << std::endl;
        Bureaucrat b4("David", 5);
        Form f4("Form4", 10, 30);
        std::cout << std::endl;
        std::cout << f4;
        b4.signForm(f4);
        std::cout << f4 << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }

    try {
        std::cout << std::endl;
        Bureaucrat b5("Eve", 50);
        Form f5("Form5", 10, 30);
        b5.signForm(f5); // Doit échouer
    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }

    std::cout << "\n=== Test: Incrémentation et décrémentation de grades ===" << std::endl;

    try {
        Bureaucrat b6("Frank", 2);
        std::cout << b6 << std::endl;
        b6.increment_grade(); // Passe à 1
        std::cout << b6 << std::endl;
        b6.increment_grade(); // Doit échouer (grade trop haut)
    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }
    try {
        std::cout << std::endl;
        Bureaucrat b7("Grace", 149);
        std::cout << b7 << std::endl;
        b7.decrement_grade(); // Passe à 150
        std::cout << b7 << std::endl;
        b7.decrement_grade(); // Doit échouer (grade trop bas)
    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }
    std::cout << "\n=== Test: Destruction des objets ===" << std::endl;

    try {
        Bureaucrat* b8 = new Bureaucrat("Hannah", 10);
        Form* f6 = new Form("Form6", 20, 40);

        std::cout << *b8;
        std::cout << *f6;

        delete b8;
        delete f6;
    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }
    return 0;
}