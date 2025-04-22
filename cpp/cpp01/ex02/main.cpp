/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 10:56:37 by vandre            #+#    #+#             */
/*   Updated: 2024/12/04 03:11:27 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

int main()
{
	std::string str = "HI THIS IS BRAIN";
	std::string *stringPTR = &str;
	std::string &stringREF = str;

	std::cout << "str = " << &str << std::endl;
	std::cout << "stringPTR = " << &stringPTR << std::endl;
	std::cout << "stringREF = " << &stringREF << std::endl;
	std::cout << std::endl;
	std::cout << "str = " << str << std::endl;
	std::cout << "stringPTR = " << *stringPTR << std::endl;
	std::cout << "stringREF = " << stringREF << std::endl;
	return 0;
}