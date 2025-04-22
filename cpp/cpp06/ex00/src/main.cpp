/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:47:43 by vandre            #+#    #+#             */
/*   Updated: 2024/10/09 00:26:21 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Bureaucrat.hpp"

int main()
{
	try {
		Bureaucrat b1("Bureaucrat1", 1);
		Bureaucrat b2("Bureaucrat2", 150);
		//Bureaucrat b3("Bureaucrat3", 0);
		Bureaucrat b4("Bureaucrat4", 119);

		try {
			b1.increment_grade();
		} catch (const Bureaucrat::GradeTooHighException& e) {
			std::cerr << "Exception caught: " << e.what() << std::endl;
		}
		try {
			b2.decrement_grade();
		} catch (const Bureaucrat::GradeTooLowException& e) {
			std::cerr << "Exception caught: " << e.what() << std::endl;
		}
		try {
			b4.increment_grade();
			b4.increment_grade();
			std::cout << b4;
		} catch (const Bureaucrat::GradeTooHighException& e) {
			std::cerr << "Exception caught: " << e.what() << std::endl;
		}
	} catch (const std::exception& e) {
		std::cerr << "Critical exception: " << e.what() << std::endl;
	}
	return 0;
}