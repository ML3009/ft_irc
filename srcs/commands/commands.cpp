/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purple <medpurple@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 16:14:47 by mvautrot          #+#    #+#             */
/*   Updated: 2024/01/05 23:12:25 by purple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.hpp"

/*----------------- Coplien ------------- */

commands::commands(){

	cmdMap["/INVITE"] = &commands::functionINVITE;
	cmdMap["/JOIN"] = &commands::functionJOIN;
	cmdMap["/KICK"] = &commands::functionKICK;
	cmdMap["/MODE"] = &commands::functionMODE;
	cmdMap["/NICK"] = &commands::functionNICK;
	cmdMap["/PART"] = &commands::functionPART;
	cmdMap["/PASS"] = &commands::functionPASS;
	cmdMap["/PRIVMSG"] = &commands::functionPRIVMSG;
	cmdMap["/QUIT"] = &commands::functionQUIT;
	cmdMap["/TOPIC"] = &commands::functionTOPIC;
	cmdMap["/USER"] = &commands::functionUSER;
}

commands::commands(const commands& rhs){
	*this = rhs;
	display_constructor(COMMANDS_CC);

}

commands& commands::operator=(const commands& rhs){
	if(this != &rhs) {
		// this->cmdMap.clear();  // Effacer la map actuelle
		for (std::map<std::string, cmdFunctionPointer>::const_iterator it = rhs.cmdMap.begin(); it != rhs.cmdMap.end(); ++it)
			this->cmdMap[it->first] = it->second;
	}
	return *this;
}

commands::~commands(){

}


/*---------------- Operator ------------- */




/*---------- Getter / Setter ------------ */




/*--------------- Function -------------- */


void	commands::getCommand(server& Server, user& Client, std::vector<std::string>& argument) {

	debug("getCommand", BEGIN);
	if (!argument.empty()) {
		for (std::map<std::string, cmdFunctionPointer>::iterator it = cmdMap.begin(); it!= cmdMap.end(); ++it) {
			if (it->first == argument[0])
				(this->*(it->second))(Server, Client, argument);
		}
	}
	debug("getCommand", END);

	return;
}

void	commands::getAuthentified(server& Server, user& Client, std::vector<std::string>& argument) {

	debug("getAuthentified", BEGIN);
	int cmd = isCmdAuthentified(Client, argument[0]);
    if (!argument.empty()) {
		switch (cmd) {
			case PASS:
				getCommand(Server, Client, argument);
				break;
			case NICK:
				getCommand(Server, Client, argument);
				break;
			case USER:
				getCommand(Server, Client, argument);
				break;
			default:
				Server.sendrawMsg(Client, Server, "\e[0;33m[ You are not connected to the server ]\e[0m");
				if (!(Client.getPassword().empty()))
					Server.sendrawMsg(Client, Server, "\e[0;36m\t[Password] OK\e[0m");
				else{
					Server.sendrawMsg(Client, Server, "\e[0;36m\tuse /PASS before doing anything\e[0m");
					break;
				}
				!(Client.getUsername().empty()) ? Server.sendrawMsg(Client, Server, "\e[0;36m \t[Username] " + Client.getUsername())  : Server.sendrawMsg(Client, Server, "\e[0;36m \t[/USER] username must be set \e[0m");
				!(Client.getNickname().empty()) ? Server.sendrawMsg(Client, Server, "\e[0;36m \t[Nickname] " + Client.getNickname())  : Server.sendrawMsg(Client, Server, "\e[0;36m \t[/NICK] nickname must be set \e[0m");
		}
	}
	debug("getAuthentified", END);
	return;
}

int	commands::isCmdAuthentified(user& Client, std::string argument){
	if (!argument.empty()) {
		if (Client.getPassword().empty() && argument == "/PASS")
			return 0;
		else if (!Client.getPassword().empty()){
			if (Client.getNickname().empty() && argument == "/NICK")
				return 1;
			if (!Client.getNickname().empty() && argument == "/USER")
				return 2;
		}
	}
   return -1;
}

