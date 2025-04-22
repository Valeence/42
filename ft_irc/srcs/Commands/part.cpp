 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvalino- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 17:37:34 by dvalino-          #+#    #+#             */
/*   Updated: 2025/03/29 17:37:36 by dvalino-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Server.hpp"

void	ft_part(const std::string &buffer, Client &client, Server &server)
{
	std::stringstream line(buffer);
	std::string str, channel_name;

	while (getline(line, str, ' '))
	{
		if (str == "PART")
			continue;
		channel_name = str;
		break ;
	}
	if (channel_name.empty())
	{
		out_msg(client.getClientSocket(), "461 " + client.getNickname() + ERR_NEEDMOREPARAMS("PART"));
		return ;
	}
	std::map<std::string, Channel *> &channels = server.getChannels();
	if (channels.find(channel_name) == channels.end())
	{
		out_msg(client.getClientSocket(),  "403 " + client.getNickname() + ERR_NOSUCHCHANNEL(channel_name));
		return ;
	}
	if (channels[channel_name]->isConnected(client.getNickname()))
	{
		// out_msg(client.getClientSocket(), ":" +  client.getNickname() + " PART " + channel_name);
		std::vector<Client *> clients = channels[channel_name]->getConnectedClients();
		for (size_t i = 0; i < clients.size(); i++)
		{
			// if (i->second->getNickname() != client.getNickname()) //check
				out_msg(clients[i]->getClientSocket(), ":" +  client.getNickname() + "!" + client.getUsername() + "@" + client.getHost() + " PART " + channel_name);
		}
		channels[channel_name]->disconnectClient(client.getNickname());
		client.removeChannel(channel_name);
		if (channels[channel_name]->isEmpty())
		{
			delete channels[channel_name];
			channels.erase(channel_name);
		}
		return ;
	}
	out_msg(client.getClientSocket(), "442 " + client.getNickname() + ERR_NOTONCHANNEL(channel_name));
}
