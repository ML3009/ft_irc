/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvautrot <mvautrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/01/17 11:04:53 by mvautrot         ###   ########.fr       */
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
#include <set>
#include <algorithm>
#include <limits>
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
#include "bot.hpp"

/* ---- DEBUG AND LOGS ---- */
extern int					CONSTRUCTOR; // Display constructor message
extern int					DEBUG; // Display debug message
extern int					LOG;
extern bool					handleSignal;
// extern std::map<std::string, channel> channelMap;


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
#define CAP_LS 3 //irssi
#define QUIT 4 //quit

#define JOIN 5 //rejoindre un channel
#define PART 6 //quitter un channel
#define KICK 7
#define INVITE 8
#define TOPIC 9
#define MODE 10
#define PRIVMSG 11

#define USR_IN_CHANNEL 0
#define CHANNELISFULL 1
#define INVITEONLYCHAN 2
#define BADCHANNELKEY 3
#define ISVALIDUSER 4

#define MODE_I 0
#define MODE_T 1
#define MODE_O 2
#define MODE_K 3
#define MODE_L 4
#define UNKNOW_MODE 5

#define TOPIC_NEED_NOOP 0
#define TOPIC_NEED_OP 1
#define TOPIC_NONEED 2
#define TOPIC_NOUSER 3

#define RPL_JOIN_C 10
#define RPL_NICK_C 11
#define RPL_QUIT_C 12
#define RPL_QUIT_M_C 13
#define RPL_KICK_C 14
#define RPL_NOTICE_C 15
#define RPL_PRIVMSG_C 16

#define ACCEPTED 1
#define DECLINED -1

#define pvm_CHANNEL 1
#define pvm_USER    2

#define BLK "\e[0;30m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define BLU "\e[0;34m"
#define MAG "\e[0;35m"
#define CYN "\e[0;36m"
#define WHT "\e[0;37m"
#define COLOR_RESET "\e[0m"
