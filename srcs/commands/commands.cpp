/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvautrot <mvautrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 16:14:47 by mvautrot          #+#    #+#             */
/*   Updated: 2024/01/17 12:38:23 by mvautrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.hpp"

/*----------------- Coplien ------------- */

commands::commands(){

	cmdMap["CAP LS"] = &commands::cmdCAPLS;
	cmdMap["INVITE"] = &commands::cmdINVITE; // ok
	cmdMap["JOIN"] = &commands::cmdJOIN; // ok
	cmdMap["KICK"] = &commands::cmdKICK; // ok
	cmdMap["MODE"] = &commands::cmdMODE; // ok
	cmdMap["NICK"] = &commands::cmdNICK; // ok
	cmdMap["PART"] = &commands::cmdPART; // ok
	cmdMap["PASS"] = &commands::cmdPASS; // ok
	cmdMap["NAMES"] = &commands::cmdNAMES; // ok
	cmdMap["PRIVMSG"] = &commands::cmdPRIVMSG; // ok
	cmdMap["QUIT"] = &commands::cmdQUIT; // a faire
	cmdMap["TOPIC"] = &commands::cmdTOPIC; // en cours
	cmdMap["USER"] = &commands::cmdUSER;//ok
	cmdMap["@bot"] = &commands::cmdBOT; // ok mais modif ideal
}

commands::commands(const commands& rhs){
	*this = rhs;
	return;
}

commands& commands::operator=(const commands& rhs){
	if(this != &rhs) {
		this->cmdMap = rhs.cmdMap;
	}
	return *this;
}

commands::~commands(){

}

/*---------- Getter / Setter ------------ */

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
	if ((!argument.empty() && argument.size() > 1)) {
		if (argument[0] == "CAP" && argument[1] == "LS") {
			argument[0] = "CAP LS";
			argument.erase(argument.begin() + 1); // cas erreur a regarder qd cap ls deja ecrit
		}
	}
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
			case CAP_LS:
				getCommand(Server,Client, argument);
				break;
			default:
				Server.sendrawMsg(Client, Server, "\e[0;33m[ You are not connected to the server ]\e[0m");
				if (!(Client.getPassword().empty()))
					Server.sendrawMsg(Client, Server, "\e[0;36m\t[Password] OK\e[0m");
				else{
					Server.sendrawMsg(Client, Server, "\e[0;36m\tuse PASS before doing anything\e[0m");
					break;
				}
				!(Client.getUsername().empty()) ? Server.sendrawMsg(Client, Server, "\e[0;36m \t[Username] " + Client.getUsername() + "\e[0m")  : Server.sendrawMsg(Client, Server, "\e[0;36m \t[USER] username must be set \e[0m");
				!(Client.getNickname().empty()) ? Server.sendrawMsg(Client, Server, "\e[0;36m \t[Nickname] " + Client.getNickname() + "\e[0m") : Server.sendrawMsg(Client, Server, "\e[0;36m \t[NICK] nickname must be set \e[0m");
		}
	}
	debug("getAuthentified", END);
	return;
}

int	commands::isCmdAuthentified(user& Client, std::string argument){
	if (!argument.empty()) {
		if (argument == "CAP LS")
			return 3;
		if (Client.getPassword().empty() && argument == "PASS")
			return 0;
		else if (!Client.getPassword().empty()){
			if (Client.getNickname().empty() && argument == "NICK")
				return 1;
			if (!Client.getNickname().empty() && argument == "USER")
				return 2;
		}
	}
   return -1;
}


/*--------------- Function -------------- */



