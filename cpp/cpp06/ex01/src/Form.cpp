/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 00:35:29 by vandre            #+#    #+#             */
/*   Updated: 2024/10/12 06:32:12 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Form.hpp"

Form::Form() : _name("default"), _signed(false), _grade_to_sign(150), _grade_to_execute(150)
{
    std::cout << "Form " << _name << " created, grade to sign: " << _grade_to_sign
        << ", grade to execute: " << _grade_to_execute << std::endl;
}

Form::Form(std::string name, int grade_to_sign, int grade_to_execute) 
	: _name(name), _signed(false), _grade_to_sign(grade_to_sign), _grade_to_execute(grade_to_execute)
{
	if (_grade_to_sign > 150 || _grade_to_execute > 150)
		throw Form::GradeTooLowException();
	else if (_grade_to_sign < 1 || _grade_to_execute < 1)
		throw Form::GradeTooHighException();
	std::cout << "Form " << _name << " created, grade to sign: " << _grade_to_sign
		<< ", grade to execute: " << _grade_to_execute << std::endl;
}

Form::Form(const Form &form) : _name(form._name), _signed(form._signed), _grade_to_sign(form._grade_to_sign), _grade_to_execute(form._grade_to_execute)
{
	std::cout << "Form " << _name << " created, grade to sign: " << _grade_to_sign
		<< ", grade to execute: " << _grade_to_execute << std::endl;
}

Form &Form::operator=(const Form &form)
{
	if (this == &form)
		return (*this);
	if (form._grade_to_sign > 150 || form._grade_to_execute > 150)
		throw Form::GradeTooLowException();
	else if (form._grade_to_sign < 1 || form._grade_to_execute < 1)
		throw Form::GradeTooHighException();
	_signed = form._signed;
	return (*this);
}

Form::~Form()
{
	std::cout << "Form " << _name << " destroyed" << std::endl;
}

std::string Form::get_name() const
{
	return (this->_name);
}

int Form::get_grade_to_sign() const
{
	return (this->_grade_to_sign);
}

int Form::get_grade_to_execute() const
{
	return (this->_grade_to_execute);
}

bool Form::is_signed() const
{
	return (this->_signed);
}

const char* Form::GradeTooHighException::what() const throw()
{
	return ("Form Grade is too high");
}

const char* Form::GradeTooLowException::what() const throw()
{
	return ("Form Grade is too low");
}

void Form::be_signed(Bureaucrat &bureaucrat)
{
    if (bureaucrat.get_grade() > _grade_to_sign)
    {
        throw Form::GradeTooLowException();
    }
    _signed = true;
}

std::ostream&	operator<<(std::ostream &o, const Form& form)
{
	o	<< std::boolalpha << "Form " << form.get_name() << ", signed: "
		<< form.is_signed() << ", grade to sign " << form.get_grade_to_sign()
		<< ", grade to execute " << form.get_grade_to_execute() << std::endl;
	return o;
}
