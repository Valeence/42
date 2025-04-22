/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 16:23:00 by vandre            #+#    #+#             */
/*   Updated: 2024/10/31 00:41:03 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AForm.hpp"

class ShrubberyCreationForm : public AForm
{
	public :
		ShrubberyCreationForm();
		ShrubberyCreationForm(std::string target);
		ShrubberyCreationForm(const ShrubberyCreationForm &form);
		ShrubberyCreationForm &operator=(const ShrubberyCreationForm &form);
		virtual ~ShrubberyCreationForm();
	protected :
		void	exec() const;
	private :
	std::string _target;
};
