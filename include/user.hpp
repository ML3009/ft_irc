/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purple <medpurple@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 17:33:39 by purple            #+#    #+#             */
/*   Updated: 2024/01/06 14:16:14 by purple           ###   ########.fr       */
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
// Setter / Getter
			int                 getfd() const;
			std::string 		getNickname() const;
			std::string         getUsername() const;
			std::string 		getRealname() const;
			std::string         getBuffer() const;
			std::string			getPassword() const;
			clock_t		 		getLastPing() const;

			void				setPassword(std::string password);
			void				setNickname(std::string nickname);
			void				setUsername(std::string username);
			void				setRealname(std::string realname);
// Function
			void				parseClientMessage(server Server, const std::string &buffer);
			bool				isAuthentified(void);
			void				addData(const std::string &buffer);


protected :

private :
			std::string         _hostname;
			std::string         _nickname;
			std::string         _username;
			std::string			_realname;
			std::string         _buffer;
			std::string         _password;
			int                 _fd;
			clock_t				_last_ping;



};


#define USER_DC "[+] [Default] Constructor called for USER CLASS"
#define USER_PC "[+] [Parametric] Constructor called for USER CLASS"
#define USER_CC "[x] [Copy] Constructor called for USER CLASS"
#define USER_AO "[x] [Attribution] Operator called for USER CLASS"
#define USER_DD "[-] [Default] Destructor called for USER CLASS"
