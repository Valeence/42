/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:47:43 by vandre            #+#    #+#             */
/*   Updated: 2024/12/23 04:31:31 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Bureaucrat.hpp"
#include "../include/AForm.hpp"
#include "../include/ShrubberyCreationForm.hpp"
#include "../include/RobotomyRequestForm.hpp"
#include "../include/PresidentialPardonForm.hpp"
#include "../include/Intern.hpp"

int main()
{
    Intern someRandomIntern;
    AForm* rrf;
	AForm* rrff;
	AForm* rrfff;
	Bureaucrat vandre("vandre", 1);
    rrf = someRandomIntern.makeForm("robotomy request", "Bender");
    rrff = someRandomIntern.makeForm("presidential pardon", "Tester");
    rrfff = someRandomIntern.makeForm("shrubbery creation", "Tueur");
	vandre.signForm(*rrf);
	vandre.signForm(*rrff);
	vandre.signForm(*rrfff);
	vandre.executeForm(*rrf);
	vandre.executeForm(*rrff);
	vandre.executeForm(*rrfff);

    delete rrf;
	delete rrff;
	delete rrfff;
	
    return 0;
}