#include "../includes/Server.hpp"
#include "../includes/Client.hpp"


std::map<std::string, CommandHandler> initCommandMap()
{
    std::map<std::string, CommandHandler> m;
    m["PASS"]    = handlePass;
    m["NICK"]    = handleNick;
    m["USER"]    = handleUser;
    m["PING"]    = handlePing;
    m["PRIVMSG"] = handlePrivmsg;
    m["JOIN"]    = handleJoin;
    m["PART"]    = handlePart;
    m["WHOIS"]   = handleWhois;
    m["WHO"]     = handleWho;
    m["MODE"]    = handleMode;
    m["INVITE"]  = handleInvite;
    m["KICK"]    = handleKick;
    m["TOPIC"]   = handleTopic;
    m["QUIT"]    = handleQuit;
    return m;
}

void handlePass(const std::string& line, int fd, Client& client, Server& server) 
{
    if (line.empty() || line.size() <= 5)
    {
        out_msg(fd, "ERROR :Invalid password");
        // server.removeClient(fd);
        return ;
    }
    std::string pass = line.substr(5);
    pass = pass.substr(0, pass.find_first_of(" \r\n"));
    if (pass.empty() || pass != server.getPassword()) 
    {
        send(fd, "ERROR :Invalid password\r\n", 26, 0);
        server.removeClient(fd);
        return;
    }
    client.setPass(true);
}

void handleNick(const std::string& line, int fd, Client& client, Server& server) 
{
    if (!client.getPass()) 
    {
        send(fd, "ERROR :You must use a password first\r\n", 39, 0);
        server.removeClient(fd);
        return;
    }
    ft_nick(line, fd, client, server);
}

void handleUser(const std::string& line, int fd, Client& client, Server& server) 
{
    ft_user(line, fd, client, server);
}

void handlePing(const std::string& line, int fd, Client& client, Server& server) 
{
    (void)fd;   
    (void)client; 
    (void)server;
    std::string msg = line.substr(5) + "\r\n";
    if (msg.find(' ') != std::string::npos)
        msg = "PONG :" + msg;
    else
        msg = "PONG " + msg;
    send(fd, msg.c_str(), msg.size(), 0);
}

void handlePrivmsg(const std::string& line, int fd, Client& client, Server& server) 
{
    (void)fd;
    ft_msg(line.c_str(), &client, server);
}

void handleJoin(const std::string& line, int, Client& client, Server& server) 
{
    ft_join(line, client, server);
}

void handlePart(const std::string& line, int, Client& client, Server& server) 
{
    ft_part(line, client, server);
}

void handleWhois(const std::string& line, int, Client& client, Server& server)
{
    ft_whois(line, client, server);
}

void handleWho(const std::string& line, int, Client& client, Server& server)
 {
    ft_who(line, client, server);
}

void handleMode(const std::string& line, int, Client& client, Server& server) 
{
    ft_mode(line, client, server);
}

void handleInvite(const std::string& line, int, Client& client, Server& server) 
{
    ft_invite(line, client, server);
}

void handleKick(const std::string& line, int, Client& client, Server& server) 
{
    ft_kick(line, client, server);
}

void handleTopic(const std::string& line, int, Client& client, Server& server) 
{
    ft_topic(line, client, server);
}

void handleQuit(const std::string& line, int fd, Client& client, Server& server) 
{
    std::string quitMsg = line;
    if (quitMsg.find(':') != std::string::npos)
        quitMsg = quitMsg.substr(quitMsg.find(':') + 1);

    if (!quitMsg.empty() && quitMsg[quitMsg.length() - 1] == '\n')
        quitMsg.resize(quitMsg.length() - 1); 

    if (!quitMsg.empty() && quitMsg[quitMsg.length() - 1] == '\r')
        quitMsg.resize(quitMsg.length() - 1); 
    
    std::string msg = ":" + client.getNickname() + "!" + client.getUsername() + "@" + client.getHost()
                    + " QUIT :" + quitMsg;
    out_msg(client.getClientSocket(), msg);
    server.removeClient(fd);
}
