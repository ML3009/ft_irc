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

#include "irc_fct.hpp"
#include "irc_exception.hpp"
#include "server.hpp"
#include "user.hpp"


extern bool CONSTRUCTOR; // Display constructor message
extern bool DEBUG; // Display debug message

extern bool	handleSignal; 
