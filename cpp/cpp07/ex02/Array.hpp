/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 17:36:35 by vandre            #+#    #+#             */
/*   Updated: 2025/02/28 17:46:51 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <iostream>

template<typename T> class Array {
	public:
		Array() : _Array(NULL), _size(0) {}
		
		Array(unsigned int n) : _Array(new T[n]()), _size(n) {}
		
		Array(const Array& other) : _Array(NULL), _size(0) {*this = other;}
		
		~Array() {delete[] _Array;}

		Array& operator=(const Array& other) {
        if (this != &other) {
            delete[] _Array;
            _size = other._size;
            _Array = new T[_size];
            for (unsigned int i = 0; i < _size; ++i) {
                _Array[i] = other._Array[i];
            }
        }
        return *this;
		}

		T& operator[](unsigned int index) {
        if (index >= _size) {
            throw std::out_of_range("Index out of bounds");
        }
        return _Array[index];
    }
		const T& operator[](unsigned int index) const {
        if (index >= _size) {
            throw std::out_of_range("Index out of bounds");
        }
        return _Array[index];
    	}

		unsigned int size() {
			return _size;
		}
	private:

		T* _Array;
		unsigned int _size;
};

#endif