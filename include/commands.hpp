/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvautrot <mvautrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 16:15:35 by mvautrot          #+#    #+#             */
/*   Updated: 2024/01/11 16:23:31 by mvautrot         ###   ########.fr       */
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
	void cmdPART(server& Server, user& Client, std::vector<std::string>& argument);
	void cmdKICK(server& Server, user& Client, std::vector<std::string>& argument);
	void cmdINVITE(server& Server, user& Client, std::vector<std::string>& argument);
	void cmdTOPIC(server& Server, user& Client, std::vector<std::string>& argument);
	void cmdMODE(server& Server, user& Client, std::vector<std::string>& argument);
	void cmdPRIVMSG(server& Server, user& Client, std::vector<std::string>& argument);
	void cmdBOT(server& Server, user& Client, std::vector<std::string>& argument);


	void cmdJOIN(server& Server, user& Client, std::vector<std::string>& channel_tmp);

	void cmdNAMES(server& Server, user& Client, std::vector<std::string>& argument);
	private:
		typedef void (commands::*cmdFunctionPointer)(server& Server, user& Client, std::vector<std::string>& argument);
		std::map<std::string, cmdFunctionPointer> cmdMap;

};



	int	parseChannelKeyword(server &Server, user &Client, std::vector<std::string>& key_tmp, std::vector<std::string>& channel_tmp);
	int	parseChannelName(server &Server, user &Client, std::vector<std::string>& channel_tmp);
	int	parseCmdJoin(server &Server, user &Client, std::vector<std::string>& argument);
	int	isValidUser(server &Server, user &Client, channel &Channel, std::vector<std::string> key_tmp, int pos);
	void	UserJoinChannel(server &Server, user &Client, channel &Channel);
	std::vector<std::string>	splitCmdJoin(std::string buffer);

	// std::vector<std::string>	splitCmdMode(std::vector<std::string> buffer, int pos);
	int isValidArgMod(char mod);


#define COMMANDS_DC "[+] [Default] Constructor called for COMMANDS CLASS"
#define COMMANDS_PC "[+] [Parametric] Constructor called for COMMANDS CLASS"
#define COMMANDS_CC "[x] [Copy] Constructor called for COMMANDS CLASS"
#define COMMANDS_AO "[x] [Attribution] Operator called for COMMANDS CLASS"
#define COMMANDS_DD "[-] [Default] Destructor called for COMMANDS CLASS"
