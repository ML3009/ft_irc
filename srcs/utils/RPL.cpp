/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPL.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purple <medpurple@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 14:50:00 by purple            #+#    #+#             */
/*   Updated: 2024/01/05 23:11:55 by purple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

int special_code(std::string RPL){
    if (RPL == "RPL_JOIN")
        return 10;
    if (RPL == "RPL_NICK")
        return 11;
    if (RPL == "RPL_QUIT")
        return 12;
    if (RPL == "RPL_QUIT_M")
        return 13;
    if (RPL == "RPL_KICK")
        return 14;
    if (RPL == "RPL_NOTICE")
        return 15;
    if (RPL == "RPL_PRIVMSG")
        return 16;
    return -1;
}


std::string displayRPL(server &server, user &client, std::string RPL){
{
    int code;
    if ((int)std::strtol(RPL.c_str(), NULL, 10))
        code = (int)std::strtol(RPL.c_str(), NULL, 10);
    else
        code = special_code(RPL);
    switch (code)
    {
    case 10:
        return RPL_JOIN(server, client, "channel");
    case 11:
        return RPL_NICK(server, client, "old", "new");
    case 12:
        return RPL_QUIT(server, client);
    case 13:
        return RPL_QUIT_M(server, client, "");
    case 14:
        return RPL_KICK(server, client, "channel", "user", "message");
    case 15:
        return RPL_NOTICE(server, client, "channel", "message");
    case 16:
        return RPL_PRIVMSG(server, client, "channel", "message");
    case 221:
        return RPL_UMODEIS(server, client, "mode");
    case 321:
        return RPL_LISTSTART(server, client);
    case 322:
        return RPL_LIST(server, client, "channel", "nb", "topic");
    case 323:
        return RPL_LISTEND(server, client);
    case 324:
        return RPL_CHANNELMODEIS(server, client, "channel", "mode");
    case 331:
        return RPL_NOTOPIC(server, client, "channel");
    case 332:
        return RPL_TOPIC(server, client, "channel", "topic");
    case 353:
        return RPL_NAMREPLY(server, client, "channel", "user");
    case 366:
        return RPL_ENDOFNAMES(server, client, "channel");
    case 401:
        return ERR_NOSUCHNICK(server, client, "user", "dest");
    case 403:
        return ERR_NOSUCHCHANNEL(server, client, "channel");
    case 404:
        return ERR_CANNOTSENDTOCHAN(server, client, "channel");
    case 405:
        return ERR_TOOMANYCHANNELS(server, client, "channel");
    case 407:
        return ERR_TOOMANYTARGETS(server, client, "channel");
    case 411:
        return ERR_NORECIPIENT(server, client, "message");
    case 412:
        return ERR_NOTEXTTOSEND(server, client);
    case 413:
        return ERR_NOTOPLEVEL(server, client, "message");
    case 414:
        return ERR_WILDTOPLEVEL(server, client, "message");
    case 421:
        return ERR_UNKNOWNCOMMAND(server, client);
    case 431:
        return ERR_NONICKNAMEGIVEN(server, client);
    case 432:
        return ERR_ERRONEUSNICKNAME(server, client, "nickname");
    case 433:
        return ERR_NICKNAMEINUSE(server, client,"nickname");
    case 441:
        return ERR_USERNOTINCHANNEL(server, client,"user", "channel");
    case 442:
        return ERR_NOTONCHANNEL(server, client, "channel");
    case 451:
        return ERR_NOTREGISTERED(server, client);
    case 461:
        return ERR_NEEDMOREPARAMS(server, client);
    case 462:
        return ERR_ALREADYREGISTRED(server, client);
    case 464:
        return ERR_PASSWDMISMATCH(server, client);
    case 465:
        return ERR_NOLOGIN(server, client);
    case 472:
        return ERR_UNKNOWNMODE(server, client, "mode");
    case 473:
        return ERR_INVITEONLYCHAN(server, client, "channel");
    case 476:
        return ERR_BADCHANMASK(server, client, "channel");
    case 482:
        return ERR_CHANOPRIVSNEEDED(server, client,"channel");
    case 502:
        return ERR_USERSDONTMATCH(server, client);
    default:
        return RPL;
    }
}

}

void displayWelcome(server &server, user &client){
    
	if (send(client.getfd(), RPL_WELCOME(server, client).c_str(), RPL_WELCOME(server, client).length(), 0) == -1 ||
    	send(client.getfd(), RPL_YOURHOST(server, client).c_str(), RPL_YOURHOST(server, client).length(), 0) == -1 ||
        send(client.getfd(), RPL_CREATED(server, client).c_str(), RPL_CREATED(server, client).length(), 0) == -1 ||
    	send(client.getfd(), RPL_MYINFO(server, client).c_str(), RPL_MYINFO(server, client).length(), 0) == -1)
		std::perror("send:");
}

std::string RPL_WELCOME(server &server, user &client){
	(void)server;
	(void)client;
	return "Bienvenue sur le serveur IRC. Connecté avec succès !\n";
}

std::string RPL_YOURHOST(server &server, user &client){
	(void)client;
	return "Notre serveur hôte IRC est " + server.getID() + "\n";
}

std::string RPL_CREATED(server &server, user &client) {
	(void)server;
	(void)client;
    std::time_t now = std::time(NULL);
    std::tm* localTime = std::localtime(&now);

    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "Ce serveur a été créé le %d %B %Y à %H:%M:%S.\n", localTime);
    
    return buffer;
}

std::string RPL_MYINFO(server &server, user &client){
	(void)client;
	return server.getID() + " Serveur IRC v1.0. Modes supportés : +i, +t, +k, +o, +l. Utilisez /HELP pour obtenir de l'aide.\n";
}

/*---------------------------------------------------------------------------------------------------*/




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

