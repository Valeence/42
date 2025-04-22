/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:48:14 by vandre            #+#    #+#             */
/*   Updated: 2024/10/12 06:47:11 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Bureaucrat.hpp"

Bureaucrat::Bureaucrat() : _name("default"), _grade(150)
{
	std::cout << "Bureaucrat " << _name << " created, his grade is " << _grade << std::endl;
}

Bureaucrat::Bureaucrat(std::string name, int grade) : _name(name), _grade(grade)
{
	if (_grade > 150)
		throw Bureaucrat::GradeTooLowException();
	else if (_grade < 1)
		throw Bureaucrat::GradeTooHighException();
	std::cout << "Bureaucrat " << _name << " created, his grade is " << _grade << std::endl;
}

Bureaucrat::Bureaucrat(Bureaucrat const &bureaucrat) : _name(bureaucrat._name), _grade(bureaucrat._grade)
{
	std::cout << "Bureaucrat " << _name << " created, his grade is " << _grade << std::endl;
}

Bureaucrat &Bureaucrat::operator=(Bureaucrat const &bureaucrat)
{ 
	_grade = bureaucrat._grade;
	return (*this);
}

Bureaucrat::~Bureaucrat()
{
	std::cout << "Bureaucrat " << _name << " destroyed" << std::endl;
}

std::string Bureaucrat::get_name() const 
{
	return (this->_name);
}

int Bureaucrat::get_grade() const
{
	return (this->_grade);
}

void Bureaucrat::increment_grade() {
    if (_grade <= 1) {
        throw Bureaucrat::GradeTooHighException();
    }
    _grade--;
    std::cout << _name << " incremented to grade " << _grade << std::endl;
}

void Bureaucrat::decrement_grade() {
    if (_grade >= 150) {
        throw Bureaucrat::GradeTooLowException();
    }
    _grade++;
    std::cout << _name << " decremented to grade " << _grade << std::endl;
}

const char *Bureaucrat::GradeTooHighException::what() const throw()
{
	return ("Grade is too high");
}

const char *Bureaucrat::GradeTooLowException::what() const throw()
{
	return ("Grade is too low");
}

std::ostream &operator<<(std::ostream &str, Bureaucrat const &bureaucrat)
{
    return (str << bureaucrat.get_name() << ", bureaucrat grade " << bureaucrat.get_grade() << std::endl);
}
