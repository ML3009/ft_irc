#pragma once

#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>

#ifdef __APPLE__
#include <fcntl.h>
#else
#include <unistd.h>
#endif

#include "irc_fct.hpp"


class NumberArgException : public std::exception {
	const char *what() const throw(){
   		return ("\x1b[31m \x1b[3m Usage : ./ircserv <port> <password> \x1b[0m");}
};

class TypeArgException : public std::exception {
	const char *what() const throw(){
    	return ("\x1b[31m \x1b[3m Error: port must be included between 1 and 65535. \x1b[0m");}
};
