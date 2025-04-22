/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 15:03:53 by vandre            #+#    #+#             */
/*   Updated: 2024/12/23 02:23:55 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Intern.hpp"
#include "../include/ShrubberyCreationForm.hpp"
#include "../include/PresidentialPardonForm.hpp"
#include "../include/RobotomyRequestForm.hpp"

Intern::Intern()
{
	std::cout << "Intern default constructor called" << std::endl;
}

Intern::Intern(const Intern &cpy)
{
	std::cout << "Intern copy constructor called" << std::endl;
	(void)cpy;
}

Intern &Intern::operator=(const Intern &cpy)
{
	std::cout << "Intern assignation operator called" << std::endl;
	if (this == &cpy)
		return *this;
	return *this;
}

Intern::~Intern()
{
	std::cout << "Intern destructor called" << std::endl;
}

AForm* Intern::makeForm(std::string name, std::string target)
{
	std::string formName[3] = {
		"shrubbery creation",
		"robotomy request",
		"presidential pardon"
	};
	
	AForm* (*functptr[3])(std::string) = {
		Intern::createShrubbery,
		Intern::createRobotomy,
		Intern::createPresidential
	};
	
	for (int i = 0; i < 3; i++)
	{
		if (formName[i] == name)
		{
			std::cout << "Intern creates " << name << std::endl;
			return functptr[i](target);
		}
	}
	std::cerr << "Error form " << name << " not found" << std::endl;
	return NULL;
}

AForm* Intern::createShrubbery(std::string target)
{
	return new ShrubberyCreationForm(target);
}

AForm* Intern::createPresidential(std::string target)
{
	return new PresidentialPardonForm(target);
}

AForm* Intern::createRobotomy(std::string target)
{
	return new RobotomyRequestForm(target);
}