void	commands::cmdCAPLS(server& Server, user& Client, std::vector<std::string>& argument) {

	std::vector<std::string> pass;
	std::vector<std::string> nick;
	std::vector<std::string> user;

	if (argument.size() < 9)
		return Server.sendMsg(Client, Server, "461", "", "");
	if (argument[1] == "PASS") {
		pass.push_back(argument[1]);
		pass.push_back(argument[2]);
		cmdPASS(Server, Client, pass);
	}
	if (argument[3] == "NICK") {
		nick.push_back(argument[3]);
		nick.push_back(argument[4]);
		cmdNICK(Server, Client, nick);
	}
	if (argument[5] == "USER") {
		for (int i = 5; (unsigned long)i < argument.size(); ++i) {
			user.push_back(argument[i]);
		}
		cmdUSER(Server, Client, user);
	}
	return;
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

void	commands::cmdJOIN(server& Server, user& Client, std::vector<std::string>& argument){

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

	int	channelValidExist = 5;
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
							Server.sendMsg(Client, Server, "ERROR", it->second.getChannelName() + " is full","");
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
						default:
							std::cout << "error" << std::endl;
					}
				}
			}
		}
		if (channelValidExist == 5) {
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

	int count = 0;
	for (std::vector<std::string>::iterator it = argument.begin(); it != argument.end(); ++it, count++);
	if (count != 2)
		return Server.sendMsg(Client, Server, "461", "", "");
	std::vector<std::string> channel_tmp = splitCmdJoin(argument[1]);
	std::vector<std::map<std::string, channel>::iterator> channelsToRemove;

	for (unsigned long i = 0; i < channel_tmp.size(); ++i) {
		if (!Server.getChannelMap().empty()) {
			for (std::map<std::string, channel>::iterator it = Server.getChannelMap().begin(); it != Server.getChannelMap().end(); ++it) {
				if (it->second.getChannelName() == channel_tmp[i]) {
					if(it->second.isAlreadyinChannel(Client) == true) {
						Server.sendMsg(Client, Server, "LEAVE", "You have left the channel " + it->second.getChannelName(), "");
						Server.sendMsgToChannel(Client, Server, "LEAVE", Client.getNickname() + " has left the channel. Goodbye!", it->second.getChannelName());
						it->second.unsetChannelUser(Client);
						if (it->second.getChannelUser().empty()) {
							channelsToRemove.push_back(it);
						}

					} else if (channel_tmp[i] == it->second.getChannelName() && it->second.isAlreadyinChannel(Client) == false) {
						Server.sendMsg(Client, Server, "442", "", it->second.getChannelName()), void();
					}
				}
			}
		}
		if (Server.channelExist(channel_tmp[i]) == false)
			Server.sendMsg(Client, Server, "403", "", channel_tmp[i]);
	}
	for (std::vector<std::map<std::string, channel>::iterator>::iterator it = channelsToRemove.begin(); it != channelsToRemove.end(); ++it) {
    	Server.getChannelMap().erase(*it);
	}
	return;
}

void	commands::cmdQUIT(server& Server, user& Client, std::vector<std::string>& argument){

	int count = 0;
	for (std::vector<std::string>::iterator it = argument.begin(); it != argument.end(); ++it, count++);
	std::string msg;
	if (count > 1 && argument[1][0] != ':')
		return Server.sendMsg(Client, Server, "461", "", "");
	if (count > 1){
		if (argument[1][0] == ':') {
			for (unsigned long i = 1; i < argument.size(); i++)
				msg += argument[i] + " ";
		}
		else
			msg += argument[1];
	}
	std::vector<std::map<std::string, channel>::iterator> channelsToRemove;
	if (!Server.getChannelMap().empty()) {
		for (std::map<std::string, channel>::iterator it = Server.getChannelMap().begin(); it != Server.getChannelMap().end(); ++it){
			if (it->second.isAlreadyinChannel(Client) == true) {
				if (count > 1)
					Server.sendMsgToChannel(Client, Server, "QUIT_MSG" ,  msg, it->second.getChannelName());
				else
					Server.sendMsgToChannel(Client, Server, "QUIT", Client.getNickname() + " has left the channel. Goodbye!", it->second.getChannelName());
				it->second.unsetChannelUser(Client);
				Server.sendMsg(Client, Server, "QUIT", "You have left the channel " + it->second.getChannelName(), "");
				if (it->second.getChannelUser().empty()) {
						channelsToRemove.push_back(it);
				}
			}
		}
	}
	for (std::vector<std::map<std::string, channel>::iterator>::iterator it = channelsToRemove.begin(); it != channelsToRemove.end(); ++it) {
    	Server.getChannelMap().erase(*it);
	}
	Server.sendMsg(Client, Server, "QUIT", "Leaving the server. Goodbye!", "");
	Client.setStatus(DISCONNECTED);
	return;
}

