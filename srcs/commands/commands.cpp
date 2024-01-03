/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvautrot <mvautrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 16:14:47 by mvautrot          #+#    #+#             */
/*   Updated: 2024/01/03 16:05:39 by mvautrot         ###   ########.fr       */
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
	cmdMap["/PING"] = &commands::functionPING;
	cmdMap["/PONG"] = &commands::functionPONG;
	cmdMap["/PRIVMSG"] = &commands::functionPRIVMSG;
	cmdMap["/QUIT"] = &commands::functionQUIT;
	cmdMap["/TOPIC"] = &commands::functionTOPIC;
	cmdMap["/USER"] = &commands::functionUSER;
}

commands::commands(const commands& rhs){
	(void)rhs;

}

commands& commands::operator=(const commands& rhs){
	if(this != &rhs)
	{
		(void)rhs;
	}

	return *this;
}

commands::~commands(){

}


/*---------------- Operator ------------- */




/*---------- Getter / Setter ------------ */




/*--------------- Function -------------- */


void	commands::getCommand(server Server, user Client, std::vector<std::string> argument) {

	debug("getCommand", BEGIN);
	(void)Client;
	(void)Server;
	std::cout << "getCommand" << std::endl;
	if (!argument.empty()) {
		for (std::map<std::string, cmdFunctionPointer>::iterator it = cmdMap.begin(); it!= cmdMap.end(); ++it) {
			if (it->first == argument[0]) {
				std::cout << "getCommand, it->first : ";
				std::cout << it->first << std::endl;
			}

		}
	}
	debug("getCommand", END);

	return;
}

void	commands::getAuthentified(server Server, user Client, std::vector<std::string> argument) {

	debug("getAuthentified", BEGIN);
	int cmd = isCmdAuthentified(Client, argument[0]);
    if (!argument.empty()) {
		switch (cmd) {
			case PASS:
				getCommand(Server, Client, argument);
				break;
			case USER:
				getCommand(Server, Client, argument);
				break;
			case NICK:
				getCommand(Server, Client, argument);
				break;
			default:
				std::cout << "Command not found" << std::endl;
		}
	}
	debug("getAuthentified", END);
	return;
}

int	commands::isCmdAuthentified(user Client, std::string argument){
	if (!argument.empty()) {
		if (Client.getPassword().empty() && argument == "/PASS")
			return 0;
		else if (!Client.getPassword().empty()){
			std::string cmd[2] = {"/NICK", "/USER"};
			for(int i = 1; i < 3; i++)
				if (argument == cmd[i])
					return i;
		}
	}
   return -1;
}

void	commands::functionPASS(server Server, user Client, std::vector<std::string> argument){

	(void)Client;
	(void)Server;
	(void)argument;
	std::cout << "PASS" << std::endl;

	return;
}
void	commands::functionNICK(server Server, user Client, std::vector<std::string> argument){

	(void)Server;
	(void)Client;
	(void)argument;
	std::cout << "NICK" << std::endl;

	return;
}
void	commands::functionUSER(server Server, user Client, std::vector<std::string> argument){

	(void)Server;
	(void)Client;
	(void)argument;
	std::cout << "USER" << std::endl;

	return;
}
void	commands::functionQUIT(server Server, user Client, std::vector<std::string> argument){

	(void)Server;
	(void)Client;
	(void)argument;
	std::cout << "QUIT" << std::endl;

	return;
}
void	commands::functionJOIN(server Server, user Client, std::vector<std::string> argument){

	(void)Server;
	(void)Client;
	(void)argument;
	std::cout << "JOIN" << std::endl;

	return;
}
void	commands::functionPART(server Server, user Client, std::vector<std::string> argument){

	(void)Server;
	(void)Client;
	(void)argument;
	std::cout << "PART" << std::endl;

	return;
}
void	commands::functionKICK(server Server, user Client, std::vector<std::string> argument){

	(void)Server;
	(void)Client;
	(void)argument;
	std::cout << "KICK" << std::endl;

	return;
}
void	commands::functionINVITE(server Server, user Client, std::vector<std::string> argument){

	(void)Server;
	(void)Client;
	(void)argument;
	std::cout << "INVITE" << std::endl;

	return;
}
void	commands::functionTOPIC(server Server, user Client, std::vector<std::string> argument){

	(void)Server;
	(void)Client;
	(void)argument;
	std::cout << "TOPIC" << std::endl;

	return;
}
void	commands::functionMODE(server Server, user Client, std::vector<std::string> argument){

	(void)Server;
	(void)Client;
	(void)argument;
	std::cout << "MODE" << std::endl;

	return;
}
void	commands::functionPRIVMSG(server Server, user Client, std::vector<std::string> argument){

	(void)Server;
	(void)Client;
	(void)argument;
	std::cout << "PRIVMSG" << std::endl;

	return;
}
void	commands::functionPING(server Server, user Client, std::vector<std::string> argument){

	(void)Server;
	(void)Client;
	(void)argument;
	std::cout << "PING" << std::endl;

	return;
}

void	commands::functionPONG(server Server, user Client, std::vector<std::string> argument){

	(void)Server;
	(void)Client;
	(void)argument;
	std::cout << "PONG" << std::endl;

	return;
}



/*--------------- Exception ------------- */
