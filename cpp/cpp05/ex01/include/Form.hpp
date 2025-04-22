/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 00:35:46 by vandre            #+#    #+#             */
/*   Updated: 2024/10/12 06:26:01 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORM_HPP
# define FORM_HPP

#include <iostream>
#include "Bureaucrat.hpp"

class Bureaucrat;

class Form
{
	public :
		Form();
		Form(std::string name, int grade_to_sign, int grade_to_execute);
		Form(const Form &form);
		Form &operator=(const Form &form);
		~Form();
		
		std::string get_name() const;
		int get_grade_to_sign() const;
		int get_grade_to_execute() const;
		bool is_signed() const;
		
		void	be_signed(Bureaucrat &bureaucrat);
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
	private :
		std::string const _name;
		bool _signed;
		int const _grade_to_sign;
		int const _grade_to_execute;
};
std::ostream	&operator<<(std::ostream &str, Form const &form);
#endif
