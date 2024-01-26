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


std::vector<std::string> splitArgs(std::string buffer);
void execute(std::vector<std::string> argument);
int botcmd(std::string arg);

std::string sendFact(std::string dest);
std::string startquizz(std::string dest);
std::string saynothing(std::string dest);
std::string helpBot(std::string dest);
std::string sayhello(std::string dest);
std::string reponsetoQuizz();

#define BLK "\033[0;30m"
#define RED "\033[0;31m"
#define GRN "\033[0;32m"
#define YEL "\033[0;33m"
#define BLU "\033[0;34m"
#define MAG "\033[0;35m"
#define CYN "\033[0;36m"
#define WHT "\033[0;37m"
#define COLOR_RESET "\033[0m"


#define HELP 0
#define FACT 1
#define HI 2
#define QUIZZ 3
#define DFT 4

class signalException : public std::exception {
	const char *what() const throw(){
   		return ("\x1b[31m \x1b[3m ctrl+c detected\x1b[0m");}
};