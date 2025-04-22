/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 18:02:16 by vandre            #+#    #+#             */
/*   Updated: 2025/03/03 15:06:31 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "easyfind.hpp"

int main(void)
{
	std::list<int> container(1, 1);
	std::list<int>::iterator it;
	std::list<int>::iterator itest;

	for (it = container.begin(); it != container.end(); it++) {
		std::cout << *it << std::endl;
	}

	std::cout << "---" << std::endl;
	container.push_back(2);
	container.push_back(3);
	container.push_back(4);

	for (it = container.begin(); it != container.end(); it++) {
		std::cout << *it << std::endl;
	}
	std::cout << "---" << std::endl;

	itest = easyfind(container, 5);
	if (itest == container.end()) {
    	std::cerr << "Value not found" << std::endl;
	}
	else {
    std::cout << "Value found!" << std::endl;
	}
	std::cout << "---" << std::endl;
	
	container.push_back(5);
	
	for (it = container.begin(); it != container.end(); it++) {
		std::cout << *it << std::endl;
	}
	std::cout << "---" << std::endl;
	
	itest = easyfind(container, 5);
	
	if (itest == container.end()) {
    	std::cerr << "Value not found" << std::endl;
    	return 0;
	} 
	else {
    	std::cout << "Value found!" << std::endl;
	}
	return 0;
}