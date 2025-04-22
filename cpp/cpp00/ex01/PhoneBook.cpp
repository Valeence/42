/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:46:28 by vandre            #+#    #+#             */
/*   Updated: 2024/11/28 15:46:28 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"
#include <iostream>
#include <string>
#include <iomanip>  

PhoneBook::PhoneBook() : _index_contact(0), _intex_remplace(0) {}

PhoneBook::~PhoneBook(){};

bool not_digit(int nb)
{
    if(nb < '0' || nb > '9')
        return true;
    return false;

}

void PhoneBook::find_contact()
{
    int index;

    if(_index_contact == 0)
    {
        std::cerr << "Repertoir vide." << std::endl;
        return;
    }
    while (true)
    {
        index = 0;
        std::cout << "Veuillez entrer l'index du contact: " << std::endl;

        if (!(std::cin >> index))
        {
            std::cerr << "Entrée invalide. Veuillez saisir un numéro." << std::endl;
            std::cin.clear();
            while (std::cin.get() != '\n');
            continue;
            
        }
        if (index >= 0 && index <= _index_contact -1)
        {
            _contact[index].displayInfo();
            break;
        }
        else
            std::cout << "index non valide. Veuillez saisir un nombre compris entre 0 et " << (_index_contact - 1)  << "." << std::endl;
    }
    return;
}


void    PhoneBook::search()
{
    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "|  index   |firstname | lastname |nickname |" << std::endl;
    std::cout << "---------------------------------------------" << std::endl;

    int i = 0;
    while (i < _index_contact) 
    {
        std::string formatted_name = format_string(_contact[i].get_name());
        std::string formatted_lastname = format_string(_contact[i].get_lastname());
        std::string formatted_nickname = format_string(_contact[i].get_nickname());

        std::cout << std::setw(10) << i << "|";
        std::cout << std::setw(10) << formatted_name << "|";
        std::cout << std::setw(10) << formatted_lastname << "|";
        std::cout << std::setw(10) << formatted_nickname << "|";
        std::cout << std::endl;
        i++;
    }
    std::cout << "---------------------------------------------" << std::endl;
    find_contact();
}


void PhoneBook::init_contact(std::string name_contact, std::string lastname, std::string nickname, std::string number, std::string darksecret, int i)
{
    _contact[i].set_name(name_contact);
    _contact[i].set_lastname(lastname);
    _contact[i].set_number(number);
    _contact[i].set_nickname(nickname);
    _contact[i].set_darksecret(darksecret);


}

void PhoneBook::add(std::string name_contact, std::string lastname, std::string nickname, std::string number, std::string darksecret)
{
    if(_index_contact >= 8)
    {
        if(_intex_remplace == 7)
            _intex_remplace = 0;
        init_contact(name_contact, lastname, nickname,number,  darksecret, _intex_remplace);
        _intex_remplace++;
        std::cout << " !!! Contact remplacer !!!" << std::endl;
        return;
    }
    else
    {
        init_contact(name_contact, lastname, nickname,number,  darksecret, _index_contact);
        std::cout << "!!! Contact ajouté !!!" << std::endl;
        ++_index_contact;
    }
}