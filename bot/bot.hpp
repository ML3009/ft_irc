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
#include <stdexcept>
extern bool					handleSignalbot;


class bot {

	public:
		bot();
		bot(const bot& rhs);
		bot& operator=(const bot& rhs);
		~bot();

		void execute(std::vector<std::string> argument);
		int botcmd(std::string arg);

		std::string sendFact(std::string dest);
		std::string startquizz(std::string dest);
		std::string saynothing(std::string dest);
		std::string helpBot(std::string dest);
		std::string sayhello(std::string dest);
		std::string reponsetoQuizz();

		// Getters
		bool getQuizzOn() const;
		int getQuizzUser() const;
		int getServerfd() const;
		int getQuestion() const;
		int getClientSocket() const;
		const char* getServerIP() const;
		int getServerPort() const;
		const std::vector<std::string>& getQuizzAnswer() const;
		const std::string& getQuizzdest() const;
		const sockaddr_in& getServerAddress() const;

		// Setters
		void setQuizzOn(bool value);
		void setQuizzUser(int value);
		void setServerfd(int value);
		void setQuestion(int value);
		void setClientSocket(int value);
		void setServerIP(const char* value);
		void setServerPort(int value);
		void setQuizzAnswer(const std::vector<std::string>& value);
		void setQuizzdest(const std::string& value);
		void setServerAddress(const sockaddr_in& value);

		class socketException : public std::exception {
			const char *what() const throw(){
   				return ("\x1b[31m \x1b[3m socket error \x1b[0m");}};
		class connectionException : public std::exception {
			const char *what() const throw(){
   				return ("\x1b[31m \x1b[3m connection error \x1b[0m");}};
		class sendException : public std::exception {
			const char *what() const throw(){
   				return ("\x1b[31m \x1b[3m send error \x1b[0m");}};

	private:
		bool 						_quizz_on;
		int  						_quizzUser;
		int  						_serverfd;
		int  						_question;
		int 						_clientSocket;
		const char*	 				_serverIP;
		int							_serverPort;
		std::vector<std::string> 	_quizzAnswer;
		std::string 				_quizzdest;
		struct sockaddr_in 			_serverAddress;
};


std::vector<std::string> splitArgs(std::string buffer);
void	handle_signal(int signal);

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
