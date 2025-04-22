/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvalino- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 17:58:11 by dvalino-          #+#    #+#             */
/*   Updated: 2025/03/07 17:58:12 by dvalino-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

// # include <iostream>
// # include <map>
// # include <algorithm>
// # include <string>
// #include <sys/socket.h>
// # include "Client.hpp"
# include "Server.hpp"
# include "set"

class Client;

class Channel
{
private:
	std::vector<std::string> operators;
	std::vector<Client *> connected;
	std::vector<Client *> invited;
	std::vector<std::string> banned;
	
	bool		_invite_only;
	bool		_moderate;
	bool		_no_external_msg;
	bool		_secretKey;
	bool		_topic_restricted;
	bool		_limit_mode;
	bool		_ban_mode;
	std::string	_password;
	std::string _topic;
	std::string _channel_name;
	size_t		_user_limite;
	Client		*getClient(std::string &nickname);
	bool		checkClientConnection(Client *client);
public:

	Channel();
	Channel(const Channel &other);
	~Channel();

	Channel &operator=(const Channel &other);

	void insertClientOperator(std::string &nickname);
	void insertClientConnection(Client *client);
	void inviteClient(Client &client);
	void banClient(std::string &nickname);
	void unbanClient(std::string &nickname);
	void disconnectClient(std::string nickname);
	void removeClientOperator(std::string &nickname);

	const std::string &getPassword(void) const;
	const std::string &getTopic(void) const;
	const std::string &getChannelName(void) const;
	size_t 	getUserLimite(void) const;
	size_t	getConnectedSize(void) const;
	bool getInviteOnly(void) const;
	bool getModerate() const;
	bool getNoExternal() const;
	bool isKeyMode() const;
	bool isTopicRestricted() const;
	bool isLimited() const;
	bool isBanMode() const;

	void setPassword(const std::string &password);
	void setTopic(const std::string &topic);
	void setChannelName(const std::string &channel_name);
	void setUserLimite(size_t number);
	void sendMsgToConnected(std::string buffer, Client * sender);
	void sendModeMsgToConnected(std::string &modes);
	void setInviteOnly(bool flag);
	void setTopicRestricted(bool flag);
	void setModerate(bool flag);
	void setNoExternal(bool flag);
	void setKeyMode(bool flag);
	void setLimitMode(bool flag);
	void setBanMode(bool flag);

	const std::string whoIsConnected();
	void BanList(Client *client);
	bool isEmpty() const;
	bool isOperator(const std::string& nickname) const;
    bool isConnected(const std::string& nickname) const;
    bool isInvited(const std::string& nickname) const;
	bool isBanned(const std::string& nickname) const;
    const std::vector<Client *>& getConnectedClients() const;
    const std::vector<std::string>& getOperators() const;
    bool isFull() const;
    void removeInvited(const std::string& nickname);
    void updateNickname(const std::string& old_nick, const std::string& new_nick);
    void broadcast(const std::string& message, const std::string& except_nickname = "");
};

#endif
