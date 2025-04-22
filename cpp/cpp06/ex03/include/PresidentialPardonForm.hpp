/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 16:22:52 by vandre            #+#    #+#             */
/*   Updated: 2024/10/31 00:40:46 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AForm.hpp"

class PresidentialPardonForm : public AForm
{
	public :
		PresidentialPardonForm();
		PresidentialPardonForm(std::string target);
		PresidentialPardonForm(const PresidentialPardonForm &form);
		PresidentialPardonForm &operator=(const PresidentialPardonForm &form);
		virtual ~PresidentialPardonForm();
	protected :
		void	exec() const;
	private :
	std::string _target;
};