/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purple <medpurple@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 11:28:44 by purple            #+#    #+#             */
/*   Updated: 2023/12/28 20:22:35 by purple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <csignal>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <cerrno>
#include <cstdio>
#include <sys/socket.h>
#include <sys/types.h>
#include <fcntl.h>
#include <vector>
#include <poll.h>
#include <map>

#include "irc_fct.hpp"
#include "irc_exception.hpp"
#include "server.hpp"
#include "user.hpp"

/* ---- DEBUG AND LOGS ---- */
extern int CONSTRUCTOR; // Display constructor message
extern int DEBUG; // Display debug message
extern int LOG;
#define BEGIN	0
#define END		1
#define YES     1
#define NO      1
#define LOGFILE 1
#define STDOUT  0



extern bool	handleSignal; 