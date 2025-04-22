/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:57:49 by dvalino-          #+#    #+#             */
/*   Updated: 2025/04/03 16:33:11 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Server.hpp"

// this should be good
static void	manageClientModes(std::string &modes, Client &client)
{
	bool flag = false, unknow_mode_found = false;
	#ifdef DEBUG
		std::cout << "In manage client modes function : [" << modes << "]\n";
	#endif
	for (size_t i = 0; i < modes.size(); i++)
	{
		if (modes[i] == '+' || modes[i] == '-')
			flag = (modes[i] == '+');
		else if (modes[i] == 'i')
		{
			client.setInvisible(flag);
		}
		else if (modes[i] == 'w')
			client.setWallops(flag);
		else if (modes[i] != ' ')
			unknow_mode_found = true;
	}
	if (unknow_mode_found)
		out_msg(client.getClientSocket(), "501 " + client.getNickname() + ERR_UMODEUNKNOWNFLAG);
}

static void manageChannelModes(std::string &modes, Channel &channel, Client &client)
{
	#ifdef DEBUG
		std::cout << "modes : [" << modes << "]\n";
	#endif
	if (!channel.isOperator(client.getNickname()))
	{
		out_msg(client.getClientSocket(), "482 " + client.getNickname() + ERR_CHANOPRIVSNEEDED(channel.getChannelName()));
		return ;
	}
	std::stringstream args(modes);
	std::string str;
	bool flag = false;
	
	getline(args, str,' ');
	for (size_t i = 0; i < modes.size() && modes[i] != ' '; i++)
	{
		if (modes[i] == '+' || modes[i] == '-')
			flag = (modes[i] == '+');
		else if (modes[i] == 'i')
			channel.setInviteOnly(flag);
		else if (modes[i] == 'm')
			channel.setModerate(flag);
		else if (modes[i] == 'n')
			channel.setNoExternal(flag);
		else if (modes[i] == 't')
			channel.setTopicRestricted(flag);
		else if (modes[i] == 'b')
		{
			channel.setBanMode(flag);
			str = "";
			getline(args, str, ' ');
			if (str.empty())
				continue;
			if (flag)
				channel.banClient(str);
			else
				channel.unbanClient(str);
		}
		else if (modes[i] == 'l')
		{
			channel.setLimitMode(flag);
			if (flag)
			{
				str = "";
				if (!getline(args, str, ' '))
					continue;
				long number = std::strtol(str.c_str(), NULL, 0);
				if (number < 1 || number > 100)
					std::cout << "error : number not in range (1, 100)\n";
				else
					channel.setUserLimite(number);
			}
		}
		else if (modes[i] == 'k')
		{
			channel.setKeyMode(flag);
			if (flag)
			{
				str = "";
				getline(args, str, ' ');
				if (str.empty() && channel.getPassword().empty())
				{
					out_msg(client.getClientSocket(), "461 " + client.getNickname()
						+ " " + channel.getChannelName() + ERR_NEEDMOREPARAMS("MODE"));//channel.getChannelName(), 'k', "password", "Channel without password"));
					channel.setKeyMode(false);
					continue;
				}
				#ifdef DEBUG
					std::cout << "pass : " << str << std::endl;
				#endif
			    if (str.find(' ') != std::string::npos || str.size() < 4)
    			{
        			out_msg(client.getClientSocket(), "525 " + client.getNickname() + ERR_INVALIDKEY(channel.getChannelName()));
					channel.setKeyMode(false);
					continue;
			    }
				channel.setPassword(str);
			}
		}
		else if (modes[i] == 'o')
		{
			str = "";
			getline(args, str, ' ');
			if (flag && channel.isConnected(str))
				channel.insertClientOperator(str);
			else if (!flag && channel.isConnected(str) && channel.isOperator(str))
				channel.removeClientOperator(str);
		}
	}
	if (modes.find(' ') != std::string::npos)
		modes.erase(modes.find(' '));
	channel.sendModeMsgToConnected(modes);
}

void userModeIs(Client &client)
{
	std::string modes;

	modes = "+";
	if (client.isInvisible())
		modes += "i";
	if (client.GetWallops())
		modes += "w";
	if (modes.size() > 1)
		out_msg(client.getClientSocket(), ":" + client.getNickname() + " MODE " + client.getNickname() + " " + modes);
}

void ChannelModeIs(Channel &channel, Client &client)
{
	std::string modes("+");

	if (channel.getInviteOnly())
		modes += 'i';
	if (channel.getModerate())
		modes += 'm';
	if (channel.getNoExternal())
		modes += 'n';
	if (channel.isTopicRestricted())
		modes += 't';
	if (channel.isBanMode())
		modes += 'b';
	if (channel.isLimited())
		modes += 'l';
	if (channel.isKeyMode())
		modes += 'k';
	std::stringstream msg;
	msg << "324 " << client.getNickname() << " " << channel.getChannelName() << ((modes.size() > 1) ? (" " + modes) : (""));
	if (modes.size() > 1)
	{
		for (size_t i = 0; i < modes.size(); i++)
		{
			if (modes[i] == 'k')
			{
				msg << " " << channel.getPassword();
			}
			else if (modes[i] == 'l')
			{
				msg << " " << channel.getUserLimite();
			}
		}
	}
	out_msg(client.getClientSocket(), msg.str());
}

static bool checkClient(std::string &target, Client *target_client, Client &client)
{
	if (target_client && target_client->getNickname() == client.getNickname())
		return (true);

	if (target_client == NULL)
		out_msg(client.getClientSocket(), "401 " + client.getNickname() + ERR_NOSUCHNICK(target));
	else if (target_client->getNickname() != client.getNickname())
		out_msg(client.getClientSocket(), "401 " + client.getNickname() + ERR_NOSUCHNICK(target));
	return (false);
}

void	ft_mode(const std::string &buffer, Client &client, Server &server)
{
	std::stringstream line(buffer);
	std::string str, target, modes;
	int count = 0;

	while (getline(line, str, ' '))
	{
		count++;
		if (count == 1 && str == "MODE")
			continue;
		else if (count == 2)
			target = str;
		else
		{
			if (!modes.empty())
				modes += ' ';
			modes += str;
		}
	}
	if ((count >= 2 && target[0] != '#'))
	{
		Client *target_client = server.findClientByNickname(target);
		if (!checkClient(target, target_client, client))
			return ;
		if (!modes.empty())
			manageClientModes(modes, client);
		userModeIs(client);
	}
	else if (count >= 2 && target[0] == '#')
	{
		std::map<std::string, Channel *> &channels = server.getChannels();

		if (channels.find(target) == channels.end())
			out_msg(client.getClientSocket(),"403 " + client.getNickname() + ERR_NOSUCHCHANNEL(target));
		else if (!modes.empty() && modes != "b")
			manageChannelModes(modes, *channels[target], client);
		else if (!modes.empty() && modes == "b")
			channels[target]->BanList(&client);
		else if (modes.empty())
			ChannelModeIs(*channels[target], client);
	}
}
