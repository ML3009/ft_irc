/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purple <purple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 16:15:35 by mvautrot          #+#    #+#             */
/*   Updated: 2024/01/04 17:23:38 by purple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "irc.hpp"

#pragma once

#include <iostream>
#include <string>

class commands {

	public:
		commands();
		commands(const commands& rhs);
		commands& operator=(const commands& rhs);
		~commands();


	void	getCommand(server& Server, user& Client, std::vector<std::string>& argument);
	void	getAuthentified(server& Server, user& Client, std::vector<std::string>& argument);
	int		isCmdAuthentified(user& Client, std::string argument);

	void functionPASS(server& Server, user& Client, std::vector<std::string>& argument);
	void functionNICK(server& Server, user& Client, std::vector<std::string>& argument);
	void functionUSER(server& Server, user& Client, std::vector<std::string>& argument);
	void functionQUIT(server& Server, user& Client, std::vector<std::string>& argument);
	void functionJOIN(server& Server, user& Client, std::vector<std::string>& argument);
	void functionPART(server& Server, user& Client, std::vector<std::string>& argument);
	void functionKICK(server& Server, user& Client, std::vector<std::string>& argument);
	void functionINVITE(server& Server, user& Client, std::vector<std::string>& argument);
	void functionTOPIC(server& Server, user& Client, std::vector<std::string>& argument);
	void functionMODE(server& Server, user& Client, std::vector<std::string>& argument);
	void functionPRIVMSG(server& Server, user& Client, std::vector<std::string>& argument);

	private:
		typedef void (commands::*cmdFunctionPointer)(server& Server, user& Client, std::vector<std::string>& argument);
		std::map<std::string, cmdFunctionPointer> cmdMap;

/*std::string strComp[4] = {"PASS", "NICK", "USER", "QUIT", "JOIN", "PART", "KICK", "INVITE", "TOPIC", "MODE", "PRIVMSG", "PING", "PONG"};
    void (Harl::*ptrString[4])() = {&Harl::debug, &Harl::info, &Harl::warning, &Harl::error};
*/


};



// entrer parsing. avt faire cmd il faut que qd un utilisateur arrive sur le serveur la premiere cmd a faire c est pass une fios qu il
// a fait pass il faut qu il change le nick l username
// 1ere chose : PASS VALID, ensuite un NICK et un USER. Tant que ces 3 ne sont pas valide tu ne peux pas faire autre chose.


#define COMMANDS_DC "[+] [Default] Constructor called for COMMANDS CLASS"
#define COMMANDS_PC "[+] [Parametric] Constructor called for COMMANDS CLASS"
#define COMMANDS_CC "[x] [Copy] Constructor called for COMMANDS CLASS"
#define COMMANDS_AO "[x] [Attribution] Operator called for COMMANDS CLASS"
#define COMMANDS_DD "[-] [Default] Destructor called for COMMANDS CLASS"
