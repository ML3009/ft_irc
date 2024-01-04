/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvautrot <mvautrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 11:01:10 by purple            #+#    #+#             */
/*   Updated: 2024/01/04 12:36:31 by mvautrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "irc.hpp"

class commands;

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
			void disconnect_client(user client);
			void closeServerSocket();


// Getter / Setter
			//std::map<int, user> getClientMap();
			int					getUserCount() const;
			std::vector<pollfd> getpollfd();
			std::string			getPassword() const;
			//user& 				getUser(int fd);

// Exception
	protected:

	private:
			int					_port;
			int					_userCount;
			std::string			_password;
			std::vector<pollfd>	_pollFD;


};


#define SERVER_DC "[+] [Default] Constructor called for SERVER CLASS"
#define SERVER_PC "[+] [Parametric] Constructor called for SERVER CLASS"
#define SERVER_CC "[x] [Copy] Constructor called for SERVER CLASS"
#define SERVER_AO "[x] [Attribution] Operator called for SERVER CLASS"
#define SERVER_DD "[-] [Default] Destructor called for SERVER CLASS"
