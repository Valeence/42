/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:48:14 by vandre            #+#    #+#             */
/*   Updated: 2024/10/31 01:05:32 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Bureaucrat.hpp"

Bureaucrat::Bureaucrat() : _name("default"), _grade(150)
{
	std::cout << "Bureaucrat " << _name << " created, his grade is " << _grade << std::endl;
}

Bureaucrat::~Bureaucrat()
{
	std::cout << "Bureaucrat " << _name << " destroyed" << std::endl;
}

Bureaucrat::Bureaucrat(std::string name, int grade) : _name(name), _grade(grade)
{
	if (_grade > 150)
		throw Bureaucrat::GradeTooLowException();
	else if (_grade < 1)
		throw Bureaucrat::GradeTooHighException();
	std::cout << "Bureaucrat " << _name << " created, his grade is " << _grade << std::endl;
}

std::string Bureaucrat::get_name() const 
{
	return (this->_name);
}

int Bureaucrat::get_grade() const
{
	return (this->_grade);
}

void Bureaucrat::executeForm(AForm const & form)
{
	if (this->get_grade() <= form.get_grade_to_execute())
	{
		form.execute(*this);
		std::cout << this->get_name() << " executed " << form.get_name() << std::endl;
	}
	else
		std::cout << this->get_name() << " couldnt execute " << form.get_name() << std::endl;
}

void Bureaucrat::increment_grade()
{
	_grade--;
	if (_grade < 1)
		throw Bureaucrat::GradeTooHighException();
}

void Bureaucrat::decrement_grade()
{
	_grade++;
	if (_grade > 150)
		throw Bureaucrat::GradeTooLowException();
}

void Bureaucrat::signForm(AForm &form)
{
	try
	{
		form.be_signed(*this);
		std::cout << get_name() << " signed " << form.get_name() << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cout << get_name() << " couldn't sign " << form.get_name() << " because " << e.what() << std::endl;
	}
}

const char *Bureaucrat::GradeTooHighException::what() const throw()
{
	return (" Bureaucrat Grade is too high");
}

const char *Bureaucrat::GradeTooLowException::what() const throw()
{
	return ("Bureaucrat Grade is too low");
}

std::ostream &operator<<(std::ostream &str, Bureaucrat const &bureaucrat)
{
    return (str << bureaucrat.get_name() << ", bureaucrat grade " << bureaucrat.get_grade() << std::endl);
}
