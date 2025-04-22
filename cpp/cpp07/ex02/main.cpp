#include <iostream>
#include <stdlib.h>
#include "Array.hpp"

#define MAX_VAL 5
int main(int, char**)
{
    Array<int> numbers(MAX_VAL);
    int* mirror = new int[MAX_VAL];
    srand(time(NULL));
    std::cout << numbers.size() << std::endl;
    for (int i = 0; i < MAX_VAL; i++)
    {
        const int value = rand();
        numbers[i] = value;
        mirror[i] = value;
    }
    //SCOPE
    {
        Array<int> tmp = numbers;
        Array<int> test(tmp);
    }

    for (int i = 0; i < MAX_VAL; i++)
    {
        if (mirror[i] != numbers[i])
        {
            std::cerr << "didn't save the same value!!" << std::endl;
            return 1;
        }
    }
    for (int i = 0 ;  i < MAX_VAL; i++)
    {
        std::cout << mirror[i] << std::endl;
    }
    try
    {
        numbers[-2] = 0;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    try
    {
        numbers[MAX_VAL] = 0;
        //std::cout << numbers[0] << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    for (int i = 0; i < MAX_VAL; i++)
    {
        numbers[i] = rand();
    }

    delete [] mirror;//
    return 0;
}

// int main(int, char**) {
//     Array<char> characters(MAX_VAL);
//     char* mirror = new char[MAX_VAL];
//     srand(time(NULL));

//     for (int i = 0; i < MAX_VAL; i++) {
//         const char value = 'A' + (rand() % 26);
//         characters[i] = value;
//         mirror[i] = value;
//     }
//     // SCOPE
//     {
//         Array<char> tmp = characters;
//         Array<char> test(tmp);
//     }
//     for (int i = 0; i < MAX_VAL; i++) {
//         if (mirror[i] != characters[i]) {
//             std::cerr << "didn't save the same value!!" << std::endl;
//             return 1;
//         }
//     }
//     for (int i = 0; i < MAX_VAL; i++) {
//         std::cout << mirror[i] << std::endl;
//     }
//     try {
//         characters[-2] = 'Z';
//     }
//     catch(const std::exception& e) {
//         std::cerr << e.what() << '\n';
//     }
//     try {
//         characters[MAX_VAL] = 'Z';
//     }
//     catch(const std::exception& e) {
//         std::cerr << e.what() << '\n';
//     }
//     for (int i = 0; i < MAX_VAL; i++) {
//         characters[i] = 'a' + (rand() % 26);
//     }
//     delete[] mirror;
//     return 0;
// }