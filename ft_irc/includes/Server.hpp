#ifndef SERVER_HPP
# define SERVER_HPP

# include <string>
# include <iostream>
# include <poll.h>
# include <vector>
# include <map>
# include <arpa/inet.h>
# include <unistd.h>
# include <sstream>
# include <stdexcept>
# include <cstring>
# include <sys/socket.h>
# include <netinet/in.h>
# include <sys/types.h>
# include <stdlib.h>
# include <string.h>
# include <csignal>
# include <poll.h>
# include "reply.hpp"
# include "Channel.hpp"
# include "Client.hpp"

class Client;
class Channel;

class Server
{
    public:
        Server(int port, const std::string &password);
        ~Server();
        void start();
        void stop();
        std::map<std::string, Channel *> &getChannels();
        std::vector<Client *> &getClients();
        std::vector<std::string> nicklist;
        const std::string& getName() const { return _serverName; }
        const std::string &getPassword(void) const;
        Client *findClientByNickname(const std::string& nickname);
        void    removeClient(int clientFd);
        bool nickalreadyregist(std::string nickname);
        
    private:
        Server();
        Server(const Server &other);
        // Server &operator=(const Server &other);

        void    initializ_socket();
        void    Management_connection();
        void    Management_client(int clientFd);
        void sendWelcomeMessages(int clinetFd);
        Client* findClientByFd(int clientFd);
        void removeEmptyChannels();
        
        int _port;
        std::string _password;
        int _serverFd;
        std::string _serverName;
        std::vector<Client *> _clients;
        std::map<std::string, Channel *> _channels;
        std::vector<pollfd> _pollFds;
    };
    typedef void (*CommandHandler)(const std::string& line, int clientFd, Client& client, Server& server);
    
    std::map<std::string, CommandHandler> initCommandMap();
    void handlePass(const std::string& line, int clientFd, Client& client, Server& server);
    void handleNick(const std::string& line, int clientFd, Client& client, Server& server);
    void handleUser(const std::string& line, int clientFd, Client& client, Server& server);
    void handlePing(const std::string& line, int clientFd, Client& client, Server& server);
    void handlePrivmsg(const std::string& line, int clientFd, Client& client, Server& server);
    void handleJoin(const std::string& line, int clientFd, Client& client, Server& server);
    void handlePart(const std::string& line, int clientFd, Client& client, Server& server);
    void handleWhois(const std::string& line, int clientFd, Client& client, Server& server);
    void handleWho(const std::string& line, int clientFd, Client& client, Server& server);
    void handleMode(const std::string& line, int clientFd, Client& client, Server& server);
    void handleInvite(const std::string& line, int clientFd, Client& client, Server& server);
    void handleKick(const std::string& line, int clientFd, Client& client, Server& server);
    void handleTopic(const std::string& line, int clientFd, Client& client, Server& server);
    void handleQuit(const std::string& line, int clientFd, Client& client, Server& server);
    
    std::string int_to_string(int i);
    void    out_msg(int clientFD, const std::string &msg);
    void    removeDuplicates(std::string &str);
    void    ft_whois(const std::string &line, Client& client, Server &server);
    void    ft_user(const std::string &input, int clientFd, Client& client, Server& server);
    void    ft_nick(const std::string &buffer, int clientFD, Client &client, Server &server);
    void    ft_join(const std::string &buffer, Client &client, Server &server);
    void	ft_msg(const char *buffer, Client *sender, Server &server);
    void    ft_kick(const std::string &input, Client &client, Server &server);
    void    ft_invite(const std::string &input, Client &client, Server &server);
    void    ft_topic(const std::string &input, Client &client, Server &server);
    void	ft_part(const std::string &buffer, Client &client, Server &server);
    void	ft_mode(const std::string &buffer, Client &client, Server &server);
    void	ft_who(const std::string &input, Client& client, Server &server);
    void    userModeIs(Client &client);
    void    ChannelModeIs(Channel &channel, Client &client);
    
    std::ostream& operator<<(std::ostream& os, std::vector<Client *>& vec);
    std::ostream& operator<<(std::ostream& os, std::map<std::string, Channel *>& map);
    
    #endif