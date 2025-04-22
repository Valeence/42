/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 02:28:55 by vandre            #+#    #+#             */
/*   Updated: 2025/03/03 16:15:09 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPAN_HPP
#define SPAN_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

class Span {
	public:
		Span(unsigned int n) : _n(n) {};
		Span(const Span &cpy) {
			*this = cpy;};
		Span &operator=(const Span &cpy) {
			if (this != &cpy) {
				this->_n = cpy._n;
				this->_list = cpy._list;
			}
			return *this;};
		~Span() {};

		void addNumber(unsigned int n) {
			if (_list.size() >= _n)
				throw std::overflow_error("Span is full");
			_list.push_back(n);};

		int shortestSpan() {
			if (_list.size() < 2)
				throw std::logic_error("Not enought number to to find a shortest Span");
        std::vector<int> sortedNumbers = _list;
        std::sort(sortedNumbers.begin(), sortedNumbers.end());
        int shortest = INT_MAX;
        for (size_t i = 1; i < sortedNumbers.size(); ++i) {
            int diff = sortedNumbers[i] - sortedNumbers[i - 1];
            if (diff < shortest) {
                shortest = diff;
            }
        }
        return shortest;
		};

		int longestSpan() {
			if (_list.size() < 2)
				throw std::logic_error("Not enought number to to find the longest Span");
			int min = *std::min_element(_list.begin(), _list.end());
			int max = *std::max_element(_list.begin(), _list.end());
			return max - min;
			};

	private:
		unsigned int _n;
		std::vector<int> _list;
};

#endif