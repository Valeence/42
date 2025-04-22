/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 00:35:29 by vandre            #+#    #+#             */
/*   Updated: 2024/10/31 00:25:57 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/AForm.hpp"

AForm::AForm() : _name("default"), _signed(false), _grade_to_sign(5), _grade_to_execute(5)
{
    std::cout << "Form " << _name << " created, grade to sign: " << _grade_to_sign
        << ", grade to execute: " << _grade_to_execute << std::endl;
}

AForm::AForm(std::string name, int grade_to_sign, int grade_to_execute) 
	: _name(name), _signed(false), _grade_to_sign(grade_to_sign), _grade_to_execute(grade_to_execute)
{
    std::cout << "Form " << _name << " created, grade to sign: " << _grade_to_sign
		<< ", grade to execute: " << _grade_to_execute << std::endl;
	if (_grade_to_sign > 150 || _grade_to_execute > 150)
		throw AForm::GradeTooLowException();
	else if (_grade_to_sign < 1 || _grade_to_execute < 1)
		throw AForm::GradeTooHighException();
}

AForm::AForm(const AForm &form) : _name(form._name), _signed(form._signed),
	_grade_to_sign(form._grade_to_sign), _grade_to_execute(form._grade_to_execute)
{
	std::cout << "Form " << _name << " created, grade to sign: " << _grade_to_sign
		<< ", grade to execute: " << _grade_to_execute << std::endl;
}

AForm &AForm::operator=(const AForm &form)
{
	this->_signed = form._signed;
	return (*this);
}

AForm::~AForm()
{
	std::cout << "Form " << _name << " destroyed" << std::endl;
}

std::string AForm::get_name() const
{
	return (this->_name);
}

int AForm::get_grade_to_sign() const
{
	return (this->_grade_to_sign);
}

int AForm::get_grade_to_execute() const
{
	return (this->_grade_to_execute);
}

bool AForm::is_signed() const
{
	return (this->_signed);
}

void AForm::execute(Bureaucrat const & executor) const
{
	if (!this->is_signed())
		throw FormNotSignedException();
	if (executor.get_grade() > this->get_grade_to_execute())
		throw GradeTooLowException();
	this->exec();
}

const char* AForm::GradeTooHighException::what() const throw()
{
	return ("Form Grade is too high");
}

const char* AForm::GradeTooLowException::what() const throw()
{
	return ("Form Grade is too low");
}

const char* AForm::FormNotSignedException::what() const throw()
{
	return ("Form is not signed");
}

void AForm::be_signed(Bureaucrat &bureaucrat)
{
	if (bureaucrat.get_grade() <= this->_grade_to_sign)
		this->_signed = true;
	else
		throw AForm::GradeTooLowException();
}

std::ostream&	operator<<(std::ostream &o, const AForm& form)
{
	o	<< std::boolalpha << "Form " << form.get_name() << ", signed: "
		<< form.is_signed() << ", grade to sign " << form.get_grade_to_sign()
		<< ", grade to execute " << form.get_grade_to_execute() << std::endl;
	return o;
}
