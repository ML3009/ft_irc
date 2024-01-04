/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvautrot <mvautrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 17:32:31 by purple            #+#    #+#             */
/*   Updated: 2024/01/04 13:29:11 by mvautrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "user.hpp"



/*----------------- Coplien ------------- */

user::user(){

}
user::user(int fd){
	_fd = fd;
	_username = "";
	_nickname = "";
	_buffer = "";
	_password = "";
	_hostname = "127.0.0.1";
	display_constructor(USER_DC);
}
user::user(const user& rhs){

    *this = rhs;
	display_constructor(USER_DC);

}

user&	user::operator=(const user& rhs){

	if (this != &rhs) {
		_fd = rhs._fd;
		_username = rhs._username;
		_nickname = rhs._nickname;
		_buffer = rhs._buffer;
		_password = rhs._password;
		_hostname = rhs._hostname;
	}
	display_constructor(USER_AO);
	return *this;
}

user::~user(){
	display_constructor(SERVER_DD);

}


/*---------------- Operator ------------- */

/*---------- Getter / Setter ------------ */
int 		user::getfd() const {return _fd;}
std::string user::getUsername() const{return _username;}
std::string user::getBuffer() const{return _buffer;}
std::string user::getPassword() const{return _password;}
std::string user::getNickname() const{return _nickname;}
/*--------------- Function -------------- */

void user::parseClientMessage(server Server, const std::string &buffer){
	debug("parseClientMessage", BEGIN);
	(void) Server;
	addData(buffer);
	if (completeCommand(_buffer, 1) == COMPLETE)
	{
		std::vector<std::string> argument = splitArgs(_buffer);
		_buffer.clear();
		commands cmd;
		isAuthentified() == true ? cmd.getCommand(Server, *this, argument) : cmd.getAuthentified(Server, *this, argument);
		argument.clear();
		if (!argument.empty())
			std::cout << "NOT EMPTY" << std::endl;
	}
	else
		std::cout << "\n[Recieving a non-complete message, saving in buffer]\x1b[0m" << std::endl;
	debug("parseClientMessage", END);
	return;
}

bool	user::isAuthentified(void) {
	debug("isAuthentified", BEGIN);
	if (_password.empty() || _username.empty() || _nickname.empty())
		return false;
	return true;
}

void user::addData(const std::string &buffer){
	debug("addData", BEGIN);
	if (completeCommand(buffer, 0) == COMPLETE)
		_buffer += buffer;
	else
	{
		size_t i = -1;
		while (++i < buffer.length() && (buffer[i] != '\r' && buffer[i] != '\n'&& buffer[i] != '\0'))
			_buffer += buffer[i];
	}
	debug("addData", END);
	return;
}

/*--------------- Exception ------------- */
