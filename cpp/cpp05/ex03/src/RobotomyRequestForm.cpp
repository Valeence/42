/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 16:23:06 by vandre            #+#    #+#             */
/*   Updated: 2024/10/31 00:26:16 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/RobotomyRequestForm.hpp"
#include <stdlib.h>
#include <time.h>


RobotomyRequestForm::RobotomyRequestForm() : AForm("Robotomy", 72, 45)
{
	_target = "untargeted";
}

RobotomyRequestForm::RobotomyRequestForm(std::string target) : AForm("Robotomy", 72, 45)
{
	_target = target;
}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm &form) : AForm(form)
{
	_target = form._target;
}

RobotomyRequestForm &RobotomyRequestForm::operator=(const RobotomyRequestForm &form)
{
	if (this == &form)
		return *this;
	AForm::operator=(form);
	_target = form._target;
	return *this;
}

RobotomyRequestForm::~RobotomyRequestForm()
{
	std::cout << "Robotomy deleted" << std::endl; 
}

void RobotomyRequestForm::exec() const
{
    static bool graineInitialisee = false;
    if (!graineInitialisee) {
        std::srand(::time(NULL));
        graineInitialisee = true;
    }

    if (std::rand() % 2) {
        std::cout << "Succès : " << _target << " a été robotomisé avec succès !" << std::endl;
    } else {
        std::cout << "Échec : " << _target << " n'a pas pu être robotomisé." << std::endl;
    }
}
