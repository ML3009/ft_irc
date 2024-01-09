/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purple <purple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 11:21:50 by purple            #+#    #+#             */
/*   Updated: 2024/01/09 10:14:18 by purple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

/*----------------- Coplien ------------- */

server::server(){
	_port = 6667;
	_password = "password";
	_userCount = 0;
	_upTime = clock();
	_ID = "IRC";
	_maxtimeout = 10000;

	display_constructor(SERVER_DC);
}


server::server(int port, std::string password){
	_ID = "IRC";
	_port = port;
	_password = password;
	_userCount = 0;
	_upTime = clock();
	_maxtimeout = 10000;

	display_constructor(SERVER_PC);

}

server::server(const server& rhs){

	*this = rhs;
	display_constructor(SERVER_CC);

}

server&	server::operator=(const server& rhs){

	if (this != &rhs){
		_port = rhs._port;
		_password = rhs._password;
		_userCount = rhs._userCount;
		_upTime = rhs._upTime;
		_maxtimeout = rhs._maxtimeout;
		_ID = rhs._ID;
	}
	display_constructor(SERVER_AO);
	return *this;
}

server::~server(){
	display_constructor(SERVER_DD);

}


/*---------------- Operator ------------- */



/*---------- Getter / Setter ------------ */

int server::getUserCount() const { return _userCount;}
std::vector<pollfd> server::getpollfd() { return _pollFD;}
std::string server::getPassword() const{return _password;}
std::string server::getID() const{return _ID;}
bot 		&server::getbot() {return _bot;}
std::map<int, user> &server::getUserMap(){return _clientMap;}
std::map<std::string, channel>& server::getChannelMap(){return _channelMap;}

/*--------------- Function -------------- */



void server::init_server(){

	debug("init_server", BEGIN);
	int opt = 1;
	int	serverSocket;
	_userCount = 0;
	struct	sockaddr_in serverAdress;

	// Set up server address
    serverAdress.sin_family = AF_INET;
    serverAdress.sin_addr.s_addr = INADDR_ANY;
    serverAdress.sin_port = htons(_port);

	//Create socket
	!((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1 ) ? void() : (std::perror("socket"), throw socketException());

	//Option socket to reuse adress | port
	#ifdef SO_REUSEPORT
	!(setsockopt(serverSocket, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt)) == -1) ? void() : (std::perror("socket option"), throw socketoptException());
	#endif
	!(setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1) ? void() : (std::perror("socket option"), throw socketoptException());

	//Option socket to be non bloquant
	!(fcntl(serverSocket, F_SETFL, O_NONBLOCK) == -1) ? void() : (std::perror("fcntl"), throw fcntlException());

	//Bind the socket
	!(bind(serverSocket, (struct sockaddr *)&serverAdress, sizeof(serverAdress)) == -1) ? void() : (std::perror("bind"), throw bindException());

	//Listen for incoming connections
	!(listen(serverSocket, serverAdress.sin_port) == -1) ? void() : (std::perror("listen"), throw listenException());

	_pollFD.push_back(pollfd());
	_pollFD.back().fd = serverSocket;
	_pollFD.back().events = POLLIN;
	std::cout << "\x1b[32m \x1b[3m" << "Initialisation ended sucessfully" << "\x1b[0m" << std::endl;
	debug("init_server", END);
	return;
}

void server::run_server(){

	debug("run_server", BEGIN);
	!(poll(&_pollFD[0], _pollFD.size(), 10000) == -1) ? void() : (std::perror("poll"), throw pollException());
	(_pollFD[0].revents == POLLIN) ? getNewClient() : getClientMessage();
	if (_userCount > 0)
		for(std::map<int, user>::iterator it = _clientMap.begin(); it != _clientMap.end(); it++)
			if (LastPing(it->second) == TIMEOUT)
				return timeout_client(it->first);

	debug("run_server", END);

}
/*--------------- Exception ------------- */

void server::getNewClient(){
	debug("getNewClient", BEGIN);

	int fd;
	struct sockaddr_in	address = {};
	socklen_t			size 	= sizeof(sockaddr_in);

	!((fd = accept(_pollFD[0].fd, (struct sockaddr *)&address, &size)) == -1) ? void() : (std::perror("accept"), throw acceptException());
	!(fcntl(fd, F_SETFL, O_NONBLOCK) == -1) ? void() : (std::perror("fcntl"), throw fcntlException());

	user User(fd);
	_clientMap[fd] = User;
	_pollFD.push_back(pollfd());
	_pollFD.back().fd = fd;
	_pollFD.back().events = POLLIN;
	_userCount++;
	debug("getNewClient", END);
}

void server::getClientMessage(){
	debug("getClientMessage", BEGIN);
	if (_userCount == 0 || _pollFD.size() == 1)
		return ;
	std::vector<pollfd>::iterator it;
	for (it = _pollFD.begin(); it != _pollFD.end(); it++)
	{

		if (it->revents == POLLIN)
		{
			char buffer[512];
			int bytes = recv(_clientMap[it->fd].getfd(), buffer, 1024, 0);
			if (bytes <= 0)
			{
				disconnect_client(_clientMap[it->fd]);
				it = _pollFD.erase(it);
				return;
			}
			else{
				buffer[bytes] = '\0';
				_clientMap[it->fd].parseClientMessage(*this, buffer);
			}
		}
	}
	debug("getClientMessage", END);
}

void server::disconnect_client(user &client){
	close(client.getfd());
	_clientMap.erase(client.getfd());
	_userCount--;
	std::cout << "\e[0;33m" << "[Disconnected]"  << " \e[0m" << std::endl;
}

void server::closeServerSocket() {close(_pollFD[0].fd);}

