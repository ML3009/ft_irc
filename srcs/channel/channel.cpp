/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purple <purple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 16:14:16 by mvautrot          #+#    #+#             */
/*   Updated: 2024/01/11 17:23:02 by purple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "channel.hpp"

/*----------------- Coplien ------------- */

channel::channel(){
	_channelName = "";
	_limit = 0;
}

channel::channel(std::string channelName) {
	_channelName = channelName;
	_limit = 0;
}

channel::channel(const channel& rhs){
	*this = rhs;
}

channel& channel::operator=(const channel& rhs){
	if(this != &rhs){
		_channelName = rhs._channelName;
		_channelUser = rhs._channelUser;
		_channelOperator = rhs._channelOperator;
		_mode = rhs._mode;
		_keyword = rhs._keyword;
		_limit = rhs._limit;
		_invitedUser = rhs._invitedUser;
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
std::vector<std::string> &channel::getInviteList(){return _invitedUser;}
long	channel::getLimit(){ return _limit;}

void	channel::setOperator(std::string channelOperator) {
	_channelOperator.push_back(channelOperator);
	return;
}

void	channel::unsetOperator(std::string& channelOperator) {
	_channelOperator.erase(std::remove(_channelOperator.begin(), _channelOperator.end(), channelOperator),
		 _channelOperator.end());
	return;
}


void	channel::setMode(std::string mode) {

	if (mode.find_first_not_of("itkol") != std::string::npos)
		return;
	for (int i = 0; mode[i]; ++i)
		_mode.insert(mode[i]);
	for (std::set<char>::iterator it = _mode.begin(); it != _mode.end(); it++)
		std::cout << *it << std::endl;
	return;
}


bool	channel::isValidMode(server &Server, user &Client, std::vector<std::string>& argument, std::string mode) {

	int i = 0;
	(void)argument;
	if (mode.find_first_not_of("itkol") != std::string::npos)
		return Server.sendMsg(Client, Server, "472", "", ""), false;
	for (std::set<char>::iterator it = _mode.begin(); it != _mode.end(); it++, ++i)
		if (*it == mode[i])
			return std::cout << "Error : Is already set" << std::endl, false;
	return true;
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

void	channel::unsetChannelUser(user& Client){

	_channelUser.erase(std::remove(_channelUser.begin(), _channelUser.end(), Client),
		 _channelUser.end());
	return;
}

void	channel::setKeyword(std::string keyword) {

	_keyword = keyword;
	return;
}

void	channel::unsetKeyword() {
	_keyword = "";
	return;
}

bool	channel::isValidLimit(std::string limit) {
	
	if (limit.find_first_not_of("0123456789") != std::string::npos)
		return false;
	if (limit.size() > 10)
		return false;
	const char* limit_tmp = limit.c_str();
	char *endPtr;
	unsigned long result = strtoul(limit_tmp, &endPtr, 10);
	if (*endPtr != '\0')
		return false;
	if ((int)result > std::numeric_limits<int>::max())
		return false;
	if (result == 0)
		return false;
	return true;
}

void	channel::setLimit(std::string limit) {

	const char* limit_tmp = limit.c_str();
	_limit = strtol(limit_tmp, NULL, 10);
	std::cout << _limit << std::endl;
}

void	channel::unsetLimit() {
	_limit = 0;
}


/*--------------- Function -------------- */
bool	channel::isInvited(std::string name){
	for (std::vector<std::string>::iterator it = _invitedUser.begin(); it!= _invitedUser.end(); ++it)
		if (*it == name)
			return true;
	return false;
}

bool	channel::isOperator(std::string usernameClient){
	for (std::vector<std::string>::iterator it = _channelOperator.begin(); it!= _channelOperator.end(); ++it)
		if (*it == usernameClient)
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
			if (canal.isOperator(client.getUsername()))
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
	std::string message = std::string("[");
	for (std::set<char>::iterator it = _mode.begin(); it!= _mode.end(); ++it)
		message += *it;
	message += std::string( "] ");
	return message;
}

bool	channel::isAlreadyinChannel(user &Client) {
	std::cout << "SEARCHING FOR " << Client.getUsername() << std::endl;
	for (std::vector<user>::iterator it = _channelUser.begin(); it != _channelUser.end(); ++it) {
		if (it->getUsername() == Client.getUsername())
		{
			std::cout << "IN" << std::endl;
			return true;
		}
	}
	std::cout << "IN" << std::endl;
	return false;
}

bool	channel::isFull(server &Server, user &Client) {

	(void)Server;
	(void)Client;
	int	nbClient = 0;
	for (std::vector<user>::iterator it = _channelUser.begin(); it != _channelUser.end(); ++it, ++nbClient);
	if (nbClient >= _limit && _limit != 0)
		return true;
	std::cout << "nbClient: " << nbClient << "_limit: " << _limit << std::endl;
	return false;
}

bool	channel::isValidPass(std::vector<std::string> key_tmp, int pos) {

	if (key_tmp.empty() || key_tmp.size() < (unsigned long)pos)
		return false;
	if (_keyword == key_tmp[pos])
		return true;
	return false;
}


