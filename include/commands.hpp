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

class commands {

	public:
		commands();
		commands(const commands& rhs);
		commands& operator=(const commands& rhs);
		~commands();


	void	getCommand(server& Server, user& Client, std::vector<std::string>& argument);
	void	getAuthentified(server& Server, user& Client, std::vector<std::string>& argument);
	int		isCmdAuthentified(user& Client, std::string argument);

	void cmdPASS(server& Server, user& Client, std::vector<std::string>& argument);
	void cmdNICK(server& Server, user& Client, std::vector<std::string>& argument);
	void cmdUSER(server& Server, user& Client, std::vector<std::string>& argument);
	void cmdQUIT(server& Server, user& Client, std::vector<std::string>& argument);
	void cmdJOIN(server& Server, user& Client, std::vector<std::string>& argument);
	void cmdPART(server& Server, user& Client, std::vector<std::string>& argument);
	void cmdKICK(server& Server, user& Client, std::vector<std::string>& argument);
	void cmdINVITE(server& Server, user& Client, std::vector<std::string>& argument);
	void cmdTOPIC(server& Server, user& Client, std::vector<std::string>& argument);
	void cmdMODE(server& Server, user& Client, std::vector<std::string>& argument);
	void cmdPRIVMSG(server& Server, user& Client, std::vector<std::string>& argument);

	private:
		typedef void (commands::*cmdFunctionPointer)(server& Server, user& Client, std::vector<std::string>& argument);
		std::map<std::string, cmdFunctionPointer> cmdMap;

};

#define COMMANDS_DC "[+] [Default] Constructor called for COMMANDS CLASS"
#define COMMANDS_PC "[+] [Parametric] Constructor called for COMMANDS CLASS"
#define COMMANDS_CC "[x] [Copy] Constructor called for COMMANDS CLASS"
#define COMMANDS_AO "[x] [Attribution] Operator called for COMMANDS CLASS"
#define COMMANDS_DD "[-] [Default] Destructor called for COMMANDS CLASS"
