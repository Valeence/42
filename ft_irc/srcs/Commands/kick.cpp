/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvalino- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 20:14:08 by dvalino-          #+#    #+#             */
/*   Updated: 2025/03/24 20:14:12 by dvalino-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Server.hpp"

void ft_kick(const std::string &input, Client &client, Server &server)
{
    std::stringstream ss(input);
    std::string cmd, channel, target, reason;
    
    ss >> cmd >> channel >> target;
    std::getline(ss, reason);
    
    if (channel.empty() || target.empty()) 
    {
        out_msg(client.getClientSocket(), ":" + server.getName() + ERR_NEEDMOREPARAMS("KICK"));
        return;
    }
    
    std::map<std::string, Channel *>& channels = server.getChannels();
    std::map<std::string, Channel *>::iterator chan_it = channels.find(channel);
    if (chan_it == channels.end()) {//":" + server.getName()
        out_msg(client.getClientSocket(), "403 " + client.getNickname() + ERR_NOSUCHCHANNEL(channel));
        return;
    }
    
    Channel& chan = *chan_it->second;
    
    if (!chan.isOperator(client.getNickname())) {//":" + server.getName()
        out_msg(client.getClientSocket(), "482 " + client.getNickname() + ERR_CHANOPRIVSNEEDED(channel));
        return;
    }
    
    if (!chan.isConnected(target)) {//":" + server.getName()
        out_msg(client.getClientSocket(), "441 " + client.getNickname() + ERR_USERNOTINCHANNEL(target, channel));
        return;
    }
    
    std::string kick_msg = ":" + client.getNickname() + " KICK " + channel + " " + target;
    if (!reason.empty()) {
        kick_msg += " :" + reason.substr(1);
    }
    
    // Diffusion du message
    const std::vector<Client *>& connected = chan.getConnectedClients();
    for (size_t i = 0; i < connected.size(); i++) {
        if (connected[i]) {
            out_msg(connected[i]->getClientSocket(), kick_msg);
        }
    }
    
    chan.disconnectClient(target);
}