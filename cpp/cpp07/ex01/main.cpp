/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 02:50:26 by vandre            #+#    #+#             */
/*   Updated: 2025/01/03 23:21:17 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iter.hpp"
#include <iostream>

int main()
{
    char s1[] = "Hello";
    int s2[5] = {1, 2, 3, 4, 5};

    for (int i = 0; i < 5; ++i) {
        std::cout << s2[i] << " ";
    }
    std::cout << std::endl;

    iter(s2, 5, changeArray<int>);

    for (int i = 0; i < 5; ++i) {
        std::cout << s2[i] << " ";
    }
    std::cout << std::endl;

        for (int i = 0; i < 5; ++i) {
        std::cout << s1[i];
    }
    std::cout << std::endl;

    iter(s1, 5, changeArray<char>);

    for (int i = 0; i < 5; ++i) {
        std::cout << s1[i];
    }
    return 0;
}