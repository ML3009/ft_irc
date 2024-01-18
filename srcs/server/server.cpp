/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purple <purple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 11:21:50 by purple            #+#    #+#             */
/*   Updated: 2024/01/18 14:05:36 by purple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

/*----------------- Coplien ------------- */

server::server(){
	_port = 6667;
	_password = "password";
	_userCount = 0;
	_upTime = clock();
	_ID = "127.0.0.1";
	_maxtimeout = 2000000;

	display_constructor(SERVER_DC);
}


server::server(int port, std::string password){
	_ID = "127.0.0.1";
	_port = port;
	_password = password;
	_userCount = 0;
	_upTime = time(NULL);
	_maxtimeout = 15;
	_botToken = "hvsqhzjhbrpojnwdf5454";
	_botCount = 0;

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
int server::getBotCount() const {return _botCount;}
void server::setBotOn(){_botCount++;}
std::vector<pollfd> server::getpollfd() { return _pollFD;}
std::string server::getPassword() const{return _password;}
std::string server::getID() const{return _ID;}
std::string server::getToken() const{return _botToken;}
std::map<int, user> &server::getUserMap(){return _clientMap;}
std::map<std::string, channel>& server::getChannelMap(){return _channelMap;}
user &server::getClient(std::string name){
	for (std::map<int, user>::iterator it = _clientMap.begin(); it != _clientMap.end(); it++)
		if (it->second.getUsername() == name)
			return it->second;
	return _clientMap.begin()->second;
}

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
	if ((poll(&_pollFD[0], _pollFD.size(), 10000) == -1))
	{
		if (handleSignal == false){
			std::perror("poll");
			throw pollException();
		}
	}
	(_pollFD[0].revents == POLLIN) ? getNewClient() : getClientMessage();
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
		std::ostringstream oss;
    	oss << _clientMap[it->fd].getfd();
		std::cout << "[" + oss.str() + std::string("] ") + _clientMap[it->fd].getUsername() << std::endl;
		if (it->revents == POLLIN)
		{
			char buffer[512];
			int bytes = recv(_clientMap[it->fd].getfd(), buffer, 512, 0);
			if (bytes <= 0)
			{
				memset(buffer, 0, 512);
				disconnect_client(_clientMap[it->fd]);
				return;
			}
			else{

				buffer[bytes] = '\0';
				_clientMap[it->fd].appendToBuffer(buffer);
				_clientMap[it->fd].receive(*this);
				memset(buffer, 0, 512);
				if (_clientMap[it->fd].getStatus() == DISCONNECTED){
					disconnect_client(_clientMap[it->fd]);
					return;
				}
			}
		}
	}
	debug("getClientMessage", END);
}


void server::disconnect_client(user &client){
	std::vector<pollfd>::iterator it = std::find_if(_pollFD.begin(), _pollFD.end(), IsClientFDPredicate(client.getfd()));
	if (it != _pollFD.end()) {_pollFD.erase(it);}
	close(client.getfd());
	std::map<int, user>::iterator ita = _clientMap.find(client.getfd());
		if (ita != _clientMap.end()){_clientMap.erase(ita);}

	_userCount--;
	if (_userCount == 0)
		_clientMap.clear();
}

bool server::userExist(std::string name){
	for (std::map<int, user>::iterator it = _clientMap.begin(); it != _clientMap.end(); ++it)
	{
		if (it->second.getUsername() == name)
			return true;
	}
	return false;
}

bool server::channelExist(std::string channelName){

	if (!_channelMap.empty()) {
		for (std::map<std::string, channel>::iterator it = _channelMap.begin(); it != _channelMap.end(); ++it){
			if (it->second.getChannelName() == channelName)
				return true;
		}
	}
	return false;
}

void server::closeServerSocket() {close(_pollFD[0].fd);}

void server::timeout_client(user &client){
	sendMsg(client, *this, "QUIT", "You have been disconnected by the server for being AFK", "");
	std::vector<std::map<std::string, channel>::iterator> channelsToRemove;
	if (!getChannelMap().empty()) {
		for (std::map<std::string, channel>::iterator it = getChannelMap().begin(); it != getChannelMap().end(); ++it){
			if (it->second.isAlreadyinChannel(client) == true) {
				it->second.unsetChannelUser(client);
				sendMsg(client, *this, "LEAVE", "You have left the channel " + it->second.getChannelName(), "");
				sendMsgToChannel(client, *this, "LEAVE", client.getNickname() + " has left the channel. Goodbye!", it->second.getChannelName());

				if (it->second.getChannelUser().empty()) {
						channelsToRemove.push_back(it);
				}
			}
		}
	}
	for (std::vector<std::map<std::string, channel>::iterator>::iterator it = channelsToRemove.begin(); it != channelsToRemove.end(); ++it) {
    	getChannelMap().erase(*it);
	}
	sendMsg(client, *this, "QUIT", "Leaving the server. Goodbye!", "");
	disconnect_client(client);
}

bool server::LastPing(user &client){
	time_t actual = time(NULL);
	if (actual - client.getLastPing() > _maxtimeout)
		return TIMEOUT;
	return TIMEIN;
}

void server::sendMsg(user &client, server &server, std::string message) {
	std::string msg;
	msg =  ":" + client.getNickname() + " " + message + "\r\n";;
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

void server::sendMsgToChannel(server &server, user &client, std::string message, std::string canal) {
    std::ostringstream oss;
	for (std::map<std::string, channel>::iterator it = _channelMap.begin(); it != _channelMap.end(); ++it){
		if (canal == it->first){
			std::vector<user> userlist = it->second.getChannelUser();
			for (std::vector<user>::iterator it = userlist.begin(); it != userlist.end(); ++it){
				if (it->getfd() == client.getfd())
				{
					for (std::vector<user>::iterator it = userlist.begin(); it != userlist.end(); ++it) {
						if (it->getfd() == client.getfd())
							continue;
						std::string msg =	":" + client.getNickname()
											+ "!" + client.getNickname()
											+ "@" + server.getID()
											+ " PRIVMSG " + canal
											+ " :" + message + "\r\n";
						if (send(it->getfd(), msg.c_str(), msg.length(), 0) == -1)
							std::perror("send:");
						std::cout  << "---- SERVER RESPONSE ----\n"
									<< msg << "\n"
									<< "-------------------------" << std::endl;
					}
					return;
				}
			}
			//return sendMsg(client, server, "441", "", canal);
		}
    }
	//return sendMsg(client, server, "403", "", canal);
}

void server::sendMsgToUser(server &server, user &client, user &dest, std::string message) {
	std::string msg =	":" + client.getNickname()
						+ "!" + client.getNickname()
						+ "@" + server.getID()
						+ " PRIVMSG " + dest.getNickname()
						+ " :" + message + "\r\n";
    if (send(dest.getfd(), msg.c_str(), msg.length(), 0) == -1)
        std::perror("send:");
    std::cout   << "---- SERVER RESPONSE ----\n"
                << msg << "\n"
                << "-------------------------" << std::endl;
}
