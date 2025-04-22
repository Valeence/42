/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MutantStack.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 02:50:00 by vandre            #+#    #+#             */
/*   Updated: 2025/01/09 03:14:01 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTANTSTACK_HPP
#define MUTANTSTACK_HPP

#include <iostream>
#include <stack>
#include <deque>
#include <iterator>
#include <list>

template <typename T>
class MutantStack : public std::stack<T> {
	public:
		MutantStack() : std::stack<T>() {};
   		MutantStack(const MutantStack<T>& other) : std::stack<T>(other) {}
		~MutantStack() {};

    	MutantStack<T>& operator=(const MutantStack<T>& other) {
        	std::stack<T>::operator=(other);
        	return *this;
    	}

		typedef typename std::stack<T>::container_type::iterator iterator;
		typedef typename std::stack<T>::container_type::const_iterator const_iterator;
		typedef typename std::stack<T>::container_type::reverse_iterator reverse_iterator;
		typedef typename std::stack<T>::container_type::const_reverse_iterator const_reverse_iterator;

		iterator begin() {return this->c.begin();}
		iterator end() {return this->c.end();}

		reverse_iterator rbegin() {return this->c.rbegin();}
		reverse_iterator rend() {return this->c.rend();}

		const_iterator cbegin() const {return this->c.cbegin();}
		const_iterator cend() const {return this->c.cend();}

		const_reverse_iterator crbegin() const {return this->c.crbegin();}
		const_reverse_iterator crend() const {return this->c.crend();}
};
#endif