/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purple <purple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 16:14:47 by mvautrot          #+#    #+#             */
/*   Updated: 2024/01/18 16:02:06 by purple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.hpp"

/*----------------- Coplien ------------- */

commands::commands(){

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
			Server.sendMsg(Server, Client, ERR_UNKNOWNCOMMAND(command));
	}
	else
		Server.sendMsg(Server, Client, ERR_UNKNOWNCOMMAND(command));
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
				return;
				break;
			default:
				Server.sendrawMsg(Server, Client, "\033[0;33m[ You are not connected to the server ]\033[0m");
				if (!(Client.getPassword().empty()))
					Server.sendrawMsg(Server, Client, "\033[0;36m\t[Password] OK\033[0m");
				else{
					Server.sendrawMsg(Server, Client, "\033[0;36m\tuse /PASS before doing anything\033[0m");
					break;
				}
				!(Client.getUsername().empty()) ? Server.sendrawMsg(Server, Client, "\033[0;36m \t[Username] " + Client.getUsername() + "\033[0m")  : Server.sendrawMsg(Server, Client, "\033[0;36m \t[/USER] username must be set \033[0m");
				!(Client.getNickname().empty()) ? Server.sendrawMsg(Server, Client, "\033[0;36m \t[Nickname] " + Client.getNickname() + "\033[0m") : Server.sendrawMsg(Server, Client, "\033[0;36m \t[/NICK] nickname must be set \033[0m");
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



void	commands::cmdPASS(server& Server, user& Client, std::vector<std::string>& argument){

	int	count = 0;
	for (std::vector<std::string>::iterator it = argument.begin(); it != argument.end(); ++it, ++count);
	if (count != 2) {
		Server.sendMsg(Server, Client, ERR_NEEDMOREPARAMS(Server, Client));
		return;
	}
	if (argument[1] == Server.getPassword()) {
		if (Client.getPassword().empty())
			Client.setPassword(argument[1]);
		else
			return 	Server.sendMsg(Server, Client, ERR_ALREADYREGISTRED(Server, Client));
	}
	else
		Server.sendMsg(Server, Client, ERR_PASSWDMISMATCH(Server, Client));

	return;
}

