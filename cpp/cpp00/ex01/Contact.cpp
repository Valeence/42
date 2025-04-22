/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:53:17 by vandre            #+#    #+#             */
/*   Updated: 2024/11/28 15:53:17 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"

Contact::Contact() : _name_contact(""), _number(""), _lastname(""), _darksecret("") {}

std::string     Contact::get_name()const
{
    return _name_contact;
}

std::string     Contact::get_lastname()const
{
    return _lastname;
}


std::string     Contact::get_nickname()const
{
    return _nickname;
}

std::string     Contact::get_darksecret()const
{
    return _darksecret;
}

void    Contact::set_name(std::string &name_contact)
{
    this->_name_contact = name_contact;
}


void    Contact::set_lastname(std::string &lastname)
{
    this->_lastname = lastname;
}

void    Contact::set_number(std::string &nunber_add)
{
    this->_number = nunber_add;
}

void    Contact::set_nickname(std::string &nick_name_add)
{
    this->_nickname = nick_name_add;
}

void    Contact::set_darksecret(std::string &darksecret_add)
{
    this->_darksecret = darksecret_add;    
}


void    Contact::displayInfo() const 
{
    std::cout << "Prenom    : "  << _name_contact << std::endl;
    std::cout << "Nom       : "  << _lastname << std::endl;
    std::cout << "Nickname  : "  << _nickname << std::endl;
    std::cout << "Numéro    : " << _number << std::endl;;
    std::cout << "secret    : " << _darksecret << std::endl;
}

Contact::~Contact() {};