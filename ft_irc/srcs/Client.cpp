/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 15:53:41 by dvalino-          #+#    #+#             */
/*   Updated: 2025/04/03 17:02:11 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Client.hpp"

Client::Client() : _nickname(""), _username(""), _realname(""), _host(""), _hasnick(false), _hasuser(false), _fullregist(false),
	_buffer(""), _invisible(false), _wallops(false), pass(false)
{
	std::cout << "\033[92mClient default constructor called\033[0m" << std::endl;
}

Client::Client(int fd) : _nickname(""), _username(""), _realname(""), _host(""), _client_socket(fd), _hasnick(false), _hasuser(false), _fullregist(false),
	_buffer(""), _invisible(false), _wallops(false), pass(false)
{
	std::cout << "\033[92mClient fd constructor called\033[0m" << std::endl;
}

Client::Client(std::string nick, std::string user, int socket)
	: _nickname(nick), _username(user), _realname(""), _host(""),
	_client_socket(socket), _hasnick(true), _hasuser(true), _fullregist(true), _buffer(""), _invisible(false), _wallops(false), pass(false)
{
	std::cout << "\033[92mClient constructor called\033[0m" << std::endl;
}

Client::Client(const Client &other)
{
	std::cout << "\033[92mClient copy constructor called\033[0m" << std::endl;
	*this = other;
}

Client& Client::operator=(const Client &other)
{
	// std::cout << "\033[92mClient assignment operator called\033[0m" << std::endl;
	if (this != &other)
	{
		this->_client_socket = other._client_socket;
		this->_nickname = other._nickname;
		this->_username = other._username;
		this->_realname = other._realname;
		this->_fullregist = other._fullregist;
		this->_hasnick = other._hasnick;
		this->_hasuser = other._hasuser;
		this->_host = other._host;
		this->_invisible = other._invisible;
		this->_wallops = other._wallops;
	}
	return (*this);
}

Client::~Client()
{
	std::cout << "\033[91mClient destructor called\033[0m" << std::endl;
}

bool	Client::operator==(const Client &other)
{
	return (this->_nickname == other._nickname);
	// Ask team if check _client_socket
}

bool	Client::operator!=(const Client &other)
{
	return (!(*this == other));
}

// Check if necessary :
bool	Client::operator==(const Client *other)
{
	return (this == other);
}

bool	Client::operator!=(const Client *other)
{
	return (!(this == other));
}

std::string Client::getNickname(void) const
{
	return (this->_nickname);
}

const std::string &Client::getUsername(void) const
{
	return (this->_username);
}

const std::string &Client::getRealname(void) const
{
	return (_realname);
}

const std::string &Client::getHost(void) const
{
	return (_host);
}

int Client::getClientSocket(void) const
{
	return (this->_client_socket);
}

bool	Client::isInvisible()
{
	return (this->_invisible);
}

bool	Client::GetWallops()
{
	return (this->_wallops);
}

void Client::setNickname(const std::string &nickname)
{
	this->_nickname = nickname;
}

void Client::setUsername(const std::string &username)
{
	this->_username = username;
}

void Client::setRealname(const std::string &realname)
{
	this->_realname = realname;
}

void Client::setHost(const std::string &host)
{
	this->_host = host;
}

void Client::setClientSocket(int fd)
{
	this->_client_socket = fd;
}

void	Client::setInvisible(bool invisible)
{
	this->_invisible = invisible;
}

void	Client::setWallops(bool wallops)
{
	this->_wallops = wallops;
}

void	Client::insertChannel(Channel *channel)
{
	connected_channels.push_back(channel);
}

void	Client::removeChannel(std::string &name)
{
	for (size_t i = 0; i < connected_channels.size(); i++)
	{
		if (connected_channels[i]->getChannelName() == name)
		{
			connected_channels.erase(connected_channels.begin() + i);
			break ;
		}
	}
}

void	Client::quitAllChannels()
{
	// std::string msg("PART ");
	for (size_t i = 0; i < connected_channels.size(); i++)
	{
		connected_channels[i]->sendMsgToConnected("PART " + connected_channels[i]->getChannelName(), this);
		out_msg(_client_socket, ":" + _nickname + "!" + _username + "@" + _host + " PART " + connected_channels[i]->getChannelName());
		connected_channels[i]->disconnectClient(_nickname);
	}
	connected_channels.clear();
}


void Client::appendToBuffer(const char* data, size_t len)
{
    for (size_t i = 0; i < len; i++) {
        if ((unsigned char)data[i] < 32 && data[i] != '\r' && data[i] != '\n' && data[i] != '\t') {
            continue;
        }
        _buffer += data[i];
    }
}

bool	Client::hasCompleteCommand() const
{
	return (_buffer.find("\n") != std::string::npos); //changed
}

std::string Client::extractCommand()
{
    std::string::size_type pos = _buffer.find("\n"); //changed
    if (pos == std::string::npos) {
        if (_buffer.size() > 512) {
            _buffer.clear();
            return "";
        }
        return "";
    }
    std::string command = _buffer.substr(0, pos);
    _buffer.erase(0, pos + 1); //changed + 2
    return command;
}

void Client::clearBuffer()
{
    _buffer.clear();
}

bool	Client::isFullRegist() const
{
	return (_fullregist);
}

void	Client::checkRegist(int clientFd)
{
	if (_hasnick && _hasuser && !_fullregist)
	{
		_fullregist = true;
		std::string msg = ":" + _nickname + " 001 " + _nickname + " :Welcome to the IRC server\r\n";
		send(clientFd, msg.c_str(), msg.size(), 0);
		// msg = "PING " + _nickname + "\r\n";
		// send(clientFd, msg.c_str(), msg.size(), 0);
	}

}

void	Client::setNick(bool hasnick)
{
	_hasnick = hasnick;
}

void	Client::setUser(bool hasuser)
{
	_hasuser = hasuser;
}

const bool	&Client::getPass() const
{
	return (this->pass);
}

void	Client::setPass(bool pass)
{
	this->pass = pass;
}