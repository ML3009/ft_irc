/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purple <purple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 11:28:44 by purple            #+#    #+#             */
/*   Updated: 2024/01/02 13:47:25 by purple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once


#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <csignal>
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cerrno>
#include <vector>
#include <map>
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

/* ---- DEBUG AND LOGS ---- */
extern int CONSTRUCTOR; // Display constructor message
extern int DEBUG; // Display debug message
extern int LOG;
extern std::map<int, user> clientMap;


#define BEGIN	0
#define END		1
#define YES     1
#define NO      -1
#define LOGFILE 1
#define STDOUT  0
#define COMPLETE true
#define INCOMPLETE false



extern bool	handleSignal; 