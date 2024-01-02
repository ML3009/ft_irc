/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purple <medpurple@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 11:21:50 by purple            #+#    #+#             */
/*   Updated: 2023/12/31 15:59:18 by purple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

/*----------------- Coplien ------------- */

server::server(){
	_port = 6667;
	_password = "password";
	_userCount = 0;

	display_constructor(SERVER_DC);
}


server::server(int port, std::string password){
	_port = port;
	_password = password;

	display_constructor(SERVER_PC);

}

server::server(const server& rhs){
	
	*this = rhs; 
	display_constructor(SERVER_CC);

}

server&	server::operator=(const server& rhs){

	if (this != &rhs)
		*this = rhs;
	display_constructor(SERVER_AO);
	return *this;
}

server::~server(){
	display_constructor(SERVER_DD);

}


/*---------------- Operator ------------- */



/*---------- Getter / Setter ------------ */

std::map<int, user> server::getClientMap() const {return _client;}

int server::getUserCount() const { return _userCount;}

user server::getUser(int fd) const {
    debug("getUser", BEGIN);
    
    std::map<int, user> map = this->getClientMap();
    std::map<int, user>::const_iterator it;
    for (it = map.begin(); it != map.end(); it++) {
        if (it->first == fd) {
            debug("getUser", END);
            return it->second;
        }
    }
    debug("getUser", END);
    return NULL;
}
/*--------------- Function -------------- */



void server::init_server(){
	
	debug("init_server", BEGIN);
	int opt = 1;
	int	serverSocket;
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
	_client[fd] = User;
	_pollFD.push_back(pollfd());
	_pollFD.back().fd = fd;
	_pollFD.back().events = POLLIN;
	_userCount++;
	debug("getNewClient", END);
}

void server::getClientMessage(){
	debug("getClientMessage", BEGIN);

	std::vector<pollfd>::const_iterator it;
	for (it = _pollFD.begin(); it != _pollFD.end(); it++)
	{
		if (it->revents == POLLIN)
		{
			user user = getUser(it->fd);
			//(user == NULL) ? void() : (std::perror("user"), throw userException());
			char buffer[1024];
			std::cout << "User : " << user.getUsername() << " base fd : " << it->fd << " user fd : " << user.getfd()<< std::endl;
			if (recv(user.getfd(), buffer, 1024, 0) <= 0)
			{
				std::cout << "DISCONNECTED" << std::endl;
				exit(0);	
			}
			else{
				std::string buff (buffer);
				buff[buff.length()] = '\0';
				user.parseClientMessage(buff);
			}
		}
	}
	debug("getClientMessage", END);	
}

