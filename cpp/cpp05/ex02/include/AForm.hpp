/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 00:35:46 by vandre            #+#    #+#             */
/*   Updated: 2024/10/31 00:18:32 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AFORM_HPP
# define AFORM_HPP

#include <iostream>
#include "Bureaucrat.hpp"
#include <fstream>

class Bureaucrat;

class AForm
{
	public :
		AForm();
		AForm(std::string name, int grade_to_sign, int grade_to_execute);
		AForm(const AForm &form);
		AForm &operator=(const AForm &form);
		~AForm();
		
		std::string get_name() const;
		int get_grade_to_sign() const;
		int get_grade_to_execute() const;
		bool is_signed() const;

		void be_signed(Bureaucrat &bureaucrat);
		void execute(Bureaucrat const & executor) const;
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
		class FormNotSignedException : public std::exception
		{
			public:
				const char *what() const throw();
		};
	protected :
		virtual void exec() const = 0;
	private :
		std::string const _name;
		bool _signed;
		int const _grade_to_sign;
		int const _grade_to_execute;
};
std::ostream	&operator<<(std::ostream &str, AForm const &form);
#endif
