/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 00:10:01 by vandre            #+#    #+#             */
/*   Updated: 2024/12/09 16:22:53 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Harl.hpp"

Harl::Harl()
{
}

Harl::~Harl()
{
}

void Harl::debug()
{
    std::cout << "I love having extra bacon for my 7XL-double-cheese-triple-pickle-special- ketchup burger. I really do !" << std::endl;
}
void Harl::info()
{
    std::cout << "I cannot believe adding extra bacon costs more money. You didn’t put enough bacon in my burger ! If you did, I wouldn’t be asking for more !" << std::endl;
}
void Harl::warning()
{
	std::cout << "I think I deserve to have some extra bacon for free. I’ve been coming for years whereas you started working here since last month." << std::endl;
}
void Harl::error()
{
    std::cout  << "This is unacceptable ! I want to speak to the manager now." << std::endl;
}


void Harl::complain(std::string level)
{
	std::map<std::string, void(Harl::*)(void)> HarlMap; 
	
	HarlMap.insert(std::make_pair("DEBUG", &Harl::debug));
	HarlMap.insert(std::make_pair("INFO", &Harl::info));
	HarlMap.insert(std::make_pair("WARNING", &Harl::warning));
	HarlMap.insert(std::make_pair("ERROR", &Harl::error));
	
	if(HarlMap.find(level) != HarlMap.end()) {
		(this->*HarlMap[level])();
	} else {
		std::cout << "Invalid level: " << level << std::endl;
	}
}

