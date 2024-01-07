/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc_fct.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purple <medpurple@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 11:28:38 by purple            #+#    #+#             */
/*   Updated: 2024/01/07 18:04:28 by purple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
class user;
class server;

/* PARSING */
void	                try_args(int ac, char **av);

/* SIGNAL  */
void	                handle_signal(int signal);

/* DEBUG   */
void	                debug(std::string msg, int type);
void 	                display_constructor(std::string msg);

/* UTILS   */
bool						completeCommand(std::string msg, int opt);
std::vector<std::string>	splitArgs(std::string buffer);
std::string					displayRPL(server &server, user &client, std::string RPL, std::string message);
void displayWelcome(server &server, user &client);


/*  RPL    */
std::string RPL_WELCOME(server &server, user &client);
std::string RPL_YOURHOST(server &server, user &client);
std::string RPL_CREATED(server &server, user &client) ;
std::string RPL_MYINFO(server &server, user &client);
std::string RPL_UMODEIS(server& server, user& client, const std::string& mode) ;
std::string RPL_LISTSTART(server& server, user& client) ;
std::string RPL_LIST(server& server, user& client, const std::string& channel, const std::string& nb, const std::string& topic) ;
std::string RPL_LISTEND(server& server, user& client) ;
std::string RPL_CHANNELMODEIS(server& server, user& client, const std::string& channel, const std::string& mode) ;
std::string RPL_NOTOPIC(server& server, user& client, const std::string& channel) ;
std::string RPL_TOPIC(server& server, user& client, const std::string& channel, const std::string& topic) ;
std::string RPL_NAMREPLY(server& server, user& client, const std::string& channel, const std::string& users) ;
std::string RPL_ENDOFNAMES(server& server, user& client, const std::string& channel) ;
std::string ERR_NOSUCHNICK(server& server, user& client); // 401
std::string ERR_NOSUCHCHANNEL(server& server, user& client, const std::string& channel) ;
std::string ERR_CANNOTSENDTOCHAN(server& server, user& client) ; //404
std::string ERR_TOOMANYCHANNELS(server& server, user& client, const std::string& channel) ;
std::string ERR_TOOMANYTARGETS(server& server, user& client, const std::string& channel) ;
std::string ERR_NORECIPIENT(server& server, user& client, const std::string& message) ;
std::string ERR_NOTEXTTOSEND(server& server, user& client) ;
std::string ERR_NOTOPLEVEL(server& server, user& client, const std::string& message) ;
std::string ERR_WILDTOPLEVEL(server& server, user& client, const std::string& message) ;
std::string ERR_UNKNOWNCOMMAND(server& server, user& client) ;
std::string ERR_NONICKNAMEGIVEN(server& server, user& client) ;
std::string ERR_ERRONEUSNICKNAME(server& server, user& client, const std::string& nickname) ;
std::string ERR_NICKNAMEINUSE(server& server, user& client, const std::string& nickname) ;
std::string ERR_USERNOTINCHANNEL(server& server, user& client, const std::string& user, const std::string& channel) ;
std::string ERR_NOTONCHANNEL(server& server, user& client, const std::string& channel) ;
std::string ERR_NOTREGISTERED(server& server, user& client) ;
std::string ERR_NEEDMOREPARAMS(server& server, user& client) ;
std::string ERR_ALREADYREGISTRED(server& server, user& client) ;
std::string ERR_PASSWDMISMATCH(server& server, user& client) ;
std::string ERR_NOLOGIN(server& server, user& client) ;
std::string ERR_UNKNOWNMODE(server& server, user& client, const std::string& mode) ;
std::string ERR_INVITEONLYCHAN(server& server, user& client, const std::string& channel) ;
std::string ERR_BADCHANMASK(server& server, user& client, const std::string& channel);
std::string ERR_CHANOPRIVSNEEDED(server& server, user& client, const std::string& channel) ;
std::string ERR_USERSDONTMATCH(server& server, user& client) ;
std::string RPL_JOIN(server& server, user& client, const std::string& channel) ;
std::string RPL_NICK(server& server, user& client, const std::string& oldnick, const std::string& newnick) ;
std::string RPL_QUIT(server& server, user& client) ;
std::string RPL_QUIT_M(server& server, user& client, const std::string& message) ;
std::string RPL_KICK(server& server, user& client, const std::string& channel, const std::string& user, const std::string& message) ;
std::string RPL_NOTICE(server& server, user& client, const std::string& channel, const std::string& message) ;
std::string RPL_PRIVMSG(const std::string& message);
std::string HI_BOT(const std::string& message);


