/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hgh                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 11:42:15 by vandre            #+#    #+#             */
/*   Updated: 2024/09/12 14:35:48 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BRAIN_HPP
#define BRAIN_HPP

#include "Animal.hpp"

class Brain
{
	public:
		Brain();
		~Brain();
		Brain(const Brain& other);
		Brain& operator=(const Brain& other);
		static const int _ideasCount;
		void setIdea(int index, std::string idea);
		std::string getIdea(int index) const;

	protected:
		std::string ideas[100];
};

#endif