void	commands::cmdKICK(server& Server, user& Client, std::vector<std::string>& argument){

	int count = 0;
	for (std::vector<std::string>::iterator it = argument.begin(); it != argument.end(); ++it, count++);
	if (count != 3)
		return Server.sendMsg(Client, Server, "461", "", "");
	for (std::map<std::string, channel>::iterator it = Server.getChannelMap().begin(); it != Server.getChannelMap().end(); ++it) {
		if (it->first == argument[1]){
			if (!(it->second.isAlreadyinChannel(Client)))
				return Server.sendMsg(Client, Server, "441", "", argument[2]);
			if  (!(it->second.isAlreadyinChannel(Server.getClient(argument[2]))))
				return Server.sendMsg(Client, Server, "441", "", argument[2]);
			if  (it->second.isOperator(Client.getUsername()))
			{
				std::string message;
				message += "You have been kicked from "
				+ it->second.getChannelName() + " by " + Client.getNickname() + ".";

				std::vector<user>::iterator ita = std::find(it->second.getChannelUser().begin(), it->second.getChannelUser().end(), Server.getClient(argument[2]));
				it->second.getChannelUser().erase(ita);
				Server.sendMsg(Server.getClient(argument[2]), Server, "KICK", message, it->second.getChannelName());
				Server.sendMsg(Client, Server, "KICK", argument[2] + " has been kicked from the channel. Bye bye ", it->second.getChannelName());
				Server.sendMsgToChannel(Client, Server, "KICK" , argument[2] + " has been kicked from the channel. Bye bye ", it->second.getChannelName());
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
				it->second.getInviteList().push_back(Server.getClient(argument[1]).getUsername());
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
	std::string msg;
	for (std::vector<std::string>::iterator it = argument.begin(); it != argument.end(); ++it, count++);
	if (count < 2 || (count > 3 && argument[2][0] != ':'))
		return Server.sendMsg(Client, Server, "461", "", "");
	if (count > 3) {
		if (argument[2][0] == ':') {
			for (unsigned long i = 2; i < argument.size(); i++) {
				msg += argument[i];
				msg += " ";
			}
		}
		else
			msg += argument[2];
	}
	if (!Server.getChannelMap().empty()) {
		for (std::map<std::string, channel>::iterator it = Server.getChannelMap().begin(); it != Server.getChannelMap().end(); ++it){
			if (it->second.getChannelName() == argument[1]) {
				if (it->second.isAlreadyinChannel(Client) == true) {
					if (count > 2) {
						if (it->second.search_mode('t') == true) {
							if (it->second.isOperator(Client.getUsername()) == true) {
								it->second.setTopic(msg);
								Server.sendMsg(Client, Server, "TOPIC", "You have been created a new topic on " + it->second.getChannelName(), "");
								Server.sendMsgToChannel(Client, Server, "TOPIC" , "A new topic " + msg + " has been created on " + it->second.getChannelName() + " by " + Client.getNickname() + ".", it->second.getChannelName());
							} else
								return Server.sendMsg(Client, Server, "482", "", argument[2]);
						} else {
							it->second.setTopic(msg);
							Server.sendMsg(Client, Server, "332", it->second.getChannelName() + msg , "");
							Server.sendMsgToChannel(Client, Server, "TOPIC" , "A new topic " + msg + " has been created on " + it->second.getChannelName() + " by " + Client.getNickname() + ".", it->second.getChannelName());
						}
					} else {
							if (!it->second.getTopic().empty())
								Server.sendMsg(Client, Server, "332", it->second.getChannelName() + it->second.getTopic(), "");
							else
								Server.sendMsg(Client, Server, "331", "", argument[1]);
					}
				} else
					return Server.sendMsg(Client, Server, "441", "", argument[1]);
			}
			if (Server.channelExist(argument[1]) == false)
				Server.sendMsg(Client, Server, "403", "", argument[1]);
		}
	}
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
		if (argument[1] == it->second.getChannelName() && it->second.isOperator(Client.getUsername()) == true) {
			for (int i = 1; argument[2][i]; ++i){
				int ValidMod = isValidArgMod(argument[2][i]);
				std::cout << sign << std::endl;
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
							if (Server.userExist(arg_mod[0]) == true && it->second.isOperator(arg_mod[0]) == false){
								it->second.setOperator(arg_mod[0]);
								arg_mod.erase(arg_mod.begin());
							}
						}
						else if (sign == '-' && !arg_mod.empty()) {
							if (Server.userExist(arg_mod[0]) == true && it->second.isOperator(arg_mod[0]) == true) {
								it->second.unsetOperator(arg_mod[0]);
								arg_mod.erase(arg_mod.begin());
							}
						}
						break;
					case MODE_K:
						if (sign == '+' && !arg_mod.empty()) {
							it->second.setMode(std::string(1, argument[2][i]));
							it->second.setKeyword(arg_mod[0]);
							arg_mod.erase(arg_mod.begin());
						}
						else if (sign == '-') {
							it->second.unsetMode(std::string(1, argument[2][i]));
							it->second.unsetKeyword();
						}
						break;
					case MODE_L:
						if (sign == '+' && !arg_mod.empty()) {
							if(it->second.isValidLimit(arg_mod[0]) == true) {
								it->second.setMode(std::string(1, argument[2][i]));
								it->second.setLimit(arg_mod[0]);
								arg_mod.erase(arg_mod.begin());
								break;
							}
							break;
						}
						else if (sign == '-') {
							it->second.unsetMode(std::string(1, argument[2][i]));
							it->second.unsetLimit();
						}
						break;
					default:
						Server.sendMsg(Client, Server, "472", "", "");
						break;

				}
			}
		} else if (argument[1] == it->second.getChannelName() && it->second.isAlreadyinChannel(Client) == false){
			return Server.sendMsg(Client, Server, "442", "", it->second.getChannelName()), void();
		} else if (argument[1] == it->second.getChannelName() && it->second.isOperator(Client.getUsername()) == false) {
			return Server.sendMsg(Client, Server, "482", "", it->second.getChannelName()), void();
		} else if (Server.channelExist(argument[1]) == false)
			return Server.sendMsg(Client, Server, "403", "", argument[1]);
	}
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
