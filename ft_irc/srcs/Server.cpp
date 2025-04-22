#include "../includes/Server.hpp"
#include "../includes/Client.hpp"

int interruptSignal = 0;

Server::Server(int port, const std::string& password) : _port(port), _password(password), _serverFd(-1), _serverName("ft_irc")
{
    std::vector<std::string> nicklist;
    initializ_socket();
}

Server::~Server() 
{
    stop();
}

void Server::initializ_socket() 
{
    _serverFd = socket(AF_INET, SOCK_STREAM, 0);
    if (_serverFd < 0)
        throw std::runtime_error("Failed to create socket");
    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(_port);
    int on = 1;
    if (setsockopt(_serverFd, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on)) < 0)
    {
        close(_serverFd);
        throw std::runtime_error("Failed to setsockopt");
    }
    if (bind(_serverFd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) 
    {
        close(_serverFd);
        throw std::runtime_error("Failed to bind socket");
    }

    if (listen(_serverFd, SOMAXCONN) < 0) 
    {
        close(_serverFd);
        throw std::runtime_error("Failed to listen on socket");
    }

    pollfd serverPollFd;
    serverPollFd.fd = _serverFd;
    serverPollFd.events = POLLIN;
    _pollFds.push_back(serverPollFd);

    //std::cout << "Server started on port " << _port << std::endl;
}


void    signalHandler(int signum)
{
    std::cout << "\nInterrupt signal received" << std::endl;
    interruptSignal = signum;
}

void    Server::start() 
{
    signal(SIGINT, signalHandler);
    
    while (true) 
    {
        for (size_t i = 0; i < _pollFds.size(); ++i)
        {
            // _pollFds[i].events = 0;
            _pollFds[i].revents = 0;
        }
        int pollCount = poll(_pollFds.data(), _pollFds.size(), -1);
        if (interruptSignal != 0)
            return ;
        if (pollCount < 0) 
            throw std::runtime_error("Poll error");
        for (size_t i = 0; i < _pollFds.size(); ++i) 
        {
            if (_pollFds[i].revents & POLLIN) 
            {
                // usleep(10000);
                if (_pollFds[i].fd == _serverFd) 
                    Management_connection();
                else 
                    Management_client(_pollFds[i].fd);
            }
        }
    }
}

void Server::Management_connection() 
{
    struct sockaddr_in clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);
    int clientFd = accept(_serverFd, (struct sockaddr*)&clientAddr, &clientAddrLen);
    if (clientFd < 0) 
    {
        std::cerr << "Failed to accept client connection" << std::endl;
        return;
    }
    Client * newClient = new Client(clientFd);
    // _clients.push_back(newClient);
    
    pollfd clientPollFd;
    clientPollFd.fd = clientFd;
    clientPollFd.revents = 0;
    clientPollFd.events = POLLIN;
    _pollFds.push_back(clientPollFd);
    
    //changes
    // newClient->setClientSocket(clientFd);
    newClient->setHost(inet_ntoa(clientAddr.sin_addr));
    _clients.push_back(newClient);
    std::cout << "New connection from " << inet_ntoa(clientAddr.sin_addr) << ":" << ntohs(clientAddr.sin_port) << std::endl;    
}

void Server::Management_client(int clientFd)
{
    // Initialisation de la map de commandes
    static const std::map<std::string, CommandHandler> commandMap = initCommandMap();

    char buffer[1024];
    ssize_t bytesRead = recv(clientFd, buffer, sizeof(buffer) - 1, 0);
    if (bytesRead <= 0) 
    {
        //std::cout << "+++++++++++++++++++++++++++++++++++\n";
        if (findClientByFd(clientFd))
            removeClient(clientFd);
        return;
    }

    Client* client = findClientByFd(clientFd);
    if (!client) 
        return;

    buffer[bytesRead] = '\0';
    #ifdef DEBUG
        std::cout << "buffer : [" << buffer << "]\n";
    #endif
    client->appendToBuffer(buffer, bytesRead);

    while (client && client->hasCompleteCommand()) 
    {
        std::string line = client->extractCommand();
        if (line.empty())
            break;

        if (line.find('\r') != std::string::npos)
            line.erase(line.find('\r'), 1);

        std::istringstream iss(line);
        std::string cmd;
        iss >> cmd;

        // Convertir la commande en majuscule
        for (std::string::iterator it = cmd.begin(); it != cmd.end(); ++it) {
            *it = std::toupper(*it);
        }

        // Gestion des commandes spécifiques
        if (cmd == "CAP" && line.find("LS") != std::string::npos) {
            std::string response = ":" + _serverName + " CAP * LS :\r\n";
            send(clientFd, response.c_str(), response.size(), 0);
        }
        else if (cmd != "DCC" && cmd != "PONG" && cmd != "CAP" && cmd != "CAP END") 
        {
            std::map<std::string, CommandHandler>::const_iterator it = commandMap.find(cmd);
            if (it != commandMap.end()) 
            {
                it->second(line, clientFd, *client, *this);
                if (cmd == "QUIT")
                    return ;
            } 
            else
            {
                size_t i = 0;
                while (!line.empty() && line[0] == ' ') {
                    line.erase(0, 1);
                }
                for (; i < line.size() && line[i] != ' '; i++);
                if (i < line.size()) {
                    line.erase(i);
                }
                out_msg(client->getClientSocket(), "421 " + client->getNickname() + ERR_UNKNOWNCOMMAND(line));
            }
        }
    }
}