void server::timeout_client(int fd){
	disconnect_client(_clientMap[fd]);
	std::cout << "\e[0;36m" << " user has been kick for [ AFK ]" << " \e[0m" << std::endl;
	// std::vector<pollfd>::iterator it;
	// for (it = _pollFD.begin(); it != _pollFD.end(); it++)
	// 	if (it->fd == fd)
	// 		it = _pollFD.erase(it);
}

bool server::LastPing(user &client){
	clock_t actual = clock();
	//std::cout << "client [" << client.getfd() << "] | " << actual - client.getLastPing() << std::endl;
	if (actual - client.getLastPing() > _maxtimeout)
		return TIMEOUT;
	return TIMEIN;
}

void server::sendMsg(user &client, server &server, std::string RPL){
	std::string msg;
	(void)server;
	msg = "\e[0m:\e[0;33m" + getID()
		+ "\e[0m \e[0;32m" + RPL
		+ "\e[0m \e[0;34m" + client.getNickname()
		+ "\e[0m :" + displayRPL(server, client, RPL, "", "")
		+ "\r\n";
	if (send(client.getfd(), msg.c_str(), msg.length(), 0) == -1)
		std::perror("send:");
	std::cout 	<< "---- SERVER RESPONSE ----\n"
				<< msg << "\n"
				<< "-------------------------" << std::endl;
}

void server::sendrawMsg(user &client, server &server, std::string message){
	std::string msg;
	(void)server;
	msg = ":" + getID() + " " + client.getNickname() + " : " + message + "\r\n";
	if (send(client.getfd(), msg.c_str(), msg.length(), 0) == -1)
		std::perror("send:");
	std::cout 	<< "---- SERVER RESPONSE ----\n"
				<< msg << "\n"
				<< "-------------------------" << std::endl;
}
		
void server::sendMsgToChannel(user &client, server &server, std::string RPL, std::string message, std::string canal) {
    std::ostringstream oss;
	for (std::map<std::string, channel>::iterator it = _channelMap.begin(); it != _channelMap.end(); ++it){
		if (canal == it->first){	
			std::vector<user> userlist = it->second.getChannelUser();
			for (std::vector<user>::iterator it = userlist.begin(); it != userlist.end(); ++it) {
				if (it->getfd() == client.getfd())
					continue;
				oss.clear();
				oss << client.getfd();
				std::string msg = "\e[0m:\e[0;35m"
								+ client.getNickname() + "\e[0m!\e[0;35m"
								+ oss.str() + "\e[0m@\e[0;33m"
								+ server.getID() + "\e[0m \e[0;32m"
								+ RPL + "\e[0m \e[0;34m"
								+ canal + "\e[0m | \e[0;34m"
								+ it->getNickname() + "\e[0m :"
								+ displayRPL(server, client, RPL, message, canal) + "\r\n";
				if (send(it->getfd(), msg.c_str(), msg.length(), 0) == -1)
					std::perror("send:");
				std::cout  << "---- SERVER RESPONSE ----\n"
							<< msg << "\n"
							<< "-------------------------" << std::endl;
				return;
			}
		}
    }
	return sendMsg(client, server, "403");
}

void server::sendMsgToUser(user &client, user &dest, server &server, std::string RPL, std::string message) {
   	std::ostringstream oss;
    oss << client.getfd();
    std::string msg = "\e[0m:\e[0;35m"
                    + client.getNickname() + "\e[0m!\e[0;35m"
                    + oss.str() + "\e[0m@\e[0;33m"
                    + server.getID() + "\e[0m \e[0;32m"
                    + RPL + "\e[0m \e[0;34m"
                    + dest.getNickname() + "\e[0m :"
                    + displayRPL(server, client, RPL, message, "") + "\r\n";
    if (send(dest.getfd(), msg.c_str(), msg.length(), 0) == -1)
        std::perror("send:");
    std::cout   << "---- SERVER RESPONSE ----\n"
                << msg << "\n"
                << "-------------------------" << std::endl;
}

void server::sendMsgFromBot(bot &bot, user &dest, server &server, std::string message) {
	std::string msg = "\e[0m:\e[0;35m"
                    + bot.getName() + "\e[0m!\e[0;35m"
                    + "BOT\e[0m@\e[0;33m"
                    + server.getID() + "\e[0m \e[0;32m"
                    + "PRIVMSG \e[0m \e[0;34m"
                    + dest.getNickname() + "\e[0m :"
                    + displayRPL(server, dest, "HI_BOT", message, "") + "\r\n";
    if (send(dest.getfd(), msg.c_str(), msg.length(), 0) == -1)
        std::perror("send:");
    std::cout   << "---- SERVER RESPONSE ----\n"
                << msg << "\n"
                << "-------------------------" << std::endl;
}

void server::sendMsg2(server &Server, user &Client, std::string str){
	(void)Server;
	std::string msg;
	msg = str;
	//msg = ":" + getID() + " " + Client.getNickname() + " : "  + str + "\r\n";
	if (send(Client.getfd(), msg.c_str(), msg.length(), 0) == -1)
		std::perror("send:");
	std::cout 	<< "---- SERVER RESPONSE ----\n"
				<< msg << "\n"
				<< "-------------------------" << std::endl;
}


void	server::sendJoinMsg(server& Server, user& Client, std::string channelName){

    std::string msg = ":" + Server.getID() + " 332 " + Client.getNickname() + " " + channelName + " :Bienvenue dans le nouveau canal!\r\n";

    if (send(Client.getfd(), msg.c_str(), msg.length(), 0) == -1) {
        std::perror("send:");
    }

    std::cout << "---- SERVER RESPONSE ----\n" << msg << "\n-------------------------" << std::endl;
	return;
}
