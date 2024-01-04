/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPL.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purple <purple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 14:50:00 by purple            #+#    #+#             */
/*   Updated: 2024/01/04 17:21:59 by purple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"


// void initializeRPLFunctions() {
//     RPLFunctions["322"] = &RPL_LIST;
//     RPLFunctions["321"] = &RPL_LISTSTART;
//     RPLFunctions["323"] = &RPL_LISTEND;
//     RPLFunctions["332"] = &RPL_TOPIC;
//     RPLFunctions["331"] = &RPL_NOTOPIC;
//     RPLFunctions["353"] = &RPL_NAMREPLY;
//     RPLFunctions["366"] = &RPL_ENDOFNAMES;
//     RPLFunctions["366"] = &RPL_JOIN;
//     RPLFunctions["401"] = &ERR_NOSUCHNICK;
//     RPLFunctions["402"] = &ERR_NOSUCHNICK;
//     RPLFunctions["403"] = &ERR_NOSUCHCHANNEL;
//     RPLFunctions["404"] = &ERR_CANNOTSENDTOCHAN;
//     RPLFunctions["405"] = &ERR_TOOMANYCHANNELS;
//     RPLFunctions["411"] = &ERR_NORECIPIENT;
//     RPLFunctions["412"] = &ERR_NOTEXTTOSEND;
//     RPLFunctions["413"] = &ERR_NOTOPLEVEL;
//     RPLFunctions["414"] = &ERR_WILDTOPLEVEL;
//     RPLFunctions["421"] = &ERR_UNKNOWNCOMMAND;
//     RPLFunctions["431"] = &ERR_NONICKNAMEGIVEN;
//     RPLFunctions["432"] = &ERR_ERRONEUSNICKNAME;
//     RPLFunctions["433"] = &ERR_NICKNAMEINUSE;
//     RPLFunctions["441"] = &ERR_USERNOTINCHANNEL;
//     RPLFunctions["442"] = &ERR_NOTONCHANNEL;
//     RPLFunctions["451"] = &ERR_NOTREGISTERED;
//     RPLFunctions["461"] = &ERR_NEEDMOREPARAMS;
//     RPLFunctions["462"] = &ERR_ALREADYREGISTRED;
//     RPLFunctions["464"] = &ERR_PASSWDMISMATCH;
//     RPLFunctions["465"] = &ERR_NOLOGIN;
//     RPLFunctions["472"] = &ERR_UNKNOWNMODE;
//     RPLFunctions["473"] = &ERR_INVITEONLYCHAN;
//     RPLFunctions["502"] = &ERR_USERSDONTMATCH;
// }


std::string displayRPL(server &server, user &client, std::string RPL){
	(void)server;
	(void)client;

	return RPL;
}

void displayWelcome(server &server, user &client){
	server.sendMsg(client, server, "01");
	server.sendMsg(client, server, "02");
	server.sendMsg(client, server, "03");
	server.sendMsg(client, server, "04");
}

std::string RPL_WELCOME(server &server, user &client){
	(void)server;
	(void)client;
	return "Bienvenue sur le serveur IRC. Connecté avec succès !";
}

std::string RPL_YOURHOST(server &server, user &client){
	(void)client;
	return "Notre serveur hôte IRC est " + server.getID();
}

std::string RPL_CREATED() {
    std::time_t now = std::time(NULL);
    std::tm* localTime = std::localtime(&now);

    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "Ce serveur a été créé le %d %B %Y à %H:%M:%S.", localTime);
    
    return buffer;
}

std::string RPL_MYINFO(server &server, user &client){
	(void)client;
	return server.getID() + " Serveur IRC v1.0. Modes supportés : +i, +t, +k, +o, +l. Utilisez /HELP pour obtenir de l'aide.";
}

/*---------------------------------------------------------------------------------------------------*/

// std::string ERR_NONICKNAMEGIVEN(server& server, user& client) {
//     (void)server;
//     (void)client;
//     return "431 :No nickname given";
// }

// std::string ERR_USERNOTINCHANNEL(server& server, user& client, const std::string& user, const std::string& channel) {
//     (void)server;
//     (void)client;
//     return "441 " + user + " " + channel + " :They aren't on that channel";
// }

// std::string ERR_NOTONCHANNEL(server& server, user& client, const std::string& channel) {
//     (void)server;
//     (void)client;
//     return "442 " + client.nickname + " " + channel + " :You're not on that channel";
// }

// std::string ERR_USERSDONTMATCH(server& server, user& client) {
//     (void)server;
//     (void)client;
//     return "502 " + client.nickname + " :Can't change mode for other users";
// }

std::string RPL_UMODEIS(server& server, user& client, const std::string& mode) {
    (void)server;
    (void)client;
    return "221 " + mode;
}

std::string RPL_LISTSTART(server& server, user& client) {
    (void)server;
    (void)client;
    return "321 Channel :users Name";
}
std::string RPL_LIST(server& server, user& client, const std::string& channel, const std::string& nb, const std::string& topic) {
    (void)server;
    (void)client;
    return "322 " + channel + " " + nb + " :" + topic;
}

std::string RPL_LISTEND(server& server, user& client) {
    (void)server;
    (void)client;
    return "323 :End of /LIST";
}

std::string RPL_CHANNELMODEIS(server& server, user& client, const std::string& channel, const std::string& mode) {
    (void)server;
    (void)client;
    return "324 " + channel + " " + mode;
}

std::string RPL_NOTOPIC(server& server, user& client, const std::string& channel) {
    (void)server;
    (void)client;
    return "331  " + channel + " :No topic is set";
}

