/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   who.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvalino- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 19:19:04 by dvalino-          #+#    #+#             */
/*   Updated: 2025/04/02 19:19:05 by dvalino-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Server.hpp"

static void	whoChannel(Client &client, Channel &channel, Server &server)
{
	std::string msg;

	const std::vector<Client *> &clients = channel.getConnectedClients();
	for (size_t i = 0;
		i < clients.size(); i++)
	{
		if (clients[i]->getNickname() != client.getNickname())
		{
			msg = ": 352 " + client.getNickname() + " " + channel.getChannelName() 
				+ " " + clients[i]->getUsername() + " " + clients[i]->getHost() + " " + server.getName() + " " + clients[i]->getNickname() + " H :1 " + clients[i]->getRealname();
			out_msg(client.getClientSocket(), msg);
		}
	}
	msg = ": 352 " + client.getNickname() + " " + channel.getChannelName() + " " + client.getUsername()
		+ " " + client.getHost() + " " + server.getName() + " " + client.getNickname() + " H :1 " + client.getRealname();
	out_msg(client.getClientSocket(), msg);
}

void	ft_who(const std::string &input, Client& client, Server &server)
{
	std::string mask(input), msg;
	
	mask.erase(0, 4);
	if (mask[0] == '#')
	{
		std::map<std::string, Channel *> &channels = server.getChannels();
		if (channels.find(mask) != channels.end())
		{
			whoChannel(client, *channels[mask], server);
		}
	}
	else
	{
		Client * target = server.findClientByNickname(mask);
		if (target)
		{
			msg = ": 352 " + client.getNickname() + " " + target->getUsername() + " " + target->getHost() + " "
				+ server.getName() + " " + target->getNickname() + " H :1 " + target->getRealname();
			out_msg(client.getClientSocket(), msg);
		}
	}
	msg = ": 315 " + client.getNickname() + RPL_ENDOFWHO(mask);
	out_msg(client.getClientSocket(), msg);
}
