/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purple <purple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 16:14:16 by mvautrot          #+#    #+#             */
/*   Updated: 2024/01/10 12:08:30 by purple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "channel.hpp"

/*----------------- Coplien ------------- */

channel::channel(){
	_channelName = "";
	//_channelUser = "";
	//_channelOperator = "";
}

channel::channel(std::string channelName) {
	_channelName = channelName;
	//_channelUser = "";
	//_channelOperator = "";
}

channel::channel(const channel& rhs){
	*this = rhs;
}

channel& channel::operator=(const channel& rhs){
	if(this != &rhs){
		_channelName = rhs._channelName;
		for (std::vector<user>::const_iterator it = rhs._channelUser.begin(); it != rhs._channelUser.end(); ++it)
			_channelUser = rhs._channelUser;
		for (std::vector<std::string>::const_iterator it = rhs._channelOperator.begin(); it != rhs._channelOperator.end(); ++it)
			_channelOperator = rhs._channelOperator;
	}
	return *this;
}

channel::~channel(){}


/*---------------- Operator ------------- */


/*---------- Getter / Setter ------------ */

std::string channel::getChannelName() const {return _channelName;}
std::vector<user> &channel::getChannelUser() { return _channelUser;}
std::vector<std::string> channel::getChannelOperators() const {	return _channelOperator;}

void	channel::setOperator(std::string channelOperator) {
	_channelOperator.push_back(channelOperator);
	return;
}

void	channel::setChannelUser(user& Client) {
	_channelUser.push_back(Client);
	return;

}

bool	channel::isAlreadyinChannel(user &Client) {
	std::cout << Client.getUsername();
	for (std::vector<user>::iterator it = _channelUser.begin(); it != _channelUser.end(); ++it) {
		if (it->getUsername() == Client.getUsername())
			return true;
	}
	return false;
}
/*--------------- Function -------------- */

bool	channel::isOperator(user &Client){
	for (std::vector<std::string>::iterator it = _channelOperator.begin(); it!= _channelOperator.end(); ++it)
		if (*it == Client.getUsername())
			return true;
	return false;
}

int		channel::getTopicStatus(channel &canal, user &client, server &server){
	(void)server;
	std::vector<user> userlist = canal.getChannelUser();
	for (std::vector<user>::iterator it = userlist.begin(); it != userlist.end(); ++it){
		if (it->getfd() == client.getfd()){
			// if need op
			if (canal.isOperator(client))
				return TOPIC_NEED_OP;
			else
				return TOPIC_NEED_NOOP;
		}
	}
	return TOPIC_NOUSER;
}

void	channel::display_operators(std::vector<std::string> channelOperator){

	std::cout << "DISPLAY OPERATORS" << std::endl;
	std::cout << channelOperator.size() << std::endl;
	for (std::vector<std::string>::iterator it = channelOperator.begin(); it!= channelOperator.end(); ++it)
		std::cout << *it << std::endl;
	return;
}

void	channel::display_users(std::vector<user> channelUser){

	for (std::vector<user>::iterator it = channelUser.begin(); it!= channelUser.end(); ++it)
		std::cout << it->getUsername() << std::endl;
	return;
}


//


/*--------------- operator ------------- */

