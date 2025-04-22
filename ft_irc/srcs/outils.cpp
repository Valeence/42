#include "../includes/Server.hpp"

// bool isValidNickName(std::string nickname)
// {
//     if(nickname.empty() || nickname.length() > 9)
//         return false;
//     if((nickname[0] > 58 &&  nickname[0] < 64) || (nickname[0] > 91 &&  nickname[0] < 96) || ((nickname[0] > 123)))
//         return false;
//     if (!isalnum(nickname[0]))
//         return false;
//     for(size_t i = 1; i < nickname.length(); i++)
//     {
//         if(!(isalnum(nickname[i]) || nickname[i] == '_' || nickname[i] == '-'))
//             return false;
//     }   
//     return true;
// }


std::string int_to_string(int value) 
{
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

void out_msg(int clientFD, const std::string &msg)
{
    std::string rep = msg + "\r\n";
    #ifdef DEBUG
        std::cout << "out_msg : " << rep << std::endl;
    #endif
    send(clientFD, rep.c_str(), rep.size(), 0);
}

void removeDuplicates(std::string &str)
{
	std::set<char> set(str.begin(), str.end());
	str.assign(set.begin(), set.end());
}


// void ft_nick(std::string &buffer, int clientFD)
// {
//     std::string nickname(buffer);
//     nickname.erase(0, 5);
//     if (nickname.empty())
//     {
//         out_msg(clientFD, "431 : No nickname given");
//         return;
//     }
//     if (!isValidNickName(nickname))
//     {
//         out_msg(clientFD, "432 : Invalid nickname");
//         return;
//     }
//     out_msg(clientFD, "001 : Welcome to the server " + nickname);
// }

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

// void ft_join(std::string &buffer, int clientFD, Client &client, Server &server)
// {
//     //std::cout << "in function ft_join\n";
//     const char *msg = buffer.c_str();
//     const char *channel_start = strchr(msg + 5, ' ');

//     if (channel_start == NULL)
//     {
//         out_msg(clientFD, "461 : JOIN command requires a channel name");
//         return;
//     }
//     //std::cout << "channel_start : [" << channel_start << "]\n";
//     channel_start++;
//     //std::cout << "channel_start : [" << channel_start << "]\n";
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
//     //std::cout << "channel_end : [" << channel_end << "]\n";
//     std::string channel_name(channel_start, channel_end);  
    
//     //std::cout << "channel_name : [" << channel_name << "]\n";
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

// void    ft_whois(std::string &input, Client& client, Server &server)
// {
//     std::stringstream line(input);
//     std::string str, msg;

//     //std::cout << "in whois function" << std::endl;
//     while (getline(line, str, ' '))
//     {
//         // //std::cout << "str : " << str << std::endl;
//         if (str == "WHOIS")
//             continue ;
//     }
//     //std::cout << "str : " << str << std::endl;
//     if (str.empty() || str == client.getNickname())
//     {
//         msg = client.getNickname() 
//             + RPL_WHOISUSER(client.getNickname(), client.getUsername(), client.getUsername(), client.getRealname())
//             + "\r\n";
//         msg += client.getNickname() + RPL_ENDOFWHOIS(client.getNickname()) + "\r\n";
//         send(client.getClientSocket(), msg.c_str(), msg.size(), 0);
//         return ;
//     }
//     std::vector<Client> &clients = server.getClients();
//     for (std::vector<Client>::iterator it = clients.begin()
//         ; it != clients.end(); it++)
//     {
//         if ((*it).getNickname() == str)
//         {
//             msg = client.getNickname() 
//             + RPL_WHOISUSER((*it).getNickname(),
//                 (*it).getUsername(), (*it).getUsername(), (*it).getRealname())
//             + "\r\n";
//             msg += client.getNickname() + RPL_ENDOFWHOIS((*it).getNickname()) + "\r\n";
//             send(client.getClientSocket(), msg.c_str(), msg.size(), 0);
//             return ;
//         }
//     }
//     msg = client.getNickname() + ERR_NOSUCHNICK(str) + "\r\n";
//     msg += client.getNickname() + RPL_ENDOFWHOIS(str) + "\r\n";
//     send(client.getClientSocket(), msg.c_str(), msg.size(), 0);
//     //std::cout << "WhoIs Not found : " << str << std::endl;
// }

// void ft_kick(std::string &input, Client &client, Server &server)
// {
//     std::stringstream ss(input);
//     std::string cmd, channel, target, reason;
    
//     ss >> cmd >> channel >> target;
//     std::getline(ss, reason);
    
//     if (channel.empty() || target.empty()) 
//     {
//         out_msg(client.getClientSocket(), ":" + server.getName() + ERR_NEEDMOREPARAMS("KICK"));
//         return;
//     }
    
//     std::map<std::string, Channel *>& channels = server.getChannels();
//     std::map<std::string, Channel *>::iterator chan_it = channels.find(channel);
//     if (chan_it == channels.end()) {
//         out_msg(client.getClientSocket(), ":" + server.getName() + ERR_NOSUCHCHANNEL(channel));
//         return;
//     }
    
//     Channel& chan = chan_it->second;
    
//     if (!chan.isOperator(client.getNickname())) {
//         out_msg(client.getClientSocket(), ":" + server.getName() + ERR_CHANOPRIVSNEEDED(channel));
//         return;
//     }
    
//     if (!chan.isConnected(target)) {
//         out_msg(client.getClientSocket(), ":" + server.getName() + ERR_USERNOTINCHANNEL(target, channel));
//         return;
//     }
    
//     std::string kick_msg = ":" + client.getNickname() + " KICK " + channel + " " + target;
//     if (!reason.empty()) {
//         kick_msg += " :" + reason.substr(1);
//     }
    
//     // Diffusion du message
//     const std::map<std::string, Client*>& connected = chan.getConnectedClients();
//     for (std::map<std::string, Client*>::const_iterator it = connected.begin();
//          it != connected.end(); ++it) {
//         if (it->second != NULL) {
//             out_msg(it->second->getClientSocket(), kick_msg);
//         }
//     }
    
//     chan.disconnectClient(target);
// }

// void ft_invite(std::string &input, Client &client, Server &server)
// {
//     std::stringstream ss(input);
//     std::string cmd, target, channel;
    
//     ss >> cmd >> target >> channel;
    
//     // Vérification des paramètres
//     if (target.empty() || channel.empty()) {
//         out_msg(client.getClientSocket(), ":" + server.getName() + ERR_NEEDMOREPARAMS("INVITE"));
//         return;
//     }
    
//     // Vérification de l'existence du channel
//     std::map<std::string, Channel *>& channels = server.getChannels();
//     std::map<std::string, Channel *>::iterator chan_it = channels.find(channel);
//     if (chan_it == channels.end()) {
//         out_msg(client.getClientSocket(), ":" + server.getName() + ERR_NOSUCHCHANNEL(channel));
//         return;
//     }
    
//     Channel& chan = chan_it->second;
    
//     // Vérification de la présence dans le channel
//     if (!chan.isConnected(client.getNickname())) {
//         out_msg(client.getClientSocket(), ":" + server.getName() + ERR_NOTONCHANNEL(channel));
//         return;
//     }
    
//     // Vérification des droits si mode +i
//     if (chan.getInviteOnly() && !chan.isOperator(client.getNickname())) {
//         out_msg(client.getClientSocket(), ":" + server.getName() + ERR_CHANOPRIVSNEEDED(channel));
//         return;
//     }
    
//     // Recherche du client cible
//     Client* target_client = server.findClientByNickname(target);
//     if (!target_client) {
//         out_msg(client.getClientSocket(), ":" + server.getName() + ERR_NOSUCHNICK(target));
//         return;
//     }

//     // Vérification si déjà dans le channel
//     if (chan.isConnected(target)) {
//         out_msg(client.getClientSocket(), ":" + server.getName() + ERR_USERONCHANNEL(target, channel));
//         return;
//     }
    
//     // Envoi de l'invitation
//     out_msg(target_client->getClientSocket(), ":" + client.getNickname() + " INVITE " + target + " " + channel);
//     out_msg(client.getClientSocket(), ":" + server.getName() + RPL_INVITING(client.getNickname(), target, channel));
    
//     // Ajout à la liste des invités si mode +i
//     if (chan.getInviteOnly()) {
//         chan.inviteClient(*target_client);
//     }
// }

// void ft_topic(std::string &input, Client &client, Server &server)
// {
//     std::stringstream ss(input);
//     std::string cmd, channel, new_topic;
    
//     ss >> cmd >> channel;
//     std::getline(ss, new_topic);
    
//     // Vérification des paramètres
//     if (channel.empty()) {
//         out_msg(client.getClientSocket(), ":" + server.getName() + ERR_NEEDMOREPARAMS("TOPIC"));
//         return;
//     }
    
//     // Vérification de l'existence du channel
//     std::map<std::string, Channel *>& channels = server.getChannels();
//     std::map<std::string, Channel *>::iterator chan_it = channels.find(channel);
//     if (chan_it == channels.end()) {
//         out_msg(client.getClientSocket(), ":" + server.getName() + ERR_NOSUCHCHANNEL(channel));
//         return;
//     }
    
//     Channel& chan = chan_it->second;
    
//     // Mode affichage du topic
//     if (new_topic.empty()) {
//         if (chan.getTopic().empty()) {
//             out_msg(client.getClientSocket(), ":" + server.getName() + RPL_NOTOPIC(client.getNickname(), channel));
//         } else {
//             out_msg(client.getClientSocket(), ":" + server.getName() + RPL_TOPIC(client.getNickname(), channel, chan.getTopic()));
//         }
//         return;
//     }
    
//     // Vérification de la présence dans le channel
//     if (!chan.isConnected(client.getNickname())) {
//         out_msg(client.getClientSocket(), ":" + server.getName() + ERR_NOTONCHANNEL(channel));
//         return;
//     }
    
//     // Vérification des droits si mode +t
//     if (chan.isTopicRestricted() && !chan.isOperator(client.getNickname())) {
//         out_msg(client.getClientSocket(), ":" + server.getName() + ERR_CHANOPRIVSNEEDED(channel));
//         return;
//     }
    
//     // Nettoyage du nouveau topic
//     if (!new_topic.empty() && new_topic[0] == ':')
//         new_topic = new_topic.substr(1);
    
//     // Mise à jour du topic
//     chan.setTopic(new_topic);
    
//     // Diffusion du nouveau topic
//     std::string topic_msg = ":" + client.getNickname() + " TOPIC " + channel + " :" + new_topic;
//     const std::map<std::string, Client*>& connected = chan.getConnectedClients();
//     for (std::map<std::string, Client*>::const_iterator it = connected.begin();
//          it != connected.end(); ++it) {
//         if (it->second != NULL) {
//             out_msg(it->second->getClientSocket(), topic_msg);
//         }
//     }
// }