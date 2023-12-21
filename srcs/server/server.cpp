/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purple <purple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 11:21:50 by purple            #+#    #+#             */
/*   Updated: 2023/12/21 15:57:00 by purple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

/*----------------- Coplien ------------- */

server::server(){
	_port = 6667;
	_password = "password";

	msg_const ? _display_constructor(SERVER_DC) : void ();
}


server::server(int port, std::string password){
	_port = port;
	_password = password;

	msg_const ? _display_constructor(SERVER_PC) : void ();

}

server::server(const server& rhs){
	
	*this = rhs; 
	msg_const ? _display_constructor(SERVER_CC) : void ();

}

server&	server::operator=(const server& rhs){

	if (this != &rhs)
		*this = rhs;
	msg_const ? _display_constructor(SERVER_AO) : void ();
	return *this;
}

server::~server(){
	msg_const ? _display_constructor(SERVER_DD) : void ();

}


/*---------------- Operator ------------- */



/*---------- Getter / Setter ------------ */


/*--------------- Function -------------- */

void server::_display_constructor(std::string msg){
    std::cout << "\x1b[33m \x1b[3m" << msg << "\x1b[0m" << std::endl;
}

void server::init_server(){
	
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
	!(setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) == -1) ? void() : (std::perror("socket option"), throw socketoptException());

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
	return;
}

void server::run_server(){
	
}
/*--------------- Exception ------------- */


// faire un .github a la racine et 