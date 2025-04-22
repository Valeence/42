/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:48:22 by vandre            #+#    #+#             */
/*   Updated: 2024/10/30 23:54:31 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUREAUCRAT_HPP
# define BUREAUCRAT_HPP

#include <iostream>
#include "AForm.hpp"

class AForm;

class Bureaucrat
{
	public:
		Bureaucrat();
		Bureaucrat(std::string name, int grade);
		Bureaucrat(const Bureaucrat &bureaucrat);
		Bureaucrat &operator=(const Bureaucrat &bureaucrat);
		~Bureaucrat();

		std::string get_name() const;
		int get_grade() const;
		void increment_grade();
		void decrement_grade();

		void signForm(AForm &form);
		void executeForm(AForm const & form);
		class GradeTooHighException : public std::exception
		{
			public:
				const char *what() const throw();
		};

		class GradeTooLowException : public std::exception
		{
			public:
				const char *what() const throw();
		};
		
	private:
		std::string const _name;
		int _grade;
};
std::ostream	&operator<<(std::ostream &str, Bureaucrat const &bureaucrat);
#endif