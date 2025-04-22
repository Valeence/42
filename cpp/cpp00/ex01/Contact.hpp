/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 19:04:10 by vandre            #+#    #+#             */
/*   Updated: 2024/12/01 19:04:10 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONCTACT_HPP
#define CONCTACT_HPP

#include <iostream>
#include <string.h>


class Contact
{
    private:
        std::string   _name_contact;
        std::string   _number;
        std::string   _lastname;
        std::string   _nickname;
        std::string   _darksecret;
    
    public:
        Contact();
        ~Contact();
        void        set_name(std::string &name_contact);
        void        set_lastname(std::string &lastname);
        void        set_nickname(std::string &nick_name_add);
        void        set_number(std::string &number_add);
        void        set_darksecret(std::string &darksecret_add);

        void        displayInfo() const;
        
        std::string     get_name() const;
        std::string     get_nickname()const;
        std::string     get_darksecret()const;
        std::string     get_lastname() const;

};

#endif