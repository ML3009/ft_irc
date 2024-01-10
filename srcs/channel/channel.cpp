/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purple <purple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 16:14:16 by mvautrot          #+#    #+#             */
/*   Updated: 2024/01/10 14:18:40 by purple           ###   ########.fr       */
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
		//for (std::vector<user>::const_iterator it = rhs._channelUser.begin(); it != rhs._channelUser.end(); ++it)
		_channelUser = rhs._channelUser;
		//for (std::vector<std::string>::const_iterator it = rhs._channelOperator.begin(); it != rhs._channelOperator.end(); ++it)
		_channelOperator = rhs._channelOperator;
		//for (std::set<char>::iterator it = rhs._mode.begin(); it != rhs._mode.end(); it++)
		_mode = rhs._mode;
		_keyword = rhs._keyword;
	}
	return *this;
}

channel::~channel(){}


/*---------------- Operator ------------- */


/*---------- Getter / Setter ------------ */

std::string channel::getChannelName() const {return _channelName;}
std::string& channel::getKeyword() {return _keyword;}
std::vector<user> &channel::getChannelUser() { return _channelUser;}
std::vector<std::string> channel::getChannelOperators() const {	return _channelOperator;}
std::set<char> &channel::getMode() {return _mode;}

void	channel::setOperator(std::string channelOperator) {
	_channelOperator.push_back(channelOperator);
	return;
}


void	channel::setMode(std::string mode) {

	if (mode.find_first_not_of("itkol") != std::string::npos)
		return std::cout << "Unknow mod" << std::endl, void();
	for (int i = 0; mode[i]; ++i)
		_mode.insert(mode[i]);
	for (std::set<char>::iterator it = _mode.begin(); it != _mode.end(); it++)
		std::cout << *it << std::endl;
	return;
}


void	channel::unsetMode(std::string mode) {

	if (mode.find_first_not_of("itkol") != std::string::npos)
		return std::cout << "Unknow mod" << std::endl, void();
	for (int i = 0; mode[i]; ++i)
		_mode.erase(mode[i]);
	return;
}

void	channel::setChannelUser(user& Client) {
	_channelUser.push_back(Client);
	return;

}

void	channel::setKeyword(std::string keyword) {

	_keyword = keyword;
	return;
}


// bool	channel::isKeyWordUse(user &Client) {
// 	for (std::vector<user>::iterator it = _channelUser.begin(); it != _channelUser.end(); ++it) {
// 		if (it->getUsername() == Client.getUsername())
// 			return true;
// 	}
// 	return false;
// }
/*--------------- Function -------------- */

bool	channel::isOperator(user &Client){
	for (std::vector<std::string>::iterator it = _channelOperator.begin(); it!= _channelOperator.end(); ++it)
		if (*it == Client.getUsername())
			return true;
	return false;
}

std::string printOP(std::string user, channel &channel){
	std::vector<std::string> userlist = channel.getChannelOperators();
	for (std::vector<std::string>::iterator it = userlist.begin(); it != userlist.end(); ++it){
		if (*it == user)
			return "[*]";
	}
	return "";
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


/* MODE */

bool	channel::search_mode(char mode){

	for (std::set<char>::iterator it = _mode.begin(); it!= _mode.end(); ++it)
		if (mode == *it)
			return true;
	return false;
}

std::string	channel::display_mode(){
	std::string message;
	for (std::set<char>::iterator it = _mode.begin(); it!= _mode.end(); ++it)
		message += std::string("[") + *it + std::string( "] ");
	return message;
}

bool	channel::isAlreadyinChannel(user &Client) {
	for (std::vector<user>::iterator it = _channelUser.begin(); it != _channelUser.end(); ++it) {
		if (it->getUsername() == Client.getUsername())
			return true;
	}
	return false;
}

bool	channel::isFull(server &Server, user &Client) {

	(void)Server;
	(void)Client;
	std::cout << "IS FULL" << std::endl;
	return true;
}

bool	channel::isInvited(server &Server, user &Client) {

	(void)Server;
	(void)Client;
	std::cout << "IS INVITED" << std::endl;
	return true;
}

bool	channel::isValidPass(server &Server, user &Client, std::vector<std::string> key_tmp, int pos) {

	(void)Server;
	(void)Client;
	if (key_tmp.empty() || key_tmp.size() < (unsigned long)pos)
		return false;
	if (_keyword == key_tmp[pos])
		return true;
	return false;
}




//


/*--------------- operator ------------- */