std::string RPL_TOPIC(server& server, user& client, const std::string& channel, const std::string& topic) {
    (void)server;
    (void)client;
    return "332  " + channel + " :" + topic;
}


std::string RPL_NAMREPLY(server& server, user& client, const std::string& channel, const std::string& users) {
    (void)server;
    (void)client;
    return "353  = " + channel + " :" + users;
}

std::string RPL_ENDOFNAMES(server& server, user& client, const std::string& channel) {
    (void)server;
    (void)client;
    return "366  " + channel + " :End of /NAMES list";
}

std::string ERR_NOSUCHNICK(server& server, user& client, const std::string& user_nick, const std::string& dest_nick) {
    (void)server;
    (void)client;
    return "401 " + user_nick + " " + dest_nick + " :No such nick/channel";
}

std::string ERR_NOSUCHCHANNEL(server& server, user& client, const std::string& channel) {
    (void)server;
    (void)client;
    return "403  " + channel + " :No such channel";
}


std::string ERR_CANNOTSENDTOCHAN(server& server, user& client, const std::string& channel) {
    (void)server;
    (void)client;
    return "404 " + channel + " :Cannot send to channel";
}
std::string ERR_TOOMANYCHANNELS(server& server, user& client, const std::string& channel) {
    (void)server;
    (void)client;
    return "405  " + channel + " :You have joined too many channels";
}

std::string ERR_NORECIPIENT(server& server, user& client, const std::string& message) {
    (void)server;
    (void)client;
    return "411 " + message + " :No recipient given";
}

std::string ERR_WILDTOPLEVEL(server& server, user& client, const std::string& message) {
    (void)server;
    (void)client;
    return "414 " + message + " :Wildcard in toplevel domain";
}


std::string ERR_NOTEXTTOSEND(server& server, user& client) {
    (void)server;
    (void)client;
    return "412 :No text to send";
}

std::string ERR_NOTOPLEVEL(server& server, user& client, const std::string& message) {
    (void)server;
    (void)client;
    return "413 " + message + " :No toplevel domain specified";
}

std::string ERR_TOOMANYTARGETS(server& server, user& client, const std::string& channel) {
    (void)server;
    (void)client;
    return "407 " + channel + " :Duplicate recipients. No message delivered";
}

std::string ERR_UNKNOWNCOMMAND(server& server, user& client) {
    (void)server;
    (void)client;
    return "421 :Unknown command";
}

std::string ERR_ERRONEUSNICKNAME(server& server, user& client, const std::string& nickname) {
    (void)server;
    (void)client;
    return "432 " + nickname + " :Erroneus nickname";
}

std::string ERR_NICKNAMEINUSE(server& server, user& client, const std::string& nickname) {
    (void)server;
    (void)client;
    return "433 " + nickname + " :Nickname is already in use";
}
std::string ERR_NOTREGISTERED(server& server, user& client) {
    (void)server;
    (void)client;
    return "451 :You have not registered";
}
std::string ERR_NEEDMOREPARAMS(server& server, user& client) {
    (void)server;
    (void)client;
    return "461 :Not enough parameters";
}


std::string ERR_ALREADYREGISTRED(server& server, user& client) {
    (void)server;
    (void)client;
    return "462 :You may not reregister";
}

std::string ERR_PASSWDMISMATCH(server& server, user& client) {
    (void)server;
    (void)client;
    return "464 :Password incorrect";
}

std::string ERR_NOLOGIN(server& server, user& client) {
    (void)server;
    (void)client;
    return "465 :You are not logged in";
}

std::string ERR_CHANOPRIVSNEEDED(server& server, user& client, const std::string& channel) {
    (void)server;
    (void)client;
    return "482  " + channel + " :You're not channel operator";
}

std::string ERR_UNKNOWNMODE(server& server, user& client, const std::string& mode) {
    (void)server;
    (void)client;
    return "472 " + mode + " :is unknown mode char to me";
}

std::string ERR_INVITEONLYCHAN(server& server, user& client, const std::string& channel) {
    (void)server;
    (void)client;
    return "473  " + channel + " :Cannot join channel (+i)";
}

std::string ERR_userSDONTMATCH(server& server, user& client) {
    (void)server;
    (void)client;
    return "502 :Can't change mode for other users";
}


std::string ERR_userNOTINCHANNEL(server& server, user& client, const std::string& user, const std::string& channel) {
    (void)server;
    (void)client;
    return "441 " + user + " " + channel + " :They aren't on that channel";
}

/*--------------------------------------------------------------------------------------*/

std::string RPL_JOIN(server& server, user& client, const std::string& channel) {
    (void)server;
    (void)client;
    return ": JOIN " + channel;
}

std::string RPL_NICK(server& server, user& client, const std::string& oldnick, const std::string& newnick) {
    (void)server;
    (void)client;
    return ":" + oldnick + " NICK " + newnick;
}
std::string RPL_QUIT(server& server, user& client) {
    (void)server;
    (void)client;
    return " QUIT";
}

std::string RPL_QUIT(server& server, user& client, const std::string& message) {
    (void)server;
    (void)client;
    return " QUIT :" + message;
}
std::string RPL_KICK(server& server, user& client, const std::string& channel, const std::string& user, const std::string& message) {
    (void)server;
    (void)client;
    return " KICK " + channel + " " + user + " :" + message;
}
std::string RPL_NOTICE(server& server, user& client, const std::string& channel, const std::string& message) {
    (void)server;
    (void)client;
    return " NOTICE " + channel + " :" + message;
}
std::string RPL_PRIVMSG(server& server, user& client, const std::string& channel, const std::string& message) {
    (void)server;
    (void)client;
    return " PRIVMSG " + channel + " :" + message;
}