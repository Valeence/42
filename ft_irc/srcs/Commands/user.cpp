/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:58:54 by dvalino-          #+#    #+#             */
/*   Updated: 2025/04/04 19:25:35 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Server.hpp"

bool fill_user(std::string &username, Client &client) 
{
    // bool space = false;
    if (username.empty())
        return false;
    for (size_t i = 0; i < username.size(); i++)
    {
        if (username[i] == ' ')
        {
            // if (space == true) {
                std::string a = username.substr(0, i);
                client.setUsername(a);
                client.setUser(true);
                return true;
            // }
            // else
                // space = true;
        }
    }
    return false;
}

bool fill_real(std::string &username, Client &client) 
{
    std::string real = username.substr(username.find(':') + 1, username.size());
    client.setRealname(real);
    return true;
}

void    ft_user(const std::string &input, int clientFd, Client& client, Server& server)
{
    if (client.isFullRegist())
    {
        send(clientFd, "ERROR :Already registered\r\n", 28, 0);
        server.removeClient(clientFd);
        return;
    }
    else {
        std::string username = input.substr(5);
        if (username.empty()) 
        {
            send(clientFd, "ERROR :Invalid username\r\n", 26, 0);
            server.removeClient(clientFd);
            return;
        }
        if (fill_user(username, client) == false)
        {
            send(clientFd, "ERROR :Invalid username\r\n", 26, 0);
            server.removeClient(clientFd);
            return;
        }
        if (fill_real(username, client) == false)
        {
            send(clientFd, "ERROR :Invalid realname\r\n", 26, 0);
            server.removeClient(clientFd);
            return;
        }
        client.checkRegist(clientFd);
    }
}

// std::stringstream line(input);
// std::string str, realname;
// int count = -1;

// if (!client.getRealname().empty() || !client.getUsername().empty())
// {
//     std::string msg(client.getNickname() + ERR_ALREADYREGISTERED + "\r\n");
//     send(ClientFd, msg.c_str(), msg.size(), 0);
//     return ;
// }
// while (getline(line, str, ' '))
// {
//     count++;
//     if (count == 0 && str == "USER")
//         continue;
//     if (count == 1 && !str.empty())
//         client.setUsername(str);
//     else if (count == 1 && str.empty())
//     {
//         std::string msg(client.getNickname() + ERR_NEEDMOREPARAMS("USER") + "\r\n");
//         send(ClientFd, msg.c_str(), msg.size(), 0);
//         return ;
//     }
//     if (count == 4)
//     {
//         if (str[0] == ':')
//             str.erase(0, 1);
//         realname = str;
//     }
//     else if (count > 4)
//         realname += ' ' + str;
// }
// client.setRealname(realname);
