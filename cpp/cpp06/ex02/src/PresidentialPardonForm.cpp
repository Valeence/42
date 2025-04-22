/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 16:23:03 by vandre            #+#    #+#             */
/*   Updated: 2024/10/31 00:20:28 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm() : AForm("Presidential", 25, 5)
{
	_target = "untargeted";
}

PresidentialPardonForm::PresidentialPardonForm(std::string target) : AForm("Presidential", 25, 5)
{
	_target = target;
}

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm &form) : AForm(form)
{
	_target = form._target;
}

PresidentialPardonForm &PresidentialPardonForm::operator=(const PresidentialPardonForm &form)
{
	if (this == &form)
		return *this;
	AForm::operator=(form);
	_target = form._target;
	return *this;
}

PresidentialPardonForm::~PresidentialPardonForm()
{
	std::cout << "Presidential deleted" << std::endl; 
}

void PresidentialPardonForm::exec() const
{
	std::cout << _target << " has been pardoned by Zaphod Beeblebrox" << std::endl;
}
