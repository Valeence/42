/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:46:16 by vandre            #+#    #+#             */
/*   Updated: 2024/11/28 15:46:16 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

std::string format_string(const std::string& str) 
{
    if (str.length() > 10)
        return str.substr(0, 9) + ".";
    else
        return str;
}

int ft_getline(std::string &str)
{   
    while(true)
    {
        if((std::getline(std::cin, str, '\n').eof()) == true)
        {
            std::cerr << "\nFatal Error" << std::endl;
            return 1;
        }
        if (str.find('[') != std::string::npos) 
        {
            std::cerr << "I don't understand retype your enter ?" << std::endl;
            continue;
        }
        break;
    }
    return 0;
}

int take_number(std::string &number)
{
    bool isBool = false;

    while (isBool == false)
    {
        std::cout << "Entrez le numéro du contact : ";
        if(ft_getline(number) == 1)
                return 1;
        if(number.empty())
            continue;
        isBool = true;
        unsigned long i = 0;
        while (i < number.size()) 
        {
            if (isdigit(number[i]) == 0) 
            {                           
                std::cerr << "Entree invalide, veuillez entrer uniquement des chiffres." << std::endl;
                isBool = false;
                break; 
            }
            if (i + 1 == number.size()) 
                isBool = true;
            i++;
        }
    }
    return 0;
}

int main(void)
{    
    PhoneBook phonebook;
    std::cout << "Enter a command:\nADD:\nSEARCH:\nEXIT:\n" << std::endl;

    while(true)
    {
        
        std::string str = "";
        if(ft_getline(str) == 1)
            break;
        if(str == "EXIT")
        {
            std::cout << "!!! Ciao !!!" << std::endl;
            break;
        }
        if(str == "ADD")
        {
            std::string prenom;
            std::string nom;
            std::string nickname;
            std::string number;
            std::string darksecret;
            
            std::cout << "Entrez le prenom: ";
            if(ft_getline(prenom) == 1)
                break;
            std::cout << "Entrez le nom : ";
            if(ft_getline(nom) == 1)
                break;            
            std::cout << "Entrez le surnom: ";
            if(ft_getline(nickname) == 1)
                break;
            if(take_number(number) == 1)
                break;
            std::cout << "Entrez un secret sur le contact: ";
            if(ft_getline(darksecret) == 1)
                break;
            phonebook.add(prenom, nom, nickname, number, darksecret);
        }
        if(str == "SEARCH")
            phonebook.search();
        if(str != "SEARCH" || str != "ADD" || str != "EXIT")
            std::cout << "Enter a command:\nADD:\nSEARCH:\nEXIT:\n" << std::endl;
    }
    return 0;
}