std::string ERR_TOOMANYTARGETS(server& server, user& client, const std::string& channel) {
    (void)server;
    (void)client;
    return "407 " + channel + " :Duplicate recipients. No message delivered";
}

std::string ERR_NORECIPIENT(server& server, user& client, const std::string& message) {
    (void)server;
    (void)client;
    return "411 " + message + " :No recipient given";
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

std::string ERR_WILDTOPLEVEL(server& server, user& client, const std::string& message) {
    (void)server;
    (void)client;
    return "414 " + message + " :Wildcard in toplevel domain";
}


std::string ERR_UNKNOWNCOMMAND(server& server, user& client) {
    (void)server;
    (void)client;
    return "421 :Unknown command";
}

std::string ERR_NONICKNAMEGIVEN(server& server, user& client) {
    (void)server;
    (void)client;
    return "431 :No nickname given";
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

std::string ERR_USERNOTINCHANNEL(server& server, user& client, const std::string& user, const std::string& channel) {
    (void)server;
    (void)client;
    return "441 " + user + " " + channel + " :They aren't on that channel";
}

std::string ERR_NOTONCHANNEL(server& server, user& client, const std::string& channel) {
    (void)server;
    (void)client;
    return "442 " + channel + " :You're not on that channel";
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

std::string ERR_BADCHANMASK(server& server, user& client, const std::string& channel) {
    (void)server;
    (void)client;
    return "476 " + channel + " :Bad Channel Mask";
}

std::string ERR_CHANOPRIVSNEEDED(server& server, user& client, const std::string& channel) {
    (void)server;
    (void)client;
    return "482  " + channel + " :You're not channel operator";
}
std::string ERR_USERSDONTMATCH(server& server, user& client) {
    (void)server;
    (void)client;
    return "502 :Can't change mode for other users";
}

/*--------------------------------------------------------------------------------------*/

std::string RPL_JOIN(server& server, user& client, const std::string& channel) {
    (void)server;
    (void)client;
    return ": Bienvenue sur le channel : " + channel;
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
std::string RPL_QUIT_M(server& server, user& client, const std::string& message) {
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