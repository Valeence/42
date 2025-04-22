/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 14:38:08 by vandre            #+#    #+#             */
/*   Updated: 2024/12/23 02:18:05 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AForm.hpp"

class Intern
{
	public: 
		Intern();
		Intern(const Intern &cpy);
		Intern &operator= (const Intern &cpy);
		~Intern();

		AForm* makeForm(std::string name, std::string target);
		
		static AForm* createShrubbery(std::string target); //static car appelée sans instance
		static AForm* createRobotomy(std::string target);
		static AForm* createPresidential(std::string target);
	private:
		
};