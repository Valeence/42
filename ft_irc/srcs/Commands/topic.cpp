/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvalino- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 20:16:45 by dvalino-          #+#    #+#             */
/*   Updated: 2025/03/24 20:16:46 by dvalino-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Server.hpp"

void    ft_topic(const std::string &input, Client &client, Server &server)
{
    std::stringstream ss(input);
    std::string cmd, channel, new_topic;
    
    ss >> cmd >> channel;
    std::getline(ss, new_topic);
    
    // Vérification des paramètres
    if (channel.empty()) 
    {
        out_msg(client.getClientSocket(), ":" + server.getName() + ERR_NEEDMOREPARAMS("TOPIC"));
        return;
    }
    
    // Vérification de l'existence du channel
    std::map<std::string, Channel *>& channels = server.getChannels();
    std::map<std::string, Channel *>::iterator chan_it = channels.find(channel);
    if (chan_it == channels.end()) 
    {
        out_msg(client.getClientSocket(), ":" + server.getName() + ERR_NOSUCHCHANNEL(channel));
        return;
    }
    
    Channel& chan = *(chan_it)->second;
    
    // Mode affichage du topic
    if (new_topic.empty()) 
    {
        if (chan.getTopic().empty()) 
            out_msg(client.getClientSocket(), ":" + server.getName() + RPL_NOTOPIC(client.getNickname(), channel));
        else 
            out_msg(client.getClientSocket(), ":" + server.getName() + RPL_TOPIC(client.getNickname(), channel, chan.getTopic()));
        return;
    }
    // Vérification de la présence dans le channel
    if (!chan.isConnected(client.getNickname())) {
        out_msg(client.getClientSocket(), ":" + server.getName() + ERR_NOTONCHANNEL(channel));
        return;
    }
    
    // Vérification des droits si mode +t
    if (chan.isTopicRestricted() && !chan.isOperator(client.getNickname())) {
        out_msg(client.getClientSocket(), ":" + server.getName() + ERR_CHANOPRIVSNEEDED(channel));
        return;
    }
    
    // Nettoyage du nouveau topic
    if (!new_topic.empty() && new_topic[0] == ':')
        new_topic = new_topic.substr(1);
    
    // Mise à jour du topic
    chan.setTopic(new_topic);
    
    // Diffusion du nouveau topic
    std::string topic_msg = ":" + client.getNickname() + " TOPIC " + channel + " :" + new_topic;
    const std::vector<Client *>& connected = chan.getConnectedClients();
    for (size_t it = 0;
         it < connected.size(); it++) {
        if (connected[it] != NULL) {
            out_msg(connected[it]->getClientSocket(), topic_msg);
        }
    }
}