void	commands::cmdNICK(server& Server, user& Client, std::vector<std::string>& argument){

	(void)Server;
	int	count = 0;
	for (std::vector<std::string>::iterator it = argument.begin(); it != argument.end(); ++it, ++count);
	if (count != 2)
		return Server.sendMsg(Server, Client, ERR_NEEDMOREPARAMS(Server, Client));
	if (argument[1].find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789[]\\`_^{|}-") != std::string::npos)
			return Server.sendMsg(Server, Client, ERR_NICKNAMEINUSE (Server, Client, argument[1]));
	for(std::map<int, user>::iterator it = Server.getUserMap().begin(); it != Server.getUserMap().end(); ++it) {
		if (argument[1] == it->second.getNickname())
			return Server.sendMsg(Server, Client, ERR_NICKNAMEINUSE (Server, Client, argument[1]));
	}
	Client.setNickname(argument[1]);
	return;
}

void	commands::cmdUSER(server& Server, user& Client, std::vector<std::string>& argument){

	int	count = 0;
	for (std::vector<std::string>::iterator it = argument.begin(); it != argument.end(); ++it, ++count);
	if (count < 5) {
		return Server.sendMsg(Server, Client, ERR_NEEDMOREPARAMS(Server, Client));
	}
	else if (count > 5 && argument[4][0] != ':') {
		return Server.sendMsg(Server, Client, ERR_NEEDMOREPARAMS(Server, Client));
	}
	if (!Client.getUsername().empty()) {
		return Server.sendMsg(Server, Client, ERR_ALREADYREGISTRED(Server, Client));
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
	//:nickbb!~unbb@494f-a0a0-544-a020-fae1.210.62.ip JOIN :#htviosfdbsjdfsgdfvsjgvfa
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
							Server.sendMsg(Server, Client, "ERROR", Client.getUsername() + " is already in " + it->second.getChannelName(), "");
							break;
						case CHANNELISFULL:
							Server.sendMsg(Server, Client, "ERROR", it->second.getChannelName() + " is full","");
							break;
						case INVITEONLYCHAN:
							Server.sendMsg(Server, Client, ERR_INVITEONLYCHAN(Server, Client, it->second.getChannelName()));
							break;
						case BADCHANNELKEY:
							Server.sendMsg(Server, Client, BADCHANNELKEY(Server, Client, it->second.getChannelName()));
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
			Server.sendMsg(Server, Client, "JOIN", "You are now connected on the channel " + Channel.getChannelName() + ". Say hi to everyone", "");

		}
	}

	return;
}

void	commands::cmdPART(server& Server, user& Client, std::vector<std::string>& argument){
	//:nickbb!~unbb@494f-a0a0-544-a020-fae1.210.62.ip PART #htviosfdbsjdfsgdfvsjgvfa
	int count = 0;
	for (std::vector<std::string>::iterator it = argument.begin(); it != argument.end(); ++it, count++);
	if (count != 2)
		return Server.sendMsg(Server, Client, ERR_NEEDMOREPARAMS(Server, Client));
	std::vector<std::string> channel_tmp = splitCmdJoin(argument[1]);
	std::vector<std::map<std::string, channel>::iterator> channelsToRemove;

	for (unsigned long i = 0; i < channel_tmp.size(); ++i) {
		if (!Server.getChannelMap().empty()) {
			for (std::map<std::string, channel>::iterator it = Server.getChannelMap().begin(); it != Server.getChannelMap().end(); ++it) {
				if (it->second.getChannelName() == channel_tmp[i]) {
					if(it->second.isAlreadyinChannel(Client) == true) {
						Server.sendMsg(Server, Client, "LEAVE", "You have left the channel " + it->second.getChannelName(), "");
						Server.sendMsgToChannel(Server, Client, Client.getNickname() + " has left the channel. Goodbye!", it->second.getChannelName());
						it->second.unsetChannelUser(Client);
						if (it->second.getChannelUser().empty()) {
							channelsToRemove.push_back(it);
						}

					} else if (channel_tmp[i] == it->second.getChannelName() && it->second.isAlreadyinChannel(Client) == false) {
						Server.sendMsg(Server, Client, ERR_NOTONCHANNEL(Server, Client, it->second.getChannelName())), void();
					}
				}
			}
		}
		if (Server.channelExist(channel_tmp[i]) == false)
			Server.sendMsg(Server, Client, ERR_NOSUCHCHANNEL(Server, Client, channel_tmp[i]));
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
		return Server.sendMsg(Server, Client, ERR_NEEDMOREPARAMS(Server, Client));
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
					Server.sendMsgToChannel(Server, Client, msg, it->second.getChannelName());
				else
					Server.sendMsgToChannel(Server, Client, Client.getNickname() + " has left the channel. Goodbye!", it->second.getChannelName());
				it->second.unsetChannelUser(Client);
				Server.sendMsg(Server, Client, "QUIT", "You have left the channel " + it->second.getChannelName(), "");
				if (it->second.getChannelUser().empty()) {
						channelsToRemove.push_back(it);
				}
			}
		}
	}
	for (std::vector<std::map<std::string, channel>::iterator>::iterator it = channelsToRemove.begin(); it != channelsToRemove.end(); ++it) {
    	Server.getChannelMap().erase(*it);
	}
	Server.sendMsg(Server, Client, "QUIT", "Leaving the server. Goodbye!", "");
	Client.setStatus(DISCONNECTED);
	return;
}
// MSG KICK OK
void	commands::cmdKICK(server& Server, user& Client, std::vector<std::string>& argument){
	int count = 0;
	for (std::vector<std::string>::iterator it = argument.begin(); it != argument.end(); ++it, count++);
	if (count != 3)
		return Server.sendMsg(Server, Client, ERR_NEEDMOREPARAMS(Server, Client));
	for (std::map<std::string, channel>::iterator it = Server.getChannelMap().begin(); it != Server.getChannelMap().end(); ++it) {
		if (it->first == argument[1]){
			if (!(it->second.isAlreadyinChannel(Client)))
				return Server.sendMsg(Server, Client, ERR_USERNOTINCHANNEL(Server, Client, argument[1]));
			if  (!(it->second.isAlreadyinChannel(Server.getClient(argument[2]))))
				return Server.sendMsg(Server, Client, ERR_USERNOTINCHANNEL(Server, Server.getClient(argument[2]), argument[1]));
			if  (it->second.isOperator(Client.getUsername()))
			{
				std::vector<user>::iterator ita = std::find(it->second.getChannelUser().begin(), it->second.getChannelUser().end(), Server.getClient(argument[2]));
				it->second.getChannelUser().erase(ita);
				Server.sendMsgToUser(Server, Client ,Server.getClient(argument[2]), "KICK " + it->second.getChannelName() + " " + Server.getClient(argument[2]).getNickname() + " :" + Client.getNickname());
				Server.sendMsgToUser(Server, Client , Client, "KICK " + it->second.getChannelName() + " " + Server.getClient(argument[2]).getNickname() + " :" + Client.getNickname());
				Server.sendMsgToChannel(Server, Client,"KICK " + it->second.getChannelName() + " " + Server.getClient(argument[2]).getNickname() + " :" + Client.getNickname(), it->second.getChannelName());
				return;
			}
			else
				return Server.sendMsg(Server, Client, ERR_CHANOPRIVSNEEDED(argument[1]));
		}
	}
	return Server.sendMsg(Server, Client, ERR_NOSUCHCHANNEL(Server, Client, argument[1]));
	return;
}

void	commands::cmdINVITE(server& Server, user& Client, std::vector<std::string>& argument){

	int count = 0;
	for (std::vector<std::string>::iterator it = argument.begin(); it != argument.end(); ++it, count++);
	if (count != 3)
		return Server.sendMsg(Server, Client, ERR_NEEDMOREPARAMS(Server, Client));
	if (!Server.userExist(argument[1]))
		return Server.sendMsg(Server, Client, "401", "", argument[1]);
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
				Server.sendMsgToChannel(Server, Client, Client.getNickname() + " his now on the invite list. He can now join at any moment", it->second.getChannelName());
				Server.sendMsg(Server.getClient(argument[1]), Server, "INVITE", "You are now on the invite list of " + it->second.getChannelName(), it->second.getChannelName());
				return;
			}
			else
				return Server.sendMsg(Server, Client, "441", "", argument[1]);
		}
	}
	return Server.sendMsg(Server, Client, "403", "", argument[1]);
}

void	commands::cmdTOPIC(server& Server, user& Client, std::vector<std::string>& argument){

	int count = 0;
	std::string msg;
	for (std::vector<std::string>::iterator it = argument.begin(); it != argument.end(); ++it, count++);
	if (count < 2 || (count > 3 && argument[2][0] != ':'))
		return Server.sendMsg(Server, Client, "", "", "");
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
								Server.sendMsg(Server, Client, "TOPIC", "You have been created a new topic on " + it->second.getChannelName(), "");
								Server.sendMsgToChannel(Server, Client, "A new topic " + msg + " has been created on " + it->second.getChannelName() + " by " + Client.getNickname() + ".", it->second.getChannelName());
							} else
								return Server.sendMsg(Server, Client, ,ERR_CHANOPRIVSNEEDED(it->second.getChannelName()));
						} else {
							it->second.setTopic(msg);
							Server.sendMsg(Server, Client, RPL_NOTOPIC(Server, Client, it->second.getChannelName()));
							Server.sendMsgToChannel(Server, Client, "TOPIC" , "A new topic " + msg + " has been created on " + it->second.getChannelName() + " by " + Client.getNickname() + ".", it->second.getChannelName());
						}
					} else {
							if (!it->second.getTopic().empty())
								Server.sendMsg(Server, Client, RPL_TOPIC(Server, Client, it->second.getChannelName(), it->second.getTopic()));
							else
								Server.sendMsg(Server, Client, RPL_NOTOPIC(Server, Client, it->second.getChannelName()));
					}
				} else
					return Server.sendMsg(Server,Client, ERR_USERNOTINCHANNEL(Server, Client, it->second.getChannelName()));
			}
			if (Server.channelExist(argument[1]) == false)
				Server.sendMsg(Server, Client, ERR_NOSUCHCHANNEL(Server, Client, argument[1]));
		}
	}
	return;
}

void	commands::cmdMODE(server& Server, user& Client, std::vector<std::string>& argument){
	//:nickbb!~unbb@494f-a0a0-544-a020-fae1.210.62.ip MODE #htviosfdbsjdfsgdfvsjgvfa +i 
	std::vector<std::string> arg_mod;
	int count = 0;
	for (std::vector<std::string>::iterator it = argument.begin(); it != argument.end(); ++it, ++count);
	if (count < 3 || (argument[2][0] != '+' && argument[2][0] != '-'))
		return Server.sendMsg(Server, Client, ERR_NEEDMOREPARAMS(Server, Client)), void();
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
						Server.sendMsg(Server, Client, "472", "", "");
						break;

				}
			}
		} else if (argument[1] == it->second.getChannelName() && it->second.isAlreadyinChannel(Client) == false){
			return Server.sendMsg(Server, Client, ERR_NOTONCHANNEL(Client, argument[1])), void();
		} else if (argument[1] == it->second.getChannelName() && it->second.isOperator(Client.getUsername()) == false) {
			return Server.sendMsg(Server, Client, ERR_CHANOPRIVSNEEDED(argument[1])), void();
		} else if (Server.channelExist(argument[1]) == false)
			return Server.sendMsg(Server, Client, ERR_NOSUCHCHANNEL(Server, Client, argument[1]));
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
			return Server.sendMsg(Server, Client, ERR_NORECIPIENT());
		else if (count == 2)
		{
			for(std::map<int, user>::iterator it = Server.getUserMap().begin(); it != Server.getUserMap().end(); ++it)
				if (argument[1] == it->second.getNickname())
					return Server.sendMsg(Server, Client, ERR_NOTEXTTOSEND());
			return Server.sendMsg(Server, Client, ERR_NORECIPIENT());
		}
		else
			return Server.sendMsg(Server, Client, ERR_NEEDMOREPARAMS(Server, Client));
	}
	if (argument[1][0] != '&' && argument[1][0] != '#')
		destination = pvm_USER;
	if (destination == pvm_USER){
		for(std::map<int, user>::iterator it = Server.getUserMap().begin(); it != Server.getUserMap().end(); ++it){
			if (argument[1] == it->second.getNickname())
			{
				for (std::vector<std::string>::iterator it = argument.begin() + 2; it != argument.end(); ++it)
					message += *it + " ";
				Server.sendMsgToUser(Server, Client, it->second, message);
				return;
			}
		}
		return Server.sendMsg(Server, Client, ERR_NOSUCHNICK(argument[1]));
	}
	else
	{
		for (std::vector<std::string>::iterator it = argument.begin() + 2; it != argument.end(); ++it)
			message += *it + " ";
		Server.sendMsgToChannel(Server, Client , message, argument[1]);
	}
	return;
}

void	commands::cmdBOT(server& Server, user& Client, std::vector<std::string>& argument){
	int count = 0;
	(void)Server;
	(void)Client;
	std::string msg;
	for (std::vector<std::string>::iterator it = argument.begin(); it != argument.end(); ++it, count++);
	for(std::map<int, user>::iterator it = Server.getUserMap().begin(); it != Server.getUserMap().end(); ++it){
			std::cout << "USER [" + it->second.getUsername() + "]" << std::endl;
			if (it->second.getUsername() == "rooohbot" ){
				if (count != 2){
					msg = Client.getUsername() + " DFT";
					if (send(it->second.getfd(), msg.c_str(), msg.length(), 0) == -1)
						std::perror("send:");
					return;
				}
				switch (botcmd(argument[1]))
				{
					case HELP:
						msg = Client.getUsername() + " HELP";
						if (send(it->second.getfd(), msg.c_str(), msg.length(), 0) == -1)
						 	std::perror("send:");
						break;

					case FACT:
						msg = Client.getUsername() + " FACT";
						if (send(it->second.getfd(), msg.c_str(), msg.length(), 0) == -1)
						 	std::perror("send:");
						break;
					case HI:
						msg = Client.getUsername() + " HI";
						if (send(it->second.getfd(), msg.c_str(), msg.length(), 0) == -1)
						 	std::perror("send:");
						break;
					case RPS:
						msg = Client.getUsername() + " RPS";
						if (send(it->second.getfd(), msg.c_str(), msg.length(), 0) == -1)
						 	std::perror("send:");
						break;
					default:
						msg = Client.getUsername() + " DFT";
						if (send(it->second.getfd(), msg.c_str(), msg.length(), 0) == -1)
						 	std::perror("send:");
						break;;
				}
				return;
			}
	}
	std::cout << "NOBOT" << std::endl;
}

void 	commands::cmdNAMES(server& Server, user& Client, std::vector<std::string>& argument){

	int count = 0;
	std::ostringstream oss;

	for (std::vector<std::string>::iterator it = argument.begin(); it != argument.end(); ++it, count++);
	switch (count)
	{
		case 1:
			if (Server.getChannelMap().empty())
				return Server.sendMsg(Server, Client, "403", "", "");
			for (std::map<std::string, channel>::iterator ita = Server.getChannelMap().begin(); ita != Server.getChannelMap().end(); ++ita)
			{
					oss << ita->second.getChannelUser().size();
					std::string msg = ita->second.display_mode() + ita->second.getChannelName() + " has " + oss.str() + " user connected :\n";
					for (std::vector<user>::iterator itb = ita->second.getChannelUser().begin(); itb != ita->second.getChannelUser().end(); itb++){
						msg += "\t"+ printOP(itb->getUsername(), ita->second) +" - Nickname : " + itb->getNickname() + " | Username : " + itb->getUsername() + "\n";
					}
					Server.sendMsg(Server, Client,"NAMES",msg ,"");
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
					return Server.sendMsg(Server, Client,"NAMES",msg ,"");
				}
			}
			return Server.sendMsg(Server, Client, "403", "", "");

		default:
			return Server.sendMsg(Server, Client, ERR_NEEDMOREPARAMS(Server, Client));
	}
}
