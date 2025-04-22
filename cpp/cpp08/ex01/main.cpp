/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 02:29:37 by vandre            #+#    #+#             */
/*   Updated: 2025/03/03 16:14:42 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"

void fill_span(size_t n) {
    Span sp(n);
    for (size_t i = 0; i < n; ++i) {
        sp.addNumber(i);
    }
    std::cout << "Span with " << n << " numbers: " << std::endl;
    std::cout << "Shortest Span: " << sp.shortestSpan() << std::endl;
    std::cout << "Longest Span: " << sp.longestSpan() << std::endl << std::endl;
}

int main() {
    try {
        Span sp = Span(5);
        sp.addNumber(6);
        sp.addNumber(3);
        sp.addNumber(17);
        sp.addNumber(9);
        sp.addNumber(11);

        std::cout << "Shortest Span: " << sp.shortestSpan() << std::endl;
        std::cout << "Longest Span: " << sp.longestSpan() << std::endl << std::endl;

        fill_span(10000);

    } catch (const std::exception& e) {
        std::cerr << "Error in main: " << e.what() << std::endl;
    }

    return 0;
}
