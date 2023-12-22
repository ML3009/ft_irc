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

extern bool msg_const;

extern bool	handleSignal;
