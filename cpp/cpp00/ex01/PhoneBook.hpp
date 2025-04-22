/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 19:04:22 by vandre            #+#    #+#             */
/*   Updated: 2024/12/01 19:04:22 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"
#include <iostream>
#include <string.h>

#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

class PhoneBook
{
    public:
        PhoneBook();
        ~PhoneBook();
        void    add(std::string name_contact, std::string lastname, std::string nickname, std::string number, std::string darksecret);
        void    init_contact(std::string name_contact, std::string lastname, std::string nickname, std::string number, std::string darksecret, int i);
        void    search();
        void    find_contact();

    private:
    
		int		_index_contact;
        int     _intex_remplace;
        Contact	    _contact[8];
};

std::string format_string(const std::string& str);

#endif