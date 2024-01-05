/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purple <purple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 11:01:10 by purple            #+#    #+#             */
/*   Updated: 2024/01/04 16:26:42 by purple           ###   ########.fr       */
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
			void timeout_client(int fd);
			bool LastPing(user client);
			void sendMsg(user &client, server &server, std::string RPL);
			void sendMsg2(server &Server, user &User, std::string str);

			void	sendJoinMsg(server &Server, user& Client, std::string channelName);
			void	sendUserJoinMsg(server& Server, const user& NewUser, std::string channelName);


// Getter / Setter
			//std::map<int, user> getClientMap();
			int					getUserCount() const;
			std::vector<pollfd> getpollfd();
			std::string			getPassword() const;
			std::string 		getID() const;
			//user& 				getUser(int fd);

// Exception
	protected:

	private:
			int					_port;
			int					_userCount;
			std::string			_password;
			std::string			_ID;
			std::vector<pollfd>	_pollFD;
			clock_t				_upTime;
			clock_t				_maxtimeout;


};


#define SERVER_DC "[+] [Default] Constructor called for SERVER CLASS"
#define SERVER_PC "[+] [Parametric] Constructor called for SERVER CLASS"
#define SERVER_CC "[x] [Copy] Constructor called for SERVER CLASS"
#define SERVER_AO "[x] [Attribution] Operator called for SERVER CLASS"
#define SERVER_DD "[-] [Default] Destructor called for SERVER CLASS"
