/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purple <purple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 16:14:47 by mvautrot          #+#    #+#             */
/*   Updated: 2024/01/04 14:44:04 by purple           ###   ########.fr       */
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


void	commands::getCommand(server Server, user Client, std::vector<std::string>& argument) {

	debug("getCommand", BEGIN);
	std::cout << "getCommand" << std::endl;
	if (!argument.empty()) {
		for (std::map<std::string, cmdFunctionPointer>::iterator it = cmdMap.begin(); it!= cmdMap.end(); ++it) {
			if (it->first == argument[0])
				(this->*(it->second))(Server, Client, argument);
		}
	}
	debug("getCommand", END);

	return;
}

void	commands::getAuthentified(server Server, user Client, std::vector<std::string>& argument) {

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
				std::cout << "\e[0;33m" << "[ You are not connected to the server ]" << " \e[0m" << std::endl;
				if (!(Client.getPassword().empty()))
					std::cout << "\e[0;36m" << "\t[Password] OK" << std::endl;
				else{
					std::cout << "\e[0;36m" << "\tuse /PASS before doing anything" << " \e[0m" << std::endl;
					break;
				}
				!(Client.getUsername().empty()) ? std::cout << "\e[0;36m" << "\t[Username] " << Client.getUsername() << std::endl : std::cout << "\e[0;36m" << "\t[/USER] username must be set" << std::endl;
				!(Client.getNickname().empty()) ? std::cout << "\e[0;36m" << "\t[Nickname] " << Client.getNickname() << std::endl : std::cout << "\e[0;36m" << "\t[/NICK] nickname must be set" << " \e[0m" << std::endl;
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

void	commands::functionPASS(server Server, user Client, std::vector<std::string>& argument){

	(void)Client;
	(void)Server;
	(void)argument;
	int	count = 0;
	for (std::vector<std::string>::iterator it = argument.begin(); it != argument.end(); ++it, ++count){
		std::cout << *it << std::endl;
	}
	if (count != 2) {
		std::cout << "Required two arguments." << std::endl;
		return;
	}


	std::cout << "PASS" << std::endl;
	return;
}
void	commands::functionNICK(server Server, user Client, std::vector<std::string>& argument){

	(void)Server;
	(void)Client;
	(void)argument;
	std::cout << "NICK" << std::endl;

	return;
}
void	commands::functionUSER(server Server, user Client, std::vector<std::string>& argument){

	(void)Server;
	(void)Client;
	(void)argument;
	std::cout << "USER" << std::endl;

	return;
}
void	commands::functionQUIT(server Server, user Client, std::vector<std::string>& argument){

	(void)Server;
	(void)Client;
	(void)argument;
	std::cout << "QUIT" << std::endl;

	return;
}
void	commands::functionJOIN(server Server, user Client, std::vector<std::string>& argument){

	(void)Server;
	(void)Client;
	(void)argument;
	std::cout << "JOIN" << std::endl;

	return;
}
void	commands::functionPART(server Server, user Client, std::vector<std::string>& argument){

	(void)Server;
	(void)Client;
	(void)argument;
	std::cout << "PART" << std::endl;

	return;
}
void	commands::functionKICK(server Server, user Client, std::vector<std::string>& argument){

	(void)Server;
	(void)Client;
	(void)argument;
	std::cout << "KICK" << std::endl;

	return;
}
void	commands::functionINVITE(server Server, user Client, std::vector<std::string>& argument){

	(void)Server;
	(void)Client;
	(void)argument;
	std::cout << "INVITE" << std::endl;

	return;
}
void	commands::functionTOPIC(server Server, user Client, std::vector<std::string>& argument){

	(void)Server;
	(void)Client;
	(void)argument;
	std::cout << "TOPIC" << std::endl;

	return;
}
void	commands::functionMODE(server Server, user Client, std::vector<std::string>& argument){

	(void)Server;
	(void)Client;
	(void)argument;
	std::cout << "MODE" << std::endl;

	return;
}
void	commands::functionPRIVMSG(server Server, user Client, std::vector<std::string>& argument){

	(void)Server;
	(void)Client;
	(void)argument;
	std::cout << "PRIVMSG" << std::endl;

	return;
}

// void commands::sendRPLWelcome(server &Server, user &Client)
// {
// 	"001: Bienvenue sur le serveur IRC. Connecté avec succès !"
// 	"002: Notre serveur hôte IRC est irc.example.com."
// 	"003: Ce serveur a été créé le 1er janvier 2024 à 12h00."
// 	"004: irc.example.com Serveur IRC v1.0. Modes supportés : +i, +t, +n. Utilisez /HELP pour obtenir de l'aide."

// }



/*--------------- Exception ------------- */
