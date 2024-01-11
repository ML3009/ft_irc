/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purple <purple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 16:14:47 by mvautrot          #+#    #+#             */
/*   Updated: 2024/01/11 17:19:42 by purple           ###   ########.fr       */
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
	cmdMap["/NAMES"] = &commands::cmdNAMES;
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
			Server.sendMsg(Client, Server,"421", "", "");
	}
	else
		Server.sendMsg(Client, Server,"421", "", "");
	debug("getCommand", END);

	return;
}

void	commands::getAuthentified(server& Server, user& Client, std::vector<std::string>& argument) {

	debug("getAuthentified", BEGIN);
    if (!argument.empty()) {
		int cmd = isCmdAuthentified(Client, argument[0]);
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
		Server.sendMsg(Client, Server, "461", "", "");
		return;
	}
	if (argument[1] == Server.getPassword()) {
		if (Client.getPassword().empty())
			Client.setPassword(argument[1]);
		else
			return 	Server.sendMsg(Client, Server, "462", "", "");
	}
	else
		Server.sendMsg(Client, Server, "464", "", "");

	return;
}

void	commands::cmdNICK(server& Server, user& Client, std::vector<std::string>& argument){

	(void)Server;
	int	count = 0;
	for (std::vector<std::string>::iterator it = argument.begin(); it != argument.end(); ++it, ++count);
	if (count != 2)
		return Server.sendMsg(Client, Server, "461", "", "");
	if (argument[1].find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789[]\\`_^{|}-") != std::string::npos)
		return Server.sendMsg(Client, Server, "432", "", "");
	for(std::map<int, user>::iterator it = Server.getUserMap().begin(); it != Server.getUserMap().end(); ++it) {
		if (argument[1] == it->second.getNickname())
			return Server.sendMsg(Client, Server, "463", "", "");
	}
	Client.setNickname(argument[1]);
	return;
}

void	commands::cmdUSER(server& Server, user& Client, std::vector<std::string>& argument){

	(void)Server;
	int	count = 0;
	for (std::vector<std::string>::iterator it = argument.begin(); it != argument.end(); ++it, ++count);
	if (count < 5) {
		return Server.sendMsg(Client, Server, "461", "", "");
	}
	else if (count > 5 && argument[4][0] != ':') {
		return Server.sendMsg(Client, Server, "461", "", "");
	}
	if (!Client.getUsername().empty()) {
		return Server.sendMsg(Client, Server, "462", "", "");
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
	std::vector<std::string> key_tmp;
	int	keyword = parseCmdJoin(Server, Client, argument); // regarde s il y a le bon nombre d argument
	if (keyword < 0)
		return;

	std::vector<std::string> channel_tmp = splitCmdJoin(argument[1]); // split les #channel;

	if (parseChannelName(Server, Client, channel_tmp) < 0) // parse les #channel;
		return;

	if (keyword == 1){
		key_tmp = splitCmdJoin(argument[2]); // split les mots cles
		if (parseChannelKeyword(Server, Client, key_tmp, channel_tmp) < 0) // parse les mots cles et me permet de savoir cb il y a de cles
			return;
	}

	int	channelValidExist = 0;
	for (unsigned long i = 0; i < channel_tmp.size(); ++i) {
		if (!Server.getChannelMap().empty()) {
			for (std::map<std::string, channel>::iterator it = Server.getChannelMap().begin(); it != Server.getChannelMap().end(); ++it) {
				if (channel_tmp[i] == it->second.getChannelName()) {
					channelValidExist = isValidUser(Server, Client, it->second, key_tmp, i);
					switch (channelValidExist) {
						case USR_IN_CHANNEL:
							Server.sendMsg(Client, Server, "ERROR", Client.getUsername() + " is already in " + it->second.getChannelName(), "");
							break;
						case CHANNELISFULL:
							Server.sendMsg(Client, Server, "ERROR", it->second.getChannelName() + "is full","");
							break;
						case INVITEONLYCHAN:
							Server.sendMsg(Client, Server, "473", "", it->second.getChannelName());
							break;
						case BADCHANNELKEY:
							Server.sendMsg(Client, Server, "475", "" , it->second.getChannelName());
							break;
						case ISVALIDUSER:
							UserJoinChannel(Server, Client, it->second);
							break;
					}
				}
			}
		}
		if (channelValidExist == 0) {
			channel Channel(channel_tmp[i]);
			Channel.setChannelUser(Client);
			Channel.setOperator(Client.getUsername());
			if (keyword == 1 && i <= key_tmp.size()) {
				Channel.setKeyword(key_tmp[i]);
				Channel.setMode("k");
			}
			Server.getChannelMap()[channel_tmp[i]] = Channel;
			Server.sendMsg(Client, Server, "WELCOME", "You are now connected on the channel " + Channel.getChannelName() + ". Say hi to everyone", "");

		}
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

	int count = 0;
	for (std::vector<std::string>::iterator it = argument.begin(); it != argument.end(); ++it, count++); 
	if (count != 3)
		return Server.sendMsg(Client, Server, "461", "", "");
	if (!Server.userExist(argument[1]))		
		return Server.sendMsg(Client, Server, "401", "", argument[1]);
	for (std::map<std::string, channel>::iterator it = Server.getChannelMap().begin(); it != Server.getChannelMap().end(); ++it) {
		if (it->first == argument[1]){
			if (!(it->second.isAlreadyinChannel(Client)))
				return Server.sendMsg(Client, Server, "441", "", argument[2]);
			if  (it->second.isAlreadyinChannel(Server.getClient(argument[2])))
				return Server.sendMsg(Client, Server, "441", "", argument[2]);
			if  (it->second.isOperator(Client))
			{
				std::string message;
				message += "You have been kicked from " 
				+ it->second.getChannelName() + " by " + Client.getNickname() + ".";
				
				std::vector<user>::iterator ita = std::find(it->second.getChannelUser().begin(), it->second.getChannelUser().end(), Server.getClient(argument[2]));
				it->second.getChannelUser().erase(ita);
				Server.sendMsg(Server.getClient(argument[2]), Server, "KICK", message, it->second.getChannelName());
				Server.sendMsgToChannel(Client, Server, "KICK" , Client.getNickname() + " has been kicked from the channel. Bye bye ", it->second.getChannelName());
				return;
			}
			else
				return Server.sendMsg(Client, Server, "482", "", argument[2]);
		}
	}
	return Server.sendMsg(Client, Server, "403", "", argument[1]);
	return;
}

void	commands::cmdINVITE(server& Server, user& Client, std::vector<std::string>& argument){
	
	int count = 0;
	for (std::vector<std::string>::iterator it = argument.begin(); it != argument.end(); ++it, count++);
	if (count != 3)
		return Server.sendMsg(Client, Server, "461", "", "");
	if (!Server.userExist(argument[1]))		
		return Server.sendMsg(Client, Server, "401", "", argument[1]);
	for (std::map<std::string, channel>::iterator it = Server.getChannelMap().begin(); it != Server.getChannelMap().end(); ++it) {
		if (it->first == argument[2]){
			if (it->second.isAlreadyinChannel(Client) \
			&& !(it->second.isAlreadyinChannel(Server.getClient(argument[1]))) \
			&& !(it->second.isInvited(argument[1])))
			{
				std::string message;
				message += "You have been invited on " 
				+ it->second.getChannelName() + " by " + Client.getNickname() + ".";
				
				Server.sendMsg(Server.getClient(argument[1]), Server, "INVITE", message, it->second.getChannelName());
				it->second.getInviteList().push_back(Client.getUsername());
				Server.sendMsgToChannel(Client, Server, "INVITE" , Client.getNickname() + " his now on the invite list. He can now join at any moment", it->second.getChannelName());
				Server.sendMsg(Server.getClient(argument[1]), Server, "INVITE", "You are now on the invite list of " + it->second.getChannelName(), it->second.getChannelName());
				return;
			}
			else
				return Server.sendMsg(Client, Server, "441", "", argument[1]);
		}
	}
	return Server.sendMsg(Client, Server, "403", "", argument[1]);
}

void	commands::cmdTOPIC(server& Server, user& Client, std::vector<std::string>& argument){

	int count = 0;
	std::string message;
	for (std::vector<std::string>::iterator it = argument.begin(); it != argument.end(); ++it, count++);
	if (count < 2 || (count > 3 && argument[2][0] != ':'))
		return Server.sendMsg(Client, Server, "461", "", "");
	if (count == 2){
		for (std::map<std::string, channel>::iterator it = Server.getChannelMap().begin(); it != Server.getChannelMap().end(); ++it) {
			if (it->first == argument[1])
			{
				std::vector<user> userlist = it->second.getChannelUser();
				for (std::vector<user>::iterator it = userlist.begin(); it != userlist.end(); ++it){
					if (it->getfd() == Client.getfd()){
						Server.sendMsg(Client, Server, "331", "", argument[1]);
					}
				}
				Server.sendMsg(Client, Server, "441", "", argument[1]);
			}
		}
		return Server.sendMsg(Client, Server, "403", "", argument[1]);
	}
	// else{
	// 	for (std::map<std::string, channel>::iterator ita = Server.getChannelMap().begin(); ita != Server.getChannelMap().end(); ++ita) {
	// 		if (ita->first == argument[1])
	// 		{

	// 		}
	// 	}
	// 	return Server.sendMsg(Client, Server, "403", "", argument[1]);
	// }

	return;
}

void	commands::cmdMODE(server& Server, user& Client, std::vector<std::string>& argument){

	std::vector<std::string> arg_mod;
	int count = 0;
	for (std::vector<std::string>::iterator it = argument.begin(); it != argument.end(); ++it, ++count);
	if (count < 3 || (argument[2][0] != '+' && argument[2][0] != '-'))
		return Server.sendMsg(Client, Server, "461", "", ""), void();
	char sign = argument[2][0];
	if (count > 3)
		std::copy(argument.begin() + 3, argument.end(), std::back_inserter(arg_mod));
	for (std::map<std::string, channel>::iterator it = Server.getChannelMap().begin(); it != Server.getChannelMap().end(); ++it) {
		if (argument[1] == it->second.getChannelName() && it->second.isOperator(Client) == true) {
			for (int i = 1; argument[2][i]; ++i){
				int ValidMod = isValidArgMod(Server, Client, it->second, argument[2][i]);
				switch(ValidMod) {
					case MODE_I:
						if (sign == '+')
							it->second.setMode(std::string(1, argument[2][i]));
						else if (sign == '-')
							it->second.unsetMode(std::string(1, argument[2][i]));
						break;
					case MODE_T:
						if (sign == '+')
							it->second.setMode(std::string(1, argument[2][i]));
						else if (sign == '-')
							it->second.unsetMode(std::string(1, argument[2][i]));
						break;
					case MODE_O:
						if (sign == '+' && !arg_mod.empty()) {
							it->second.setMode(std::string(1, argument[2][i]));
							arg_mod.erase(arg_mod.begin());
						}
						else if (sign == '-' && !arg_mod.empty()) {
								it->second.unsetMode(std::string(1, argument[2][i]));
								arg_mod.erase(arg_mod.begin());
						}
						break;
					case MODE_K:
						if (sign == '+' && !arg_mod.empty()) {
							it->second.setMode(std::string(1, argument[2][i]));
							it->second.setKeyword(arg_mod[0]);
							arg_mod.erase(arg_mod.begin());
						}
						else if (sign == '-')
							it->second.unsetMode(std::string(1, argument[2][i]));
						break;
					case MODE_L:
						if (sign == '+' && !arg_mod.empty()) {
							it->second.setMode(std::string(1, argument[2][i]));
							arg_mod.erase(arg_mod.begin());
						}
						else if (sign == '-')
							it->second.unsetMode(std::string(1, argument[2][i]));
						break;
					case UNKNOW_MODE:
						Server.sendMsg(Client, Server, "472", "", "");
						break;

				}
			}
		}
	}

// l depassement limite utilisateur
// i invite only
// k regarder mdp
// t TOPIC : est ce que tt le monde peut le changer ou pas.

// o donner retirer le privilege de loperateur cnal

	return;
}

void	commands::cmdPRIVMSG(server& Server, user& Client, std::vector<std::string>& argument){
	int destination = 0; // 0 FOR USER | 1 FOR CHANNEL
	int count = 0;
	std::string message;
	for (std::vector<std::string>::iterator it = argument.begin(); it != argument.end(); ++it, count++);
	if (count < 3)
	{
		if (count > 1 && argument[1][0] == '&' && argument[1][0] == '#' && count == 2)
			return Server.sendMsg(Client, Server, "412", "", "");
		else if (count == 2)
		{
			for(std::map<int, user>::iterator it = Server.getUserMap().begin(); it != Server.getUserMap().end(); ++it)
				if (argument[1] == it->second.getNickname())
					return Server.sendMsg(Client, Server, "412", "", "");
			return Server.sendMsg(Client, Server, "411", "", "");
		}
		else
			return Server.sendMsg(Client, Server, "461", "", "");
	}
	if (argument[1][0] != '&' && argument[1][0] != '#')
		destination = pvm_USER;
	if (destination == pvm_USER){
		for(std::map<int, user>::iterator it = Server.getUserMap().begin(); it != Server.getUserMap().end(); ++it){
			if (argument[1] == it->second.getNickname())
			{
				for (std::vector<std::string>::iterator it = argument.begin() + 2; it != argument.end(); ++it)
					message += *it + " ";
				Server.sendMsgToUser(Client, it->second, Server, "PRIVMSG", message);
				return;
			}
		}
		return Server.sendMsg(Client, Server, "401", "", "");
	}
	else
	{
		for (std::vector<std::string>::iterator it = argument.begin() + 2; it != argument.end(); ++it)
			message += *it + " ";
		Server.sendMsgToChannel(Client, Server , "PRIVMSG", message, argument[1]);
	}
	return;
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

void 	commands::cmdNAMES(server& Server, user& Client, std::vector<std::string>& argument){

	int count = 0;
	std::ostringstream oss;

	for (std::vector<std::string>::iterator it = argument.begin(); it != argument.end(); ++it, count++);
	switch (count)
	{
		case 1:
			if (Server.getChannelMap().empty())
				return Server.sendMsg(Client, Server, "403", "", "");
			for (std::map<std::string, channel>::iterator ita = Server.getChannelMap().begin(); ita != Server.getChannelMap().end(); ++ita)
			{
					oss << ita->second.getChannelUser().size();
					std::string msg = ita->second.display_mode() + ita->second.getChannelName() + " has " + oss.str() + " user connected :\n";
					for (std::vector<user>::iterator itb = ita->second.getChannelUser().begin(); itb != ita->second.getChannelUser().end(); itb++){
						msg += "\t"+ printOP(itb->getUsername(), ita->second) +" - Nickname : " + itb->getNickname() + " | Username : " + itb->getUsername() + "\n";
					}
					Server.sendMsg(Client, Server,"NAMES",msg ,"");
					oss.str("");
					oss.clear();
			}
			return;
		case 2:
			for (std::map<std::string, channel>::iterator ita = Server.getChannelMap().begin(); ita != Server.getChannelMap().end(); ++ita)
			{
				if (ita->first == argument[1])
				{
					oss << ita->second.getChannelUser().size();
					std::string msg = ita->second.display_mode() + ita->second.getChannelName() + " has " + oss.str() + " user connected :\n";
					for (std::vector<user>::iterator itb = ita->second.getChannelUser().begin(); itb != ita->second.getChannelUser().end(); itb++){
						msg += "\t"+ printOP(itb->getUsername(), ita->second) +" - Nickname : " + itb->getNickname() + " | Username : " + itb->getUsername()+ "\n";
					}
					return Server.sendMsg(Client, Server,"NAMES",msg ,"");
				}
			}
			return Server.sendMsg(Client, Server, "403", "", "");

		default:
			Server.sendMsg(Client, Server, "461", "", "");
	}
}
