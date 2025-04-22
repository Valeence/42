/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.C                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 03:01:32 by vandre            #+#    #+#             */
/*   Updated: 2024/12/06 03:35:09 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <fstream>
#include <iostream>
#include <iostream>
#include <string>

bool replace(const std::string& filename)
{
    std::ifstream fichier_in(filename.c_str());
    if (!fichier_in)
        return std::cerr << "Impossible d'ouvrir le fichier : " << filename << std::endl, false;

    std::ofstream fichier_replace((filename + ".replace").c_str());
    if (!fichier_replace)
        return std::cerr << "Impossible d'ouvrir le fichier de sortie : " << filename + ".replace" << std::endl, false;

    std::string ligne1, ligne2;
    if (std::getline(fichier_in, ligne1) && std::getline(fichier_in, ligne2))
        fichier_replace << ligne2 << std::endl << ligne1;
    else
        return std::cerr << "Erreur lors de la lecture des lignes" << std::endl, false;

    return true;
}

int main(int argc, char **argv)
{
    if (argc != 4)
        return std::cerr << "Error: wrong number of arguments" << std::endl, 1;

    std::ofstream fichier(argv[1]);
    if (!fichier)
        return std::cerr << "Impossible d'ouvrir le fichier : " << argv[1] << std::endl, 1;

    fichier << argv[2] << std::endl << argv[3];
    fichier.close();
	if (!replace(argv[1]))
		return 1;
    return 0;
}