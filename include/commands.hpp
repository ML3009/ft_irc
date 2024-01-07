/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purple <medpurple@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 16:15:35 by mvautrot          #+#    #+#             */
/*   Updated: 2024/01/07 17:59:27 by purple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "irc.hpp"

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
	void functionBOT(server& Server, user& Client, std::vector<std::string>& argument);

	private:
		typedef void (commands::*cmdFunctionPointer)(server& Server, user& Client, std::vector<std::string>& argument);
		std::map<std::string, cmdFunctionPointer> cmdMap;

};

#define COMMANDS_DC "[+] [Default] Constructor called for COMMANDS CLASS"
#define COMMANDS_PC "[+] [Parametric] Constructor called for COMMANDS CLASS"
#define COMMANDS_CC "[x] [Copy] Constructor called for COMMANDS CLASS"
#define COMMANDS_AO "[x] [Attribution] Operator called for COMMANDS CLASS"
#define COMMANDS_DD "[-] [Default] Destructor called for COMMANDS CLASS"
