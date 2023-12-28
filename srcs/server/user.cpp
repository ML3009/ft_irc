/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purple <purple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 17:32:31 by purple            #+#    #+#             */
/*   Updated: 2023/12/28 16:24:50 by purple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "user.hpp"




/*----------------- Coplien ------------- */

user::user(){
	_username = "default";
	_nickname = "default";
	_realname = "default";
	_buffer = "";
	_password = "default";
	_hostname = "127.0.0.1";
	CONSTRUCTOR ? _display_constructor(USER_DC) : void ();

}

user::user(const user& rhs){
    
    *this = rhs; 
	CONSTRUCTOR ? _display_constructor(USER_DC) : void ();

}

user&	user::operator=(const user& rhs){

	if (this != &rhs) {
		_username = rhs._username;
		_nickname = rhs._nickname;
		_realname = rhs._realname;
		_buffer = rhs._buffer;
		_password = rhs._password;
		_hostname = rhs._hostname;
	}
	CONSTRUCTOR ? _display_constructor(USER_AO) : void ();
	return *this;
}

user::~user(){
	CONSTRUCTOR ? _display_constructor(SERVER_DD) : void ();

}


/*---------------- Operator ------------- */

/*---------- Getter / Setter ------------ */


/*--------------- Function -------------- */

void user::_display_constructor(std::string msg){
    std::cout << "\x1b[33m \x1b[3m" << msg << "\x1b[0m" << std::endl;
}


user *user::getUser(int fd, server &server){
	debug("getUser", BEGIN);
	std::map<int, user>::const_iterator it;
	for (it = server.getClient().begin(); it != server.getClient().end(); it++)
		if (it->first == fd)
			return 	debug("getUser", END), const_cast<user*>(&(it->second));
	debug("getUser", END);
	return NULL;
}
/*--------------- Exception ------------- */