void	commands::functionPASS(server& Server, user& Client, std::vector<std::string>& argument){

	int	count = 0;
	for (std::vector<std::string>::iterator it = argument.begin(); it != argument.end(); ++it, ++count){
		std::cout << *it << std::endl;
	}
	if (count != 2) {
		Server.sendMsg(Client, Server, "461");
		return;
	}
	if (argument[1] == Server.getPassword()) {
		if (Client.getPassword().empty())
			Client.setPassword(argument[1]);
		else 
			return 	Server.sendMsg(Client, Server, "462");
	}
	else
		Server.sendMsg(Client, Server, "464");

	return;
}
void	commands::functionNICK(server& Server, user& Client, std::vector<std::string>& argument){

	(void)Server;
	int	count = 0;
	for (std::vector<std::string>::iterator it = argument.begin(); it != argument.end(); ++it, ++count){
		std::cout << *it << std::endl;
	}
	if (count != 2) 
		return Server.sendMsg(Client, Server, "461");
	if (argument[1].find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789[]\\`_^{|}-") != std::string::npos)
		return Server.sendMsg(Client, Server, "432");
	for(std::map<int, user>::iterator it = clientMap.begin(); it != clientMap.end(); ++it) {
		if (argument[1] == it->second.getNickname())
			return Server.sendMsg(Client, Server, "463");
	}
	Client.setNickname(argument[1]);
	//std::cout << Client.getNickname() << std::endl;
	return;
}
void	commands::functionUSER(server& Server, user& Client, std::vector<std::string>& argument){

	(void)Server;
	int	count = 0;
	for (std::vector<std::string>::iterator it = argument.begin(); it != argument.end(); ++it, ++count){
		std::cout << *it << std::endl;
	}
	if (count < 4) {
		return Server.sendMsg(Client, Server, "461");
	}
	if (!Client.getUsername().empty()) {
		return Server.sendMsg(Client, Server, "462");
	}
	if (argument[4][0] == ':')
	{
		std::string tmp;
		for (unsigned long i = 4; i < argument.size(); i++) {
			tmp += argument[i];
			tmp += " ";
		}
		Client.setRealname(tmp);
	} else {
		Client.setRealname(argument[4]);
	}
	Client.setUsername(argument[1]);
	displayWelcome(Server, Client);
	return;
}
void	commands::functionQUIT(server& Server, user& Client, std::vector<std::string>& argument){

	(void)Server;
	(void)Client;
	(void)argument;
	std::cout << "QUIT" << std::endl;

	return;
}
void	commands::functionJOIN(server& Server, user& Client, std::vector<std::string>& argument){

	int	count = 0;
	for (std::vector<std::string>::iterator it = argument.begin(); it != argument.end(); ++it, ++count)
		std::cout << *it << std::endl;
	if (count < 2 || count > 3) 
		return Server.sendMsg(Client, Server, "461");
	if (argument[1][0] != '&' && argument[1][0] != '#') 
		return Server.sendMsg(Client, Server, "476");
	if (argument[1].find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789[]\\`_^{|}-#&") != std::string::npos) 
		return Server.sendMsg(Client, Server, "476");
	if (!channelMap.empty()) {
		for (std::map<channel, std::vector<user> >::iterator it = channelMap.begin(); it != channelMap.end(); ++it) {
			if (argument[1] == it->first.getChannelName()) {
				it->second.push_back(Client);
				Server.sendJoinMsg(Server, Client, argument[1]);
				count = 1;
			}
		}
	}
	if (count != 1) {
		channel Channel(argument[1]);
		channelMap[Channel].push_back(Client);
		Channel.setOperator(Client);
		Server.sendJoinMsg(Server, Client, argument[1]);
	}
	Server.sendUserJoinMsg(Server, Client, argument[1]); 
	return;
}
void	commands::functionPART(server& Server, user& Client, std::vector<std::string>& argument){

	(void)Server;
	(void)Client;
	(void)argument;
	std::cout << "PART = quitter le channel" << std::endl;

	return;
}
void	commands::functionKICK(server& Server, user& Client, std::vector<std::string>& argument){

	(void)Server;
	(void)Client;
	(void)argument;
	std::cout << "KICK" << std::endl;

	return;
}
void	commands::functionINVITE(server& Server, user& Client, std::vector<std::string>& argument){

	(void)Server;
	(void)Client;
	(void)argument;
	std::cout << "INVITE" << std::endl;

	return;
}
void	commands::functionTOPIC(server& Server, user& Client, std::vector<std::string>& argument){

	(void)Server;
	(void)Client;
	(void)argument;
	std::cout << "TOPIC" << std::endl;

	return;
}
void	commands::functionMODE(server& Server, user& Client, std::vector<std::string>& argument){

	(void)Server;
	(void)Client;
	(void)argument;
	std::cout << "MODE" << std::endl;

	return;
}
void	commands::functionPRIVMSG(server& Server, user& Client, std::vector<std::string>& argument){

	(void)Server;
	(void)Client;
	(void)argument;
	std::cout << "PRIVMSG" << std::endl;

	return;
}



/*--------------- Exception ------------- */
