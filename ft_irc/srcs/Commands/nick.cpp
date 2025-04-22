/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:58:42 by dvalino-          #+#    #+#             */
/*   Updated: 2025/04/13 16:38:19 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Server.hpp"
#include <cstdio>

bool isValidNickName(const std::string &nickname) 
{
    if (nickname.empty()) return false;
    char first = nickname[0];
    if (!(isalpha(first) || first == '[' || first == ']' || first == '\\' || 
          first == '`' || first == '_' || first == '^' || first == '{' || 
          first == '|' || first == '}')) {
        return printf("caca 1\n"), false;
    }
    for (size_t i = 0; i < nickname.length() - 1; ++i) {
        if (!(isalnum(nickname[i]) || nickname[i] == '-' || nickname[i] == '_')) {
            return printf("caca 2\n"), false;
        }
    }
    return true;
}

void    ft_nick(const std::string &buffer, int clientFd, Client &client, Server &server)
{
    if (client.isFullRegist())
    {
        send(clientFd, "ERROR :Already registered\r\n", 28, 0);
        server.removeClient(clientFd);
        return;
    }
    else {
        std::string nickname = buffer.substr(5);
        if (nickname.empty() || nickname.length() > 9)
        {
            // send(clientFd, "ERROR :Invalid nickname\r\n", 26, 0);
            out_msg(clientFd, "431 " + nickname + ERR_NONICKNAMEGIVEN);
            server.removeClient(clientFd);
            return;
        }
        if (!isValidNickName(nickname)) 
        {
            out_msg(clientFd, "432 " + nickname + ERR_ERRONEUSNICKNAME(nickname));
            // send(clientFd, "ERROR :Invalid nickname\r\n", 26, 0);
            server.removeClient(clientFd);
            return;
        }
        if(!server.nickalreadyregist(nickname))
        {
            // send(clientFd, "ERROR :Nickname already taken\r\n", 31, 0);
            out_msg(clientFd, ":ft_irc 433 " + nickname + ERR_NICKNAMEINUSE(nickname));
            server.removeClient(clientFd);
            // client.clearBuffer();
            return;
        }
        client.setNickname(nickname);
        server.nicklist.push_back(nickname);
        #ifdef DEBUG
            for (std::vector<std::string>::iterator it = server.nicklist.begin(); it != server.nicklist.end(); ++it) {
                std::cout << "nicklist = " << *it << std::endl;
            }
        #endif
        client.setNick(true);
        client.checkRegist(clientFd);
    }
}

// void ft_nick(char *buffer, int clientFD)
// {
//     const char *msg = buffer;
//     const char *nick_start = strchr(msg + 5, ' ');
    
//     if(nick_start == NULL)
//     {
//         out_msg(clientFD, "431 : No nickname given");
//         return;
//     }
//     nick_start++;
//     const char *nick_end = strchr(nick_start, '\0');
    
//     if (nick_end == NULL)
//     {
//         nick_end = strchr(nick_start, '\r');
//         if(nick_end == NULL)
//             nick_end = strchr(nick_start, '\n');
//     }

//     if(nick_end == NULL)
//         nick_end = strchr(nick_start, '\0');
    
//     std::string nickname(nick_start, nick_end);
//     if(!isValidNickName(nickname))
//     {
//         out_msg(clientFD, "432 : Invalid nickname");    
//         return;
//     }
    
//     out_msg(clientFD, "001 : Welcome to the server " + nickname);
// }
