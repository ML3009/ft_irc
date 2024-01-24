/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purple <purple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 17:33:39 by purple            #+#    #+#             */
/*   Updated: 2024/01/24 17:29:17 by purple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "irc.hpp"


class commands;

class channel;

class server;

class user
{
public :
// Coplien
			user();
			user(int fd);
			user(const user& rhs);
			user &operator=(const user& rhs);
			~user();

// Operator
			bool operator==(const user& other) const {
        		return this->getUsername() == other.getUsername();}

// Setter / Getter
			int                 getfd() const;
			std::string 		getNickname() const;
			std::string         getUsername() const;
			std::string 		getRealname() const;
			std::string         getBuffer() const;
			std::string			getPassword() const;
			time_t		 		getLastPing() const;
			char 				*getIP() const;
			bool                getStatus() const;
			bool				getFileStatus() const;
			void 				setQuizzmod(int mod);
			void				setStatus(bool status);
			void				setPassword(std::string password);
			void				setNickname(std::string nickname);
			void				setUsername(std::string username);
			void				setRealname(std::string realname);
			void				setip(char *ip);
// Function
			void				parseClientMessage(server &Server, std::string comd);
			bool				isAuthentified(void);
			void				appendToBuffer(const char *buffer);
			void				clearBuffer();
			void				receive(server &server);
			void				bot_connection(std::vector<std::string> arg, server &server);
			void				bot_message(std::vector<std::string> arg, server &server);
			void				bot_quizz(std::vector<std::string> arg, server &server);
			void				bot_quizzanswer(std::vector<std::string> arg, server &server);
			void 				answertoBot(std::vector<std::string> arg, server &server);

protected :

private :
			std::string         _hostname;
			std::string         _nickname;
			std::string         _username;
			std::string			_realname;
			std::string         _buffer;
			std::string         _password;
			std::string			_bottouser;
			std::string			_bottochannel;
			int 				_messagebot;
			int					_quizzbot;
			int					_quizzanswer;
			int                 _fd;
			time_t				_last_ping;
			bool				_status;
			bool				_quizzmod;
			bool				_fileStatus;
			char *				_client_ip;



};

#define CONNECTED true
#define DISCONNECTED false
#define NONE false
#define FILE yes


#define USER_DC "[+] [Default] Constructor called for USER CLASS"
#define USER_PC "[+] [Parametric] Constructor called for USER CLASS"
#define USER_CC "[x] [Copy] Constructor called for USER CLASS"
#define USER_AO "[x] [Attribution] Operator called for USER CLASS"
#define USER_DD "[-] [Default] Destructor called for USER CLASS"
