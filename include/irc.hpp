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

#include "irc_fct.hpp"
#include "irc_exception.hpp"
#include "server.hpp"

static bool msg_const = false;

extern bool	handleSignal;
