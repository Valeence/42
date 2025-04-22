/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:47:43 by vandre            #+#    #+#             */
/*   Updated: 2025/02/25 16:03:51 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Bureaucrat.hpp"
#include "../include/AForm.hpp"
#include "../include/ShrubberyCreationForm.hpp"
#include "../include/RobotomyRequestForm.hpp"
#include "../include/PresidentialPardonForm.hpp"

int main()
{
        ShrubberyCreationForm Shrubbery("home");
        //RobotomyRequestForm Shrubbery("robot");
        //PresidentialPardonForm Shrubbery("president");
        std::cout << "---------------------------------------------------------" << std::endl;
        Bureaucrat vandre("Valence", 25);
        Bureaucrat aleee("Alejandra", 5);
        std::cout << "---------------------------------------------------------" << std::endl;
    try
	{
        std::cout << Shrubbery;
        vandre.signForm(Shrubbery);
        std::cout << Shrubbery;
        vandre.executeForm(Shrubbery);
        std::cout << Shrubbery;
        aleee.executeForm(Shrubbery);
        std::cout << "---------------------------------------------------------" << std::endl;
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}