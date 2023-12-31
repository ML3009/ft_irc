/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvautrot <mvautrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 11:01:10 by purple            #+#    #+#             */
/*   Updated: 2024/01/08 16:51:32 by mvautrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "irc.hpp"
#include "user.hpp"
#include "bot.hpp"
class commands;

class channel;

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
			void timeout_client(int fd);
			bool LastPing(user &client);

			void sendMsg(user &client, server &server, std::string RPL);
			void sendrawMsg(user &client, server &server, std::string message);

			void sendMsgToChannel(user &client, std::vector<user> &list, server &server, std::string RPL, std::string message, std::string channel);
			void sendMsgToUser(user &client, user &dest, server &server, std::string RPL, std::string message);
			void sendMsgFromBot(bot &bot, user &dest, server &server, std::string message);

			void sendMsg2(server &Server, user &User, std::string str);
			void	sendJoinMsg(server &Server, user& Client, std::string channelName);
			void	sendUserJoinMsg(server& Server, const user& NewUser, std::string channelName);


// Getter / Setter
			//std::map<int, user> getClientMap();
			int					getUserCount() const;
			std::vector<pollfd> getpollfd();
			std::string			getPassword() const;
			std::string 		getID() const;
			bot 				&getbot();
			std::map<int, user> &getUserMap();
			std::map<std::string, channel> &getChannelMap();

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
			bot					_bot;
			std::map<int, user> 	_clientMap;
			std::map<std::string, channel> _channelMap;

};


#define SERVER_DC "[+] [Default] Constructor called for SERVER CLASS"
#define SERVER_PC "[+] [Parametric] Constructor called for SERVER CLASS"
#define SERVER_CC "[x] [Copy] Constructor called for SERVER CLASS"
#define SERVER_AO "[x] [Attribution] Operator called for SERVER CLASS"
#define SERVER_DD "[-] [Default] Destructor called for SERVER CLASS"
