/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvalino- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:59:59 by dvalino-          #+#    #+#             */
/*   Updated: 2025/03/24 19:00:01 by dvalino-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Server.hpp"

void	ft_msg(const char *buffer, Client *sender, Server &server)
{
	std::stringstream line(buffer);
	std::string str, target, msg;
	int count = 0;

	while (getline(line, str, ' '))
	{
        count++;
        if (str == "PRIVMSG")
            continue ;
		if (count == 2 && !str.empty())
            target = str;
        else
        {
            if (count != 2 && !msg.empty())
                msg += ' ';
            msg += str;
        }
	}
    if (msg.empty())
    {
        msg = sender->getNickname() + ERR_NOTEXTTOSEND + "\r\n";
        send(sender->getClientSocket(), msg.c_str(), msg.size(), 0);
        return ;
    }
    if (msg.find("\n") != std::string::npos)
    {
        msg.erase(msg.find("\n"), 1);
    }
    msg = ":" + sender->getNickname() + "!" + sender->getUsername()
        + "@127.0.0.1" + " PRIVMSG " + target + " " + msg + "\r\n";
    if (target[0] == '#' && target.size() > 1)
    {
        std::map<std::string, Channel *> & channels = server.getChannels();
        // target.erase(0, 1);
        #ifdef DEBUG
            std::cout << "channel : [" << target << "]\n";
            std::cout << "channels in server : [" << channels << "]\n";
        #endif
        if (channels.find(target) != channels.end())
        {
            //std::cout << "found channel" << std::endl;
            // msg.insert(0, sender->getNickname() + " PRIVMSG " + target + " :");
            if (!channels[target]->getNoExternal() || channels[target]->isConnected(sender->getNickname()))
                channels[target]->sendMsgToConnected(buffer, sender);
            else
                out_msg(sender->getClientSocket(), ":404 " + sender->getNickname() + ERR_CANNOTSENDTOCHAN(target));
            return ;
        }
        msg = ":404 " + sender->getNickname() + ERR_CANNOTSENDTOCHAN(target) + "\r\n";
        send(sender->getClientSocket(), msg.c_str(), msg.size(), 0);
    }
    else if (target[0] != '#')
    {
        // if (msg.find(":DCC ") != 0)
        // {
        //     msg += "\r\n";
        // }

        //std::cout << "msg : [" << msg << "]\n";
        std::vector<Client *> & clients = server.getClients();
        //std::cout << "target : [" << target << "]\n"
                // << "_clients : [" << clients << ']' << std::endl;
        for (std::vector<Client *>::iterator it = clients.begin(); it != clients.end(); it++)
        {
            if ((*it)->getNickname() == target)
            {
                //std::cout << "socket : " << (*it)->getNickname() << '\n';
                send((*it)->getClientSocket(), msg.c_str(), msg.length(), 0);
                return ;
            }
        }
    }
    msg = sender->getNickname() + ERR_NOSUCHNICK(target) + "\r\n";
    send(sender->getClientSocket(), msg.c_str(), msg.size(), 0);
    #ifdef DEBUG
        std::cout << "Send error message: channel/nickname not found" << std::endl;
    #endif
}

