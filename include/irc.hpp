/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purple <purple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 11:28:44 by purple            #+#    #+#             */
/*   Updated: 2023/12/28 12:55:21 by purple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>
#include <iomanip>
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


extern bool CONSTRUCTOR; // Display constructor message
extern bool DEBUG; // Display debug message
extern bool	handleSignal; 

#define BEGIN	0
#define END		1
