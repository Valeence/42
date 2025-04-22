/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvalino- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 15:54:44 by dvalino-          #+#    #+#             */
/*   Updated: 2025/03/08 15:54:45 by dvalino-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Channel.hpp"
#include "../includes/reply.hpp"

Channel::Channel()
{
	std::cout << "\033[92mChannel default constructor called\033[0m" << std::endl;
	this->_user_limite = 30;
	this->_invite_only = false;
	this->_limit_mode = true;
	this->_moderate = false;
	this->_no_external_msg = false;
	this->_secretKey = false;
	this->_topic_restricted = false;
	this->_ban_mode = true;
	
}

Channel::Channel(const Channel &other)
{
	std::cout << "\033[92mChannel copy constructor called\033[0m" << std::endl;
	*this = other;
}

Channel::~Channel()
{
	std::cout << "\033[91mChannel destructor called\033[0m" << std::endl;
}

Channel& Channel::operator=(const Channel &other)
{
	//std::cout << "\033[92mChannel assignment operator called\033[0m" << std::endl;
	if (this != &other)
	{
		this->_channel_name = other._channel_name;
		this->operators = other.operators;
		this->connected = other.connected;
		this->invited = other.invited;
		this->_invite_only = other._invite_only;
		this->_password = other._password;
		this->_topic = other._topic;
		this->_user_limite = other._user_limite;
		this->_limit_mode = other._limit_mode;
		this->_moderate = other._moderate;
		this->_no_external_msg = other._no_external_msg;
		this->_secretKey = other._secretKey;
		this->_topic_restricted = other._topic_restricted;
		this->_ban_mode = other._ban_mode;
	}
	return (*this);
}

Client	*Channel::getClient(std::string &nickname)
{
	if (this->isConnected(nickname))
	{
		for (size_t i = 0; i < connected.size(); i++)
		{
			if (connected[i]->getNickname() == nickname)
				return (this->connected[i]);
		}		
	}
	#ifdef DEBUG
		std::cout << "Client not connected\n";
	#endif
	return (NULL);
}

bool	Channel::getInviteOnly(void) const
{
	return (this->_invite_only);
}

const	std::string &Channel::getPassword(void) const
{
	return (this->_password);
}

const	std::string &Channel::getTopic(void) const
{
	return (this->_topic);
}

const	std::string &Channel::getChannelName(void) const
{
	return (this->_channel_name);
}

size_t	Channel::getUserLimite(void) const
{
	return (this->_user_limite);
}

size_t	Channel::getConnectedSize(void) const
{
	return (this->connected.size());
}

bool	Channel::getModerate() const
{
	return (this->_moderate);
}

bool	Channel::getNoExternal() const
{
	return (this->_no_external_msg);
}

bool	Channel::isKeyMode() const
{
	return (this->_secretKey);
}

bool	Channel::isLimited() const
{
	return (this->_limit_mode);
}

bool	Channel::isBanMode() const
{
	return (this->_ban_mode);
}

void	Channel::setPassword(const std::string &password)
{
	this->_password = password;
}

void	Channel::setTopic(const std::string &topic)
{
	this->_topic = topic;
}

void	Channel::setChannelName(const std::string &channel_name)
{
	this->_channel_name = channel_name;
}

void	Channel::setUserLimite(size_t number)
{
	this->_user_limite = number;
}

void	Channel::setInviteOnly(bool flag)
{
	this->_invite_only = flag;
}

void	Channel::setTopicRestricted(bool restricted) {
	_topic_restricted = restricted;
}

void	Channel::setModerate(bool flag)
{
	this->_moderate = flag;
}

void	Channel::setNoExternal(bool flag)
{
	this->_no_external_msg = flag;
}

void	Channel::setKeyMode(bool flag)
{
	this->_secretKey = flag;
}

void	Channel::setLimitMode(bool flag)
{
	this->_limit_mode = flag;
}

void	Channel::setBanMode(bool flag)
{
	this->_ban_mode = flag;
}

void	Channel::insertClientOperator(std::string &nickname)
{
	if (!this->isConnected(nickname))
	{
		#ifdef DEBUG
			std::cout << "\033[91mClient is not connected\033[0m" << std::endl;
		#endif
		return ;
	}

	// if (std::find(operators.begin(), operators.end(), &client) == operators.end())
	// // 	this->operators.push_back(&client);
	// Client *client = this->getClient(nickname);
	if (!this->isOperator(nickname))
		this->operators.push_back(nickname);
	// else 
		//std::cout << "\033[91mClient is already an operator\033[0m" << std::endl;
}

bool	Channel::checkClientConnection(Client *client)
{
	std::string nickname(client->getNickname());

	if (_ban_mode && isBanned(nickname))
	{
		out_msg(client->getClientSocket(), "474 " + nickname + ERR_BANNEDFROMCHAN(this->_channel_name));
		return (false);
	}
	if (!isEmpty() && _invite_only && !isInvited(nickname))
	{
		out_msg(client->getClientSocket(), "473 " + nickname + ERR_INVITEONLYCHAN(this->_channel_name));
		return (false);
	}
	if (!isEmpty() && _limit_mode && connected.size() > _user_limite)
	{
		out_msg(client->getClientSocket(), "471 " + nickname + ERR_CHANNELISFULL(this->_channel_name));
		return (false);
	}
	if (isConnected(nickname))
		return (false);
	return (true);
}

void	Channel::insertClientConnection(Client *client)
{
	std::string nickname(client->getNickname());
	//std::cout << "client nickname : " << nickname << std::endl;
	if (!checkClientConnection(client))
		return ;
	std::string msg;
	this->connected.push_back(client);
	//std::cout << "insert in channel : " << this->_channel_name << "\n";
	msg = ":" + nickname + "!" + client->getUsername() + "@" + client->getHost() + " JOIN :" + this->_channel_name + "\r\n";
	for (size_t it = 0; it < this->connected.size(); it++)
	{
		// //std::cout << "msg [" << msg << "]\n";
		send(this->connected[it]->getClientSocket(), msg.c_str(), msg.size(), 0);
	}
	msg = "353 " + nickname + " = ";
	// //std::cout << "msg : " << msg << "\n";
	msg += whoIsConnected();
	out_msg(client->getClientSocket(), msg);
	if (this->connected.size() == 1)
	{
		this->operators.push_back(nickname);
		msg = ":server MODE " + this->_channel_name + " +o " + nickname;
		out_msg(client->getClientSocket(), msg);
		sendMsgToConnected(msg, client);
	}
	// msg = "353 " + nickname + " = " + whoIsConnected() + "\r\n";
	out_msg(client->getClientSocket(), "366 " + nickname + RPL_ENDOFNAMES(_channel_name));
	client->insertChannel(this);
	#ifdef DEBUG
		if (isConnected(nickname))
			std::cout << "\033[93m" << nickname << " joined " << getChannelName() << "\033[0m\n";
		else
			std::cout << "\033[91m" << nickname << " couldn't join " << getChannelName() << "\033[0m\n";
	#endif
}

void	Channel::inviteClient(Client &client)
{
	if (!isInvited(client.getNickname()))
		this->invited.push_back(&client);
	// else
		//std::cout << "\033[91mClient has already been invited\033[0m" << std::endl;
}

void	Channel::removeClientOperator(std::string &nickname)
{
	if (isOperator(nickname))
	{
		for (size_t i = 0; i < this->operators.size(); i++)
		{
			if (this->operators[i] == nickname)
				this->operators.erase(this->operators.begin() + i);
		}
	}
	// else
		//std::cout << "Client not found in operators\n";
}

void	Channel::disconnectClient(std::string nickname)
{
	removeClientOperator(nickname);
	removeInvited(nickname);
	for (size_t i = 0; i < this->connected.size(); i++)
	{
		if (this->connected[i]->getNickname() == nickname)
			this->connected.erase(this->connected.begin() + i);
	}
}

void	Channel::sendMsgToConnected(std::string buffer, Client * sender)
{
	//std::cout << "In sendMsgToConnected function : " << sender->getNickname() << std::endl;
	std::string msg(":" + sender->getNickname() + buffer);
	size_t pos = msg.find(this->_channel_name);
	if (pos == std::string::npos)
	{
		//std::cout << "Bad name found\n";
		return ;
	}
	// msg.erase(pos, this->_channel_name.size() + 1);
	if (msg[msg.size() - 1] == '\n')
	{
		msg.erase(msg.size() - 1, 1);
	}
	if (msg[msg.size() - 1] == '\r')
	{
		msg.erase(msg.size() - 1, 1);
	}
	if (this->_moderate && !isOperator(sender->getNickname()))
		return ;
	msg.insert(msg.find(sender->getNickname()) + sender->getNickname().size(), "!" + sender->getUsername() + "@" + sender->getHost() + " ");
	for (size_t i = 0; i < connected.size(); i++)
	{
		if (connected[i]->getNickname() != sender->getNickname())
		{
			out_msg(connected[i]->getClientSocket(), msg);
		}
	}
}

void	Channel::sendModeMsgToConnected(std::string &modes)
{
	#ifdef DEBUG
		std::cout << modes << "\n";
	#endif
	removeDuplicates(modes);
	#ifdef DEBUG
		std::cout << modes << "\n";
	#endif

	std::string msg(" MODE " + _channel_name + " " + modes);
	bool flag = true;
	for (size_t i = 0; i < modes.size(); i++)
	{
		if (modes[i] == '+' || modes[i] == '-')
			flag = (modes[i] == '+');
		else if (flag && this->_secretKey && modes[i] == 'k')
			msg += " " + _password;
		else if (flag && this->_limit_mode && modes[i] == 'l')
			msg += " " + int_to_string(_user_limite);
	}
	
	for (size_t i = 0; i < this->connected.size(); i++)
	{
		out_msg(connected[i]->getClientSocket(), ":" + connected[i]->getNickname()
			+ "!" + connected[i]->getUsername() + "@" + connected[i]->getHost() + msg);
	}
}

const std::string Channel::whoIsConnected() 
{
	std::string msg;

	msg = this->_channel_name + " :";
	for (size_t i = 0; i < connected.size() && connected[i]; i++)
	{
		if (i != 0)
		{
			msg += ' ';
		}
		if (this->isOperator(connected[i]->getNickname()))
			msg += '@';
		msg += connected[i]->getNickname();
	}
	return (msg);
}

bool	Channel::isEmpty() const
{
	return (connected.empty());
}

// Vérifie si un client est opérateur
bool Channel::isOperator(const std::string& nickname) const {
    for (size_t i = 0; i < operators.size(); i++)
	{
		if (nickname == operators[i])
			return (true);
	}
	return (false);
}

// Vérifie si un client est connecté
bool Channel::isConnected(const std::string& nickname) const {
	for (size_t i = 0; i < connected.size(); i++)
	{
		if (connected[i] && nickname == connected[i]->getNickname())
			return (true);
	}
	return (false);
}

// Vérifie si un client est invité
bool Channel::isInvited(const std::string& nickname) const {
	for (size_t i = 0; i < invited.size(); i++)
	{
		if (nickname == invited[i]->getNickname())
			return (true);
	}
	return (false);
}

bool Channel::isBanned(const std::string& nickname) const
{
	for (size_t i = 0; i < banned.size(); i++)
	{
		if (nickname == banned[i])
			return (true);
	}
	return (false);
}

bool	Channel::isTopicRestricted() const {
    return _topic_restricted;
}

// Retourne la map des clients connectés
const std::vector<Client *>& Channel::getConnectedClients() const {
    return connected;
}

// Retourne la map des opérateurs
const std::vector<std::string>& Channel::getOperators() const {
    return operators;
}

// Vérifie si le channel est plein
bool Channel::isFull() const {
    return (_user_limite > 0 && connected.size() >= _user_limite);
}

// Retire un client invité
void Channel::removeInvited(const std::string& nickname) {
	if (!isInvited(nickname))
		return ;
	for (size_t i = 0; i < this->invited.size(); i++)
	{
		if (this->invited[i]->getNickname() == nickname)
			invited.erase(invited.begin() + i);
	}
}

// Met à jour un nickname dans toutes les listes
void Channel::updateNickname(const std::string& old_nick, const std::string& new_nick) {
    // Mise à jour dans connected
    // if (isConnected(old_nick)) {
	
    //     Client* client = getClient(old_nick);
	// 	connected[old_nick];
    //     connected.erase(old_nick);
    //     connected[new_nick] = client;
    // }
    
    // Mise à jour dans operators
	for (size_t i = 0; i < operators.size(); i++)
	{
		if (operators[i] == old_nick)
			operators[i] = new_nick;
	}
    
    // Mise à jour dans invited
	// for (size_t i = 0; i < invited.size(); i++)
	// {
	// 	if (invited[i]->getNickname() == old_nick)

	// }
	
    // if (invited.find(old_nick) != invited.end()) {
    //     Client* client = invited[old_nick];
    //     invited.erase(old_nick);
    //     invited[new_nick] = client;
    // }
}

// Diffuse un message à tous les clients connectés
void Channel::broadcast(const std::string& message, const std::string& except_nickname) {
    std::string formatted_msg = message + "\r\n";
    for (size_t i = 0; i < connected.size(); ++i) {
        if (connected[i]->getNickname() != except_nickname) {
            send(connected[i]->getClientSocket(), formatted_msg.c_str(), formatted_msg.size(), 0);
        }
    }
}

void	Channel::banClient(std::string &nickname)
{
	if (!isBanned(nickname))
		this->banned.push_back(nickname);
}

void	Channel::unbanClient(std::string &nickname)
{
	for (size_t i = 0; i < banned.size(); i++)
	{
		if (nickname == banned[i])
		{
			banned.erase(banned.begin() + i);
			return ;
		}
	}
}

void Channel::BanList(Client *client)
{
	std::string msg("367 " + client->getNickname() + " " + _channel_name + " ");

	for (size_t i = 0; i < banned.size(); i++)
	{
		out_msg(client->getClientSocket(), msg + banned[i]);
	}
	out_msg(client->getClientSocket(), "368 " + client->getNickname() + RPL_ENDOFBANLIST(_channel_name));
}
