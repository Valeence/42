/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 16:23:09 by vandre            #+#    #+#             */
/*   Updated: 2024/10/31 00:26:31 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm() : AForm("Shrubbery", 145, 137)
{
	_target = "untargeted";
}

ShrubberyCreationForm::ShrubberyCreationForm(std::string target) : AForm("Shrubbery", 145, 137)
{
	_target = target;
}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm &form) : AForm(form)
{
	_target = form._target;
}

ShrubberyCreationForm &ShrubberyCreationForm::operator=(const ShrubberyCreationForm &form)
{
	if (this == &form)
		return *this;
	AForm::operator=(form);
	_target = form._target;
	return *this;
}

ShrubberyCreationForm::~ShrubberyCreationForm()
{
	std::cout << "Shrubbery deleted" << std::endl; 
}

void ShrubberyCreationForm::exec() const
{
	std::ofstream fichier((_target + "_shrubbery").c_str());
	if (fichier.is_open())
	{
		fichier << "       _-_\n";
		fichier << "    /~~   ~~\\\n";
		fichier << " /~~         ~~\\\n";
		fichier << "{               }\n";
		fichier << " \\  _-     -_  /\n";
		fichier << "   ~  \\\\ //  ~\n";
		fichier << "_- -   | | _- _\n";
		fichier <<  "  _ -  | |   -_\n";
		fichier << "      // \\\\" << std::endl;
		fichier.close();
	}
	else
		std::cerr << "Error: could not open file" << std::endl;
}

