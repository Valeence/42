/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whois.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvalino- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:59:35 by dvalino-          #+#    #+#             */
/*   Updated: 2025/03/24 18:59:36 by dvalino-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Server.hpp"

void    ft_whois(const std::string &input, Client& client, Server &server)
{
    std::stringstream line(input);
    std::string str, msg;

    while (getline(line, str, ' '))
    {
        if (str == "WHOIS")
            continue ;
    }
    if (str.empty() || str == client.getNickname())
    {
        msg = client.getNickname() 
            + RPL_WHOISUSER(client.getNickname(), client.getUsername(), client.getHost(), client.getRealname())
            + "\r\n";
        msg += client.getNickname() + RPL_ENDOFWHOIS(client.getNickname()) + "\r\n";
        send(client.getClientSocket(), msg.c_str(), msg.size(), 0);
        return ;
    }
    if (str[0] == '#')
    {
        std::map<std::string, Channel *> &channels = server.getChannels();
        if (channels.find(str) != channels.end())
        {
            std::string msg("353 " + client.getNickname() + " " + channels[str]->whoIsConnected() + "\r\n");
            
            msg += client.getNickname() + RPL_ENDOFNAMES(str) + "\r\n";
            send(client.getClientSocket(), msg.c_str(), msg.size(), 0);
            return ;
        }
    }
    std::vector<Client *> &clients = server.getClients();
    for (std::vector<Client *>::iterator it = clients.begin()
        ; it != clients.end(); it++)
    {
        if ((*it)->getNickname() == str)
        {
            msg = client.getNickname() 
            + RPL_WHOISUSER((*it)->getNickname(),
                (*it)->getUsername(), (*it)->getHost(), (*it)->getRealname())
            + "\r\n";
            msg += client.getNickname() + RPL_ENDOFWHOIS((*it)->getNickname()) + "\r\n";
            send(client.getClientSocket(), msg.c_str(), msg.size(), 0);
            return ;
        }
    }
    msg = client.getNickname() + ERR_NOSUCHNICK(str) + "\r\n";
    send(client.getClientSocket(), msg.c_str(), msg.size(), 0);
    msg = client.getNickname() + RPL_ENDOFWHOIS(str) + "\r\n";
    send(client.getClientSocket(), msg.c_str(), msg.size(), 0);
}
