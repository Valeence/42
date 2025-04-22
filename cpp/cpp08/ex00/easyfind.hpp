/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easyfind.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 18:02:32 by vandre            #+#    #+#             */
/*   Updated: 2025/01/07 00:32:09 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EASYFIND_HPP
#define EASYFIND_HPP

#include <iostream>
#include <list>
#include <algorithm>

template<typename T>
typename T::iterator easyfind(T& src, int i)
{
	return std::find(src.begin(), src.end(), i);
}
#endif