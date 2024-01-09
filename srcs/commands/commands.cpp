/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purple <purple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 16:14:47 by mvautrot          #+#    #+#             */
/*   Updated: 2024/01/09 10:25:32 by purple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.hpp"

/*----------------- Coplien ------------- */

commands::commands(){

	cmdMap["/INVITE"] = &commands::cmdINVITE;
	cmdMap["/JOIN"] = &commands::cmdJOIN;
	cmdMap["/KICK"] = &commands::cmdKICK;
	cmdMap["/MODE"] = &commands::cmdMODE;
	cmdMap["/NICK"] = &commands::cmdNICK;
	cmdMap["/PART"] = &commands::cmdPART;
	cmdMap["/PASS"] = &commands::cmdPASS;
	cmdMap["/PRIVMSG"] = &commands::cmdPRIVMSG;
	cmdMap["/QUIT"] = &commands::cmdQUIT;
	cmdMap["/TOPIC"] = &commands::cmdTOPIC;
	cmdMap["/USER"] = &commands::cmdUSER;
	cmdMap["@bot"] = &commands::cmdBOT;
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
	bool command = false;
	if (!argument.empty()) {
		for (std::map<std::string, cmdFunctionPointer>::iterator it = cmdMap.begin(); it != cmdMap.end(); ++it) {
			if (it->first == argument[0]){
				(this->*(it->second))(Server, Client, argument);
				command = true;
			}
		}
		if (command == false)
			Server.sendMsg(Client, Server,"421");
	}
	else
		Server.sendMsg(Client, Server,"421");
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
				!(Client.getUsername().empty()) ? Server.sendrawMsg(Client, Server, "\e[0;36m \t[Username] " + Client.getUsername() + "\e[0m")  : Server.sendrawMsg(Client, Server, "\e[0;36m \t[/USER] username must be set \e[0m");
				!(Client.getNickname().empty()) ? Server.sendrawMsg(Client, Server, "\e[0;36m \t[Nickname] " + Client.getNickname() + "\e[0m") : Server.sendrawMsg(Client, Server, "\e[0;36m \t[/NICK] nickname must be set \e[0m");
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

void	commands::cmdPASS(server& Server, user& Client, std::vector<std::string>& argument){

	int	count = 0;
	for (std::vector<std::string>::iterator it = argument.begin(); it != argument.end(); ++it, ++count);
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
void	commands::cmdNICK(server& Server, user& Client, std::vector<std::string>& argument){

	(void)Server;
	int	count = 0;
	for (std::vector<std::string>::iterator it = argument.begin(); it != argument.end(); ++it, ++count);
	if (count != 2)
		return Server.sendMsg(Client, Server, "461");
	if (argument[1].find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789[]\\`_^{|}-") != std::string::npos)
		return Server.sendMsg(Client, Server, "432");
	for(std::map<int, user>::iterator it = Server.getUserMap().begin(); it != Server.getUserMap().end(); ++it) {
		if (argument[1] == it->second.getNickname())
			return Server.sendMsg(Client, Server, "463");
	}
	Client.setNickname(argument[1]);
	//std::cout << Client.getNickname() << std::endl;
	return;
}
void	commands::cmdUSER(server& Server, user& Client, std::vector<std::string>& argument){

	(void)Server;
	int	count = 0;
	for (std::vector<std::string>::iterator it = argument.begin(); it != argument.end(); ++it, ++count);
	if (count < 5) {
		return Server.sendMsg(Client, Server, "461");
	}
	else if (count > 5 && argument[4][0] != ':') {
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
void	commands::cmdQUIT(server& Server, user& Client, std::vector<std::string>& argument){

	(void)Server;
	(void)Client;
	(void)argument;
	std::cout << "QUIT" << std::endl;

	return;
}
void	commands::cmdJOIN(server& Server, user& Client, std::vector<std::string>& argument){

	// modif pour prevoir plusieurs canaux
	//splitarg deux vector : 1 avec canal 1 avec cle
	//gere mode -k : mettre le container std::set -> on ne peut pas avoir de doublon. stocker le k dans un endroit qui sera tjrs le mm.
	int	count = 0;
	for (std::vector<std::string>::iterator it = argument.begin(); it != argument.end(); ++it, ++count);
	if (count < 2)
		return Server.sendMsg(Client, Server, "461");
	std::vector<std::string> channel_tmp = splitCmdJoin(argument[1]);
	if (count > 2){
		std::vector<std::string> key_tmp = splitCmdJoin(argument[2]);
		if (channel_tmp.size() < key_tmp.size())
			return Server.sendMsg(Client, Server, "461");
	}
	for (unsigned long i = 0; i < channel_tmp.size(); ++i) {
		if (channel_tmp[i][0] != '&' && channel_tmp[i][0] != '#')
			return Server.sendMsg(Client, Server, "476");
		if (channel_tmp[i].find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789[]\\`_^{|}-#&") != std::string::npos)
			return Server.sendMsg(Client, Server, "476");
		if (!Server.getChannelMap().empty()) {
			for (std::map<std::string, channel>::iterator it = Server.getChannelMap().begin(); it != Server.getChannelMap().end(); ++it) {
				if (channel_tmp[i] == it->second.getChannelName()) {
					if (it->second.isAlreadyinChannel(Client) == true) 
						return;
					it->second.setChannelUser(Client);
					Server.sendJoinMsg(Server, Client, channel_tmp[i]);
					it->second.display_operators(it->second.getChannelOperators());
					count = 1;
				}
			}
		}
		if (count != 1) {
			channel Channel(channel_tmp[i]);
			Channel.setChannelUser(Client);
			Channel.setOperator(Client.getUsername());
			Server.getChannelMap()[channel_tmp[i]] = Channel;
			Server.sendJoinMsg(Server, Client, channel_tmp[i]);
		}
		Server.sendUserJoinMsg(Server, Client, channel_tmp[i]);
	}

	return;
}
void	commands::cmdPART(server& Server, user& Client, std::vector<std::string>& argument){

	(void)Server;
	(void)Client;
	(void)argument;
	std::cout << "PART = quitter le channel" << std::endl;

	return;
}
void	commands::cmdKICK(server& Server, user& Client, std::vector<std::string>& argument){

	(void)Server;
	(void)Client;
	(void)argument;
	std::cout << "KICK" << std::endl;

	return;
}
void	commands::cmdINVITE(server& Server, user& Client, std::vector<std::string>& argument){

	(void)Server;
	(void)Client;
	(void)argument;
	std::cout << "INVITE" << std::endl;

	return;
}
void	commands::cmdTOPIC(server& Server, user& Client, std::vector<std::string>& argument){

	(void)Server;
	(void)Client;
	(void)argument;
	std::cout << "TOPIC" << std::endl;

	return;
}
void	commands::cmdMODE(server& Server, user& Client, std::vector<std::string>& argument){

	(void)Server;
	(void)Client;
	(void)argument;
	std::cout << "MODE" << std::endl;

	return;
}
void	commands::cmdPRIVMSG(server& Server, user& Client, std::vector<std::string>& argument){
	(void)Server;
	(void)Client;
	(void)argument;


	// int destination = 0; // 0 FOR USER | 1 FOR CHANNEL
	// int count = 0;
	// std::string message;
	// for (std::vector<std::string>::iterator it = argument.begin(); it != argument.end(); ++it, count++);
	// if (count < 3)
	// {
	// 	if (argument[1][0] == '&' && argument[1][0] == '#' && count == 2)
	// 		return Server.sendMsg(Client, Server, "412");
	// 	else if (count == 2)
	// 	{
	// 		for(std::map<int, user>::iterator it = clientMap.begin(); it != clientMap.end(); ++it)
	// 			if (argument[1] == it->second.getNickname())
	// 				return Server.sendMsg(Client, Server, "412");
	// 		return Server.sendMsg(Client, Server, "411");
	// 	}
	// 	else
	// 		return Server.sendMsg(Client, Server, "461");
	// }
	// if (argument[1][0] != '&' && argument[1][0] != '#')
	// 	destination = 1;
	// if (destination == 1){
	// 	for(std::map<int, user>::iterator it = clientMap.begin(); it != clientMap.end(); ++it){
	// 		if (argument[1] == it->second.getNickname())
	// 		{
	// 			for (std::vector<std::string>::iterator it = argument.begin() + 2; it != argument.end(); ++it)
	// 				message += *it + " ";
	// 			Server.sendMsgToUser(Client, it->second, Server, "PRIVMSG", message);
	// 			return;
	// 		}
	// 	}
	// 	return Server.sendMsg(Client, Server, "401");
	// }
	// else
	// {
	// 	for (std::map<channel, std::vector<user> >::iterator it = channelMap.begin(); it != channelMap.end(); ++it) {
	// 		if (argument[1] == it->first.getChannelName())
	// 		{
	// 			for (std::vector<std::string>::iterator it = argument.begin() + 2; it != argument.end(); ++it)
	// 				message += *it + " ";
	// 			Server.sendMsgToChannel(Client, it->second, Server, "PRIVMSG", message, argument[1]);
	// 		}
	// 		else
	// 			return Server.sendMsg(Client, Server, "401");
	// 	}
	// }
	// return;
}

void	commands::cmdBOT(server& Server, user& Client, std::vector<std::string>& argument){
	int count = 0;
	for (std::vector<std::string>::iterator it = argument.begin(); it != argument.end(); ++it, count++);
	if (count == 2 && argument[1] == "HELP")
		Server.getbot().help(Server, Client);
	else if (count == 2 && argument[1] == "FACT")
	{
		std::srand(std::time(0));
		Server.getbot().getfact(Server, Client, std::rand() % 10);
	}
	else
		Server.getbot().sayhello(Server, Client);

}
