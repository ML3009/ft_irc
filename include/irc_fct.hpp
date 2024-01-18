/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc_fct.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purple <purple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 11:28:38 by purple            #+#    #+#             */
/*   Updated: 2024/01/18 14:03:27 by purple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
class user;
class server;
class channel;

/* PARSING */
void	                try_args(int ac, char **av);

/* SIGNAL  */
void	                handle_signal(int signal);

/* DEBUG   */
void	                debug(std::string msg, int type);
void 	                display_constructor(std::string msg);

/* UTILS   */
bool						completeCommand(std::string msg);
std::vector<std::string>	splitArgs(std::string buffer);
std::string					displayRPL(server &server, user &client, std::string RPL, std::string message, std::string channel);
void 						displayWelcome(server &server, user &client);
std::string					printOP(std::string user, channel &channel);
int 						response(int clientSocket);
bool						IsClientFD(const pollfd& pfd, int clientFD);
int                         botcmd(std::string arg);


std::string ERR_NEEDMOREPARAMS(server& server, user& client) ;
std::string ERR_UNKNOWNCOMMAND(std::string cmd) ;
std::string ERR_NORECIPIENT(void); // 411
std::string ERR_NOTEXTTOSEND(void); // 412
/*  RPL    */
std::string RPL_WELCOME(server &server, user &client);
std::string RPL_YOURHOST(server &server, user &client);
std::string RPL_CREATED(server &server, user &client) ;
std::string RPL_MYINFO(server &server, user &client);



struct IsClientFDPredicate {
    int clientFD;

    IsClientFDPredicate(int fd) : clientFD(fd) {}

    bool operator()(const pollfd& pfd) const {
        return pfd.fd == clientFD;
    }
};
