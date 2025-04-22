/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvalino- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 20:15:35 by dvalino-          #+#    #+#             */
/*   Updated: 2025/03/24 20:15:37 by dvalino-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Server.hpp"

void    ft_invite(const std::string &input, Client &client, Server &server)
{
    std::stringstream ss(input);
    std::string cmd, target, channel;
    
    ss >> cmd >> target >> channel;
    
    // Vérification des paramètres
    if (target.empty() || channel.empty()) {
        out_msg(client.getClientSocket(), ":" + server.getName() + ERR_NEEDMOREPARAMS("INVITE"));
        return;
    }
    
    // Vérification de l'existence du channel
    std::map<std::string, Channel *>& channels = server.getChannels();
    std::map<std::string, Channel *>::iterator chan_it = channels.find(channel);
    if (chan_it == channels.end()) {
        out_msg(client.getClientSocket(), ":" + server.getName() + ERR_NOSUCHCHANNEL(channel));
        return;
    }
    
    Channel& chan = *chan_it->second;
    
    // Vérification de la présence dans le channel
    if (!chan.isConnected(client.getNickname())) {
        out_msg(client.getClientSocket(), ":" + server.getName() + ERR_NOTONCHANNEL(channel));
        return;
    }
    
    // Vérification des droits si mode +i
    if (chan.getInviteOnly() && !chan.isOperator(client.getNickname())) {
        out_msg(client.getClientSocket(), ":" + server.getName() + ERR_CHANOPRIVSNEEDED(channel));
        return;
    }
    
    // Recherche du client cible
    Client *target_client = server.findClientByNickname(target);
    if (!target_client) {
        out_msg(client.getClientSocket(), ":" + server.getName() + ERR_NOSUCHNICK(target));
        return;
    }

    // Vérification si déjà dans le channel
    if (chan.isConnected(target)) {
        out_msg(client.getClientSocket(), ":" + server.getName() + ERR_USERONCHANNEL(target, channel));
        return;
    }
    
    // Envoi de l'invitation
    #ifdef DEBUG
        std::cout << "inviting " << client.getNickname() << "to channel " << channel << "\n";
    #endif
    out_msg(target_client->getClientSocket(), ":" + client.getNickname() + "!" + client.getUsername() + "@" + client.getHost() + " INVITE " + target + " " + channel);
    out_msg(client.getClientSocket(), ":" + server.getName() + " " + client.getNickname() + RPL_INVITING(target, channel));
    
    // Ajout à la liste des invités si mode +i
    if (chan.getInviteOnly()) {
        chan.inviteClient(*target_client);
    }
}
