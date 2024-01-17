/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purple <purple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 17:32:31 by purple            #+#    #+#             */
/*   Updated: 2024/01/17 14:59:50 by purple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "user.hpp"



/*----------------- Coplien ------------- */

user::user(){}
user::user(int fd){
	_fd = fd;
	_username = "";
	_nickname = "";
	_realname = "";
	_buffer = "";
	_password = "";
	_hostname = "127.0.0.1";
	_last_ping = time(NULL);
	_status = CONNECTED;
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
		_realname = rhs._realname;
		_nickname = rhs._nickname;
		_buffer = rhs._buffer;
		_password = rhs._password;
		_hostname = rhs._hostname;
		_last_ping = rhs._last_ping;
		_status = rhs._status;
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
std::string user::getRealname() const{return _realname;}
std::string user::getBuffer() const{return _buffer;}
std::string user::getPassword() const{return _password;}
std::string user::getNickname() const{return _nickname;}
time_t		user::getLastPing() const{return _last_ping;}
bool		user::getStatus() const{return _status;}


void	user::setStatus(bool status) {
	_status = status;
	return;
}

void	user::setPassword(std::string password) {
	_password = password;
	return;
}

void	user::setNickname(std::string nickname) {
	_nickname = nickname;
	return;
}

void	user::setUsername(std::string username) {
	_username = username;
	return;
}


void	user::setRealname(std::string realname) {
	_realname = realname;
	return;
}


/*--------------- Function -------------- */
void user::clearBuffer() {_buffer.clear();}

void user::parseClientMessage(server &Server, std::string comd){
	debug("parseClientMessage", BEGIN);
	std::cout << "done" << std::endl;
	std::vector<std::string> argument = splitArgs(comd);
	commands cmd;
	isAuthentified() == true ? cmd.getCommand(Server, *this, argument) : cmd.getAuthentified(Server, *this, argument);
	argument.clear();
	debug("parseClientMessage", END);
	return;
}

bool	user::isAuthentified(void) {
	debug("isAuthentified", BEGIN);
	if (_password.empty() || _username.empty() || _nickname.empty())
		return false;
	return true;
}

void user::appendToBuffer(const char *buffer){
	debug("addData", BEGIN);
	_buffer += buffer;
	debug("addData", END);
	return;
}

void user::receive(server &server){
	std::cout << "TEST" << std::endl;

	if (_buffer.find("\n") == std::string::npos)
		return;
	std::cout << "TEST1" << std::endl;
	size_t pos = _buffer.find("\r\n");
	if (pos == std::string::npos)
		pos = _buffer.find("\n");
	std::cout << "TEST2" << std::endl;
	while (pos != std::string::npos){
		std::string	line = _buffer.substr(0, pos);
		if (line.size())
			parseClientMessage(server, line);
		_buffer.erase(0, _buffer.find("\n") + 1);
		pos = _buffer.find("\r\n");
		if (pos == std::string::npos)
			pos = _buffer.find("\n");
	}
	
}
/*--------------- Exception ------------- */
