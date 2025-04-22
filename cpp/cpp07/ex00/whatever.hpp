/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whatever.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 02:28:03 by vandre            #+#    #+#             */
/*   Updated: 2025/02/28 17:31:14 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WHATEVER_HPP
# define WHATEVER_HPP

#include "iostream"

template <typename T>
void swap(T& a, T& b)
{
	T tmp;
	tmp = a;
	a = b;
	b = tmp;
}

template <typename C>
C min(const C& a, const C& b)
{
	return ( (a<=b) ? a : b);
}

template <typename A>
A max(const A& a, const A& b)
{
	return ( (a>=b) ? a : b);
}

#endif