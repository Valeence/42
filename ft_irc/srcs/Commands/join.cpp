/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvalino- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:59:14 by dvalino-          #+#    #+#             */
/*   Updated: 2025/03/24 18:59:15 by dvalino-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Server.hpp"

static bool passwordCheck(Client &client, std::string password_attempt, Channel *channel)
{
    if (channel->isEmpty())
        return (true);
    if (channel->isKeyMode() && (password_attempt.empty() || password_attempt != channel->getPassword()))
    {
        out_msg(client.getClientSocket(), "475 " + client.getNickname() + ERR_BADCHANNELKEY(channel->getChannelName()));
        return false;
    }
    return (true);
}

void    ft_join(const std::string &buffer, Client &client, Server &server)
{
    std::string channel_name, str, password("");
    std::stringstream line(buffer);
    int count = 0;

    while (getline(line, str, ' '))
    {
        if (count == 1)
            channel_name = str;
        if (count == 2)
            password = str;
        count++;
    }

    if (channel_name[channel_name.size() - 1] == '\r')
        channel_name.erase(channel_name.end() - 1);

    if (channel_name.empty())
    {
        out_msg(client.getClientSocket(), "461 : JOIN command requires a channel name");
        return;
    }
    if (channel_name.empty())
    {
        out_msg(client.getClientSocket(), "461 : Invalid channel name");
        return;
    }
    if (channel_name[0] != '#')
    {
        out_msg(client.getClientSocket(), "476 " + client.getNickname() + ERR_BADCHANMASK(channel_name));
        return ;
    }
    if (server.getChannels().find(channel_name) == server.getChannels().end())
    {
        Channel *chan = new Channel;
        chan->setChannelName(channel_name);
        server.getChannels()[channel_name] = chan;
        #ifdef DEBUG
            std::cout << "\033[96mCreating channel " << channel_name << "\033[0m" << std::endl;
        #endif
    }

    #ifdef DEBUG
        std::cout << "inserting client in channel\n";
    #endif
    if (!passwordCheck(client, password, server.getChannels()[channel_name]))
        return ;
    server.getChannels()[channel_name]->insertClientConnection(&client);
}


// out_msg(client.getClientSocket(), client.getNickname() + " JOIN :" + channel_name);  // Message standard IRC
// std::string msg("353 " + client.getNickname() + " = " + server.getChannels()[channel_name].whoIsConnected() + "\r\n");
// send(client.getClientSocket(), msg.c_str(), msg.size(), 0);//  + client.getNickname() + " "
// // out_msg(client.getClientSocket(), "353 " + server.getChannels()[channel_name].whoIsConnected());
// out_msg(client.getClientSocket(), "366 " + client.getNickname() + RPL_ENDOFNAMES(channel_name));
// void ft_join(std::string &buffer, int clientFD, Client &client, Server &server)
// {
//     const char *msg = buffer.c_str();
//     const char *channel_start = strchr(msg + 5, ' ');

//     if (channel_start == NULL)
//     {
//         out_msg(clientFD, "461 : JOIN command requires a channel name");
//         return;
//     }
//     channel_start++;
//     const char *channel_end = strchr(channel_start, '\0');
//     if (channel_end == NULL)
//         channel_end = strchr(channel_start, '\r');
//     if (channel_end == NULL) 
//         channel_end = strchr(channel_start, '\n');
//     if (channel_end == NULL)
//     {
//         out_msg(clientFD, "461 : Invalid channel name");
//         return;
//     }
//     if (channel_end == NULL) 
//     {
//         out_msg(clientFD, "461 : Invalid channel name");
//         return;
//     }
//     std::string channel_name(channel_start, channel_end);  
    
//     if (server.getChannels().find(channel_name) == server.getChannels().end())
//     {
//         Channel chan;
//         chan.setChannelName(channel_name);
//         server.getChannels()[channel_name] = chan;
//     }
//     server.getChannels()[channel_name].insertClientConnection(client);
//     out_msg(clientFD, "JOIN :" + channel_name);  // Message standard IRC
//     out_msg(clientFD, "001 : Welcome to the channel " + channel_name);

// }