void    Server::removeEmptyChannels()
{
    for (std::map<std::string, Channel *>::iterator it = _channels.begin();
        it != _channels.end();)
    {
        if (it->second->isEmpty())
        {
            #ifdef DEBUG
                std::cout << "deleting empty channel\n";
            #endif
            delete it->second;
            _channels.erase(it++);
        }
        else
            it++;
    }
}

void    Server::removeClient(int clientFd)
{
    Client* client = findClientByFd(clientFd);

    if (!client)
        return ;
    if (client) {
        client->clearBuffer();
    }
    client->quitAllChannels();
    removeEmptyChannels();
    for (std::vector<std::string>::iterator it = nicklist.begin(); it != nicklist.end();) {
        if (client->getNickname() == *it) {
            it = nicklist.erase(it);
        } else {
            ++it;
        }
    }
    
    close(clientFd);

    for (std::vector<Client *>::iterator it = _clients.begin(); it != _clients.end(); ++it) 
    {
        if ((*it)->getClientSocket() == clientFd) {
            delete (*it);
            _clients.erase(it);
            break;
        }
    }

    for (std::vector<struct pollfd>::iterator it = _pollFds.begin(); it != _pollFds.end(); ++it) 
    {
        if (it->fd == clientFd) {
            _pollFds.erase(it);
            break;
        }
    }
    #ifdef DEBUG
        std::cout << "Client disconnected" << std::endl;
    #endif
}

void    Server::stop() 
{
    std::string msg;

    //Quitting all channels
    for (std::map<std::string, Channel *>::iterator it = _channels.begin();
    it != _channels.end(); it++)
    {
        const std::vector<Client *> &clients = it->second->getConnectedClients();
        while (clients.size())
        {   
            msg = ":" + clients[0]->getNickname() + "!" + clients[0]->getUsername() + "@" + clients[0]->getHost() + " PART " + it->first;
            for (size_t j = 0; j < clients.size(); j++)
            {
                out_msg(clients[j]->getClientSocket(), msg);
            }
            it->second->disconnectClient(clients[0]->getNickname());
        }
        delete it->second;
    }
    //Quitting all clients
    msg = ":server NOTICE * :Server shutting down - Goodbye";
    for (std::vector<Client *>::iterator it = _clients.begin(); it != _clients.end(); ++it) 
    {
        out_msg((*it)->getClientSocket(), msg);
        close((*it)->getClientSocket());
        delete *it;
    }
    close(_serverFd);
    std::cout << "Server stopped" << std::endl;
}

void Server::sendWelcomeMessages(int clientFd) 
{
    Client* client = findClientByFd(clientFd);
    if (!client) return;

    std::string welcome = ":" + _serverName + " 001 " + client->getNickname() 
                        + " :Welcome to " + _serverName + " IRC server\r\n";
    send(clientFd, welcome.c_str(), welcome.size(), 0);
}

Client* Server::findClientByFd(int fd) {
    for (std::vector<Client *>::iterator it = _clients.begin(); it != _clients.end(); it++) {
        if ((*it)->getClientSocket() == fd) {
            return (*it);
        }
    }
    return NULL;
}

std::vector<Client *> &Server::getClients()
{
    return (this->_clients);
}

std::map<std::string, Channel *> &Server::getChannels()
{
    return _channels;
}

const std::string &Server::getPassword(void) const
{
    return (this->_password);
}

std::ostream& operator<<(std::ostream& os, std::vector<Client *>& vec)
{
    for (std::vector<Client *>::iterator it = vec.begin()
        ; it != vec.end(); it++)
    {
        if (it != vec.begin())
            os << ' ';
        os << (*it)->getNickname();
    }
    return (os);
}

std::ostream& operator<<(std::ostream& os, std::map<std::string, Channel *>& map)
{
    for (std::map<std::string, Channel *>::iterator it = map.begin()
        ; it != map.end(); it++)
    {
        if (it != map.begin())
            os << " /// ";
        os << it->first << " - " << it->second->getChannelName();
    }
    return (os);
}

Client *Server::findClientByNickname(const std::string& nickname)
{
    for (std::vector<Client *>::iterator it = _clients.begin(); it != _clients.end(); it++) {
        if ((*it)->getNickname() == nickname) {
            return (*it);
        }
    }
    return NULL;
}

bool Server::nickalreadyregist(std::string nickname) {
    for (std::vector<std::string>::iterator it = nicklist.begin() ; it != nicklist.end(); ++it) {
        if (nickname == *it)
            return false;
    }
    return true;
}