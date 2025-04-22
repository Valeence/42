/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 18:05:16 by dvalino-          #+#    #+#             */
/*   Updated: 2025/04/03 17:02:04 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <string>
# include <iostream>
# include <vector>
# include "Channel.hpp"

class Channel;

class Client
{
private:
	std::string _nickname;
	std::string _username;
	std::string _realname;
	std::string _host;
	int			_client_socket;
	bool _hasnick;
	bool _hasuser;
	bool _fullregist;
	std::string _buffer;
	std::vector<Channel *> connected_channels;
	bool _invisible;
	bool _wallops;
	bool pass;

public:
	Client();
	Client(int fd);
	Client(std::string nick, std::string user, int socket);
	Client(const Client &other);
	~Client();
	
	Client &operator=(const Client &other);
	bool	operator==(const Client &other);
	bool	operator!=(const Client &other);
	
	bool	operator==(const Client *other);
	bool	operator!=(const Client *other);

	std::string getNickname(void) const;
	const std::string &getUsername(void) const;
	const std::string &getRealname(void) const;
	const std::string &getHost(void) const;
	const bool &getPass(void) const;

	int getClientSocket(void) const;
	bool isFullRegist() const;
	void checkRegist(int clientFd);
	void clearBuffer();
	bool isInvisible();
	bool GetWallops();

	void setNickname(const std::string &nickname);
	void setHost(const std::string &nickname);
	void setUsername(const std::string &username);
	void setRealname(const std::string &realname);
	void setClientSocket(int fd);
	void setNick(bool hasnick);
	void setUser(bool hasuser);
	void setInvisible(bool invisible);
	void setWallops(bool wallops);
	void setPass(bool pass);

	void insertChannel(Channel *channel);
	void removeChannel(std::string &name);
	void quitAllChannels();
	void appendToBuffer(const char* data, size_t len);
	bool hasCompleteCommand() const;
	std::string extractCommand();
};

#endif
