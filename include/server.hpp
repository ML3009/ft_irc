/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purple <purple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 11:01:10 by purple            #+#    #+#             */
/*   Updated: 2023/12/28 16:30:01 by purple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "irc.hpp"

class user;

class server{
	public:
// Coplien
			server();
			server(int port, std::string password);
			server(const server& rhs);
			server& operator=(const server& rhs);
			~server();

// Fonction
			void init_server(void);
			void run_server(void);
			void getNewClient(void);
			void getClientMessage(void);

// Getter / Setter
			std::map<int, user> getClient();
// Exception
	protected:

	private:
			int					_port;
			int					_userCount;
			std::string			_password;
			std::vector<pollfd>	_pollFD;
			std::map<int, user> _client;
			
			void 				_display_constructor(std::string msg);
};


#define SERVER_DC "[+] [Default] Constructor called for SERVER CLASS"
#define SERVER_PC "[+] [Parametric] Constructor called for SERVER CLASS"
#define SERVER_CC "[x] [Copy] Constructor called for SERVER CLASS"
#define SERVER_AO "[x] [Attribution] Operator called for SERVER CLASS"
#define SERVER_DD "[-] [Default] Destructor called for SERVER CLASS"