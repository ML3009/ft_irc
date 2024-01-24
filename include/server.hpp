/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purple <purple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 11:01:10 by purple            #+#    #+#             */
/*   Updated: 2024/01/24 17:20:17 by purple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "irc.hpp"
#include "user.hpp"
#include "channel.hpp"
class commands;

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
			void disconnect_client(user &client);
			void closeServerSocket();
			void timeout_client(user &client);
			bool LastPing(user &client);
			bool channelExist(std::string channelName);
			bool userExist(std::string name);
			void sendMsg(server &server, user &client, std::string message);
			void sendrawMsg(user &client, server &server, std::string message);

			void sendMsgToChannel(server &server, user &client, std::string message, std::string canal);
			void sendMsgToUser(server &server, user &client, user &dest, std::string message);

// Getter / Setter
			//std::map<int, user> getClientMap();
			int					getUserCount() const;
			int					getBotCount() const;
			std::vector<pollfd> getpollfd();
			std::string			getPassword() const;
			std::string 		getID() const;
			std::string			getToken() const;
			std::map<int, user> &getUserMap();
			std::map<std::string, channel> &getChannelMap();
			user 				&getClient(std::string name);
			bool 				getIrssi() const;
			void				setIrssi(bool irssi);

			void				setBotOn();

			//user& 				getUser(int fd);


// Exception
	protected:

	private:
			struct	sockaddr_in _serverAdress;
			int					_port;
			int					_userCount;
			std::string			_password;
			std::string			_ID;
			std::vector<pollfd>	_pollFD;
			time_t				_upTime;
			time_t				_maxtimeout;
			std::map<int, user> 	_clientMap;
			std::map<std::string, channel> _channelMap;
			std::string			_botToken;
			int 				_botCount;
			bool 				_irssi;

};


#define SERVER_DC "[+] [Default] Constructor called for SERVER CLASS"
#define SERVER_PC "[+] [Parametric] Constructor called for SERVER CLASS"
#define SERVER_CC "[x] [Copy] Constructor called for SERVER CLASS"
#define SERVER_AO "[x] [Attribution] Operator called for SERVER CLASS"
#define SERVER_DD "[-] [Default] Destructor called for SERVER CLASS"
