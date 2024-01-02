/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purple <purple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 17:32:31 by purple            #+#    #+#             */
/*   Updated: 2024/01/02 14:51:40 by purple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "user.hpp"




/*----------------- Coplien ------------- */

user::user(){
	

}
user::user(int fd){
	_fd = fd;
	_username = "default";
	_nickname = "default";
	_realname = "default";
	_buffer = "";
	_password = "default";
	_hostname = "127.0.0.1";
	display_constructor(USER_DC);
}
user::user(const user& rhs){
    
    *this = rhs; 
	display_constructor(USER_DC);

}

user&	user::operator=(const user& rhs){

	if (this != &rhs) {
		_username = rhs._username;
		_nickname = rhs._nickname;
		_realname = rhs._realname;
		_buffer = rhs._buffer;
		_password = rhs._password;
		_hostname = rhs._hostname;
		_fd = rhs._fd;
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
/*--------------- Function -------------- */

void user::parseClientMessage(std::string buffer){
	debug("parseClientMessage", BEGIN);
	// std::cout << "Client fd : " << this->getfd()  << std::endl ;
	_buffer.append(buffer);
	buffer.clear();
	// debug("Parse",5);

	// std::cout << "buffer size " << (_buffer.length()) << " for [" << _buffer << "]"  <<std::endl ;
	// for (int i = 0; i < (int)(_buffer.length()); i++) {
    //     char currentChar = _buffer[i];
        
    //     if (currentChar == '\n') {
    //         std::cout << "\\n" << " position : " << i  ;
    //     } else if (currentChar == '\r') {
    //         std::cout << "\\r"<< " position : " << i;
    //     } else if (currentChar == '\t') {
    //         std::cout << "\\t"<< " position : " << i;
    //     } else {
    //         std::cout << currentChar;
    //     }
    // }

	if (completeCommand(_buffer) == COMPLETE)
	{
		std::vector<std::string> argumuent = splitArgs(_buffer);
		_buffer.clear();
		std::vector<std::string>::const_iterator it;
		for (it = argumuent.begin(); it != argumuent.end(); it++)
			std::cout << *it << std::endl;

	}
	else
		std::cout << "\nRecieving a non-complete message, saving in buffer" << std::endl;
	debug("parseClientMessage", END);
}


/*--------------- Exception ------------- */
