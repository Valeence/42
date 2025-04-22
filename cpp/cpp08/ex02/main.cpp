/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 02:50:47 by vandre            #+#    #+#             */
/*   Updated: 2025/01/09 03:18:29 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MutantStack.hpp"

int main()
{
MutantStack<int> mstack;
mstack.push(5);
mstack.push(17);
std::cout << mstack.top() << std::endl;
mstack.pop();
std::cout << mstack.size() << std::endl;
mstack.push(3);
mstack.push(5);
mstack.push(737);
mstack.push(0);
//[...]

MutantStack<int>::iterator it = mstack.begin();
MutantStack<int>::iterator ite = mstack.end();
++it;
--it;
while (it != ite)
{
std::cout << *it++ << std::endl;
}

std::cout << "------" << std::endl;

std::list<int> s;
s.push_back(5);
s.push_back(17);
std::cout << s.back() << std::endl;
s.pop_back();
std::cout << s.size() << std::endl;
s.push_back(3);
s.push_back(5);
s.push_back(737);
s.push_back(0);

std::list<int>::iterator i = s.begin();
std::list<int>::iterator ie = s.end();
++it;
--it;
while (i != ie)
{
std::cout << *i++ << std::endl;
}
return 0;
}