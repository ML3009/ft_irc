/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purple <purple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 17:33:39 by purple            #+#    #+#             */
/*   Updated: 2023/12/28 16:05:01 by purple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "irc.hpp"

class server;

class user
{
public :
// Coplien
            user();
            user(const user& rhs);
            user &operator=(const user& rhs);
            ~user();

// Operator
// Setter / Getter
            user                *getUser(int fd, server &server);
// Function
protected :

private :
    		void 				_display_constructor(std::string msg);
            std::string         _hostname;
            std::string         _nickname;
            std::string         _username;
            std::string         _realname;
            std::string         _buffer;
            std::string         _password;

            
            
};


#define USER_DC "[+] [Default] Constructor called for USER CLASS"
#define USER_PC "[+] [Parametric] Constructor called for USER CLASS"
#define USER_CC "[x] [Copy] Constructor called for USER CLASS"
#define USER_AO "[x] [Attribution] Operator called for USER CLASS"
#define USER_DD "[-] [Default] Destructor called for USER CLASS"