/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purple <medpurple@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 11:28:44 by purple            #+#    #+#             */
/*   Updated: 2024/01/05 22:32:13 by purple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <csignal>
#include <ctime>
#include <cerrno>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <fcntl.h>
#include <poll.h>


#include "irc_fct.hpp"
#include "irc_exception.hpp"
#include "server.hpp"
#include "user.hpp"
#include "commands.hpp"
#include "channel.hpp"

/* ---- DEBUG AND LOGS ---- */
extern int					CONSTRUCTOR; // Display constructor message
extern int					DEBUG; // Display debug message
extern int					LOG;
extern bool					handleSignal;
extern std::map<int, user> 	clientMap;
extern std::map<channel, std::vector<user> > channelMap;


#define HERE	-1
#define BEGIN	0
#define END		1
#define YES     1
#define NO      -1
#define LOGFILE 1
#define STDOUT  0

#define COMPLETE true
#define INCOMPLETE false

#define TIMEOUT true
#define TIMEIN	false

#define PASS 0 //authentifier
#define NICK 1 //nickname
#define USER 2 //user
#define QUIT 3 //quit

#define JOIN 4 //rejoindre un channel
#define PART 5 //quitter un channel
#define KICK 6
#define INVITE 7
#define TOPIC 8
#define MODE 9

#define PRIVMSG 10

#define PING 11
#define PONG 12

#define PASS 0 //authentifier
#define NICK 1 //nickname
#define USER 2 //user
#define QUIT 3 //quit

#define JOIN 4 //rejoindre un channel
#define PART 5 //quitter un channel
#define KICK 6
#define INVITE 7
#define TOPIC 8
#define MODE 9

#define PRIVMSG 10

#define PING 11
#define PONG 12


#define RPL_JOIN_C 10;
#define RPL_NICK_C 11;
#define RPL_QUIT_C 12;
#define RPL_QUIT_M_C 13;
#define RPL_KICK_C 14;
#define RPL_NOTICE_C 15;
#define RPL_PRIVMSG_C 16;