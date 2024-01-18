/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPL.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purple <purple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 14:50:00 by purple            #+#    #+#             */
/*   Updated: 2024/01/18 15:01:45 by purple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

// int special_code(std::string RPL){
//     if (RPL == "JOIN")
//         return 10;
//     if (RPL == "NICK")
//         return 11;
//     if (RPL == "QUIT")
//         return 12;
//     if (RPL == "QUIT_M")
//         return 13;
//     if (RPL == "KICK")
//         return 14;
//     if (RPL == "NOTICE")
//         return 15;
//     if (RPL == "PRIVMSG")
//         return 16;
//     if (RPL == "HI_BOT")
//         return 17;
//     return -1;
// }


// std::string displayRPL(server &server, user &client, std::string RPL, std::string message, std::string channel){
// {
//     int code;
//     if ((int)std::strtol(RPL.c_str(), NULL, 10))
//         code = (int)std::strtol(RPL.c_str(), NULL, 10);
//     else
//         code = special_code(RPL);
//     switch (code)
//     {
//         case 10:
//             return RPL_JOIN(server, client, channel);
//         case 11:
//             return RPL_NICK(server, client, "old", "new");
//         case 12:
//             return RPL_QUIT(server, client);
//         case 13:
//             return RPL_QUIT_M(server, client, "");
//         case 14:
//             return RPL_KICK(server, client, channel, "user", message);
//         case 15:
//             return RPL_NOTICE(server, client, channel, message);
//         case 16:
//             return RPL_PRIVMSG(message);
//         case 17:
//             return HI_BOT(message);
//         case 221:
//             return RPL_UMODEIS(server, client, "mode");
//         case 321:
//             return RPL_LISTSTART(server, client);
//         case 322:
//             return RPL_LIST(server, client, channel, "nb", "topic");
//         case 323:
//             return RPL_LISTEND(server, client);
//         case 324:
//             return RPL_CHANNELMODEIS(server, client, channel, "mode");
//         case 331:
//             return RPL_NOTOPIC(server, client, channel);
//         case 353:
//             return RPL_NAMREPLY(server, client, channel, "user");
//         case 366:
//             return RPL_ENDOFNAMES(server, client, channel);
//         case 401:
//             return ERR_NOSUCHNICK(server, client);
//         case 403:
//             return ERR_NOSUCHCHANNEL(server, client, channel);
//         case 404:
//             return ERR_CANNOTSENDTOCHAN(server, client);
//         case 405:
//             return ERR_TOOMANYCHANNELS(server, client, channel);
//         case 407:
//             return ERR_TOOMANYTARGETS(server, client, channel);
//         case 411:
//             return ERR_NORECIPIENT(server, client, message);
//         case 412:
//             return ERR_NOTEXTTOSEND(server, client);
//         case 413:
//             return ERR_NOTOPLEVEL(server, client, message);
//         case 414:
//             return ERR_WILDTOPLEVEL(server, client, message);
//         case 421:
//             return ERR_UNKNOWNCOMMAND(server, client, cmd);
//         case 431:
//             return ERR_NONICKNAMEGIVEN(server, client);
//         case 432:
//             return ERR_ERRONEUSNICKNAME(server, client, "nickname");
//         case 433:
//             return ERR_NICKNAMEINUSE(server, client,"nickname");
//         case 441:
//             return ERR_USERNOTINCHANNEL(server, client, channel);
//         case 442:
//             return ERR_NOTONCHANNEL(server, client, channel);
//         case 451:
//             return ERR_NOTREGISTERED(server, client);
//         case 461:
//             return ERR_NEEDMOREPARAMS(server, client);
//         case 462:
//             return ERR_ALREADYREGISTRED(server, client);
//         case 464:
//             return ERR_PASSWDMISMATCH(server, client);
//         case 465:
//             return ERR_NOLOGIN(server, client);
//         case 472:
//             return ERR_UNKNOWNMODE(server, client, message);
//         case 473:
//             return ERR_INVITEONLYCHAN(server, client, channel);
//         case 475:
//             return ERR_BADCHANNELKEY(server, client, channel);
//         case 476:
//             return ERR_BADCHANMASK(server, client, channel);
//         case 482:
//             return ERR_CHANOPRIVSNEEDED(server, client,channel);
//         case 502:
//             return ERR_USERSDONTMATCH(server, client);
//         default:
//             return message;
//     }
// }

//}



void displayWelcome(server &server, user &client){

	if (send(client.getfd(), RPL_WELCOME(server, client).c_str(), RPL_WELCOME(server, client).length(), 0) == -1 ||
    	send(client.getfd(), RPL_YOURHOST(server, client).c_str(), RPL_YOURHOST(server, client).length(), 0) == -1 ||
        send(client.getfd(), RPL_CREATED(server, client).c_str(), RPL_CREATED(server, client).length(), 0) == -1 ||
    	send(client.getfd(), RPL_MYINFO(server, client).c_str(), RPL_MYINFO(server, client).length(), 0) == -1)
		std::perror("send:");
}

std::string RPL_WELCOME(server &server, user &client){
	(void)client;
    return "001 " + client.getNickname() + " :Bienvenue sur le serveur IRC !";
}

std::string RPL_YOURHOST(server &server, user &client){
    return "002 " + client->getNickname() + " :Your host is " + server.getId();
}

std::string RPL_CREATED(server &server, user &client) {
    (void)server;
    std::time_t now = std::time(NULL);
    std::tm* localTime = std::localtime(&now);

    if (!localTime) {
        return "Error.";
    }
    char buffer[512];
    std::strftime(buffer, sizeof(buffer), "003 " + client->getNickname() + " :This server was created on \033[0;36m%d %B %Y à %H:%M:%S.\r\n\033[0m", localTime);

    return std::string(buffer);
}

std::string RPL_MYINFO(server &server, user &client){

	return "004 " + client->getNickname() + " :" + server->getId() + "\033[0;34mIRC Server v1.0. Modes supportés : \033[0m\033[0;35m[+i +t +k +o +l].\r\n\033[0m";
}

/*---------------------------------------------------------------------------------------------------*/

std::string RPL_NOTOPIC(server& server, user& client, std::string & channel) {
    (void)server;
    (void)client;
    return "331 "+ channel + " :No topic is set";
}

std::string RPL_TOPIC(server& server, user& client, std::string& channel, std::string& topic) {
    (void)server;
    (void)client;
    return "332 "+ channel + " :" + topic;
}

std::string ERR_NOSUCHNICK(server& server, user& client) {
    (void)server;
    (void)client;
    return "401 " + client->getNickname() + " " "No such nick/channel";
}

std::string ERR_NOSUCHCHANNEL(server& server, user& client, std::string &Channel) {
    (void)server;
    (void)client;
    return "403 " + Channel + " No such channel";
}

std::string ERR_NORECIPIENT(void){
    return "411 :No recipient given"; 
}

std::string ERR_NOTEXTTOSEND(void){
    return "412 :No text to send"; 
}

std::string ERR_UNKNOWNCOMMAND(std::string cmd) {

    return "421" + cmd + " :unknown command";
}

std::string  ERR_NICKNAMEINUSE (server& server, user& client, std::string &name) {
    (void)server;

    return "433 " + name + " :Nickname already use";
}


std::string ERR_USERNOTINCHANNEL(server& server, user& client, std::string& Channel) {
    (void)server;
    (void)client;
    (void)channel;
    return "441 " + client->getNickname +  " " + Channel  + " :You aren't on that channel";
}

std::string ERR_NOTONCHANNEL(server& server, user& client, std::string& Channel) {
    (void)server;
    (void)client;
    (void)channel;
    return "442 " + Channel + " :You're not on that channel";

}

 std::string ERR_NOTREGISTERED(server& server, user& client) {
    (void)server;
    (void)client;
    return "451 :Not registered";
}


std::string ERR_NEEDMOREPARAMS(server& server, user& client) {
    (void)server;

    return "461 " + client->getNickname + " :Not enough parameters";
}


std::string ERR_ALREADYREGISTRED(server& server, user& client) {
    (void)server;
    (void)client;
    return  "462 :You may not reregister";
}

std::string ERR_PASSWDMISMATCH(server& server, user& client) {
    (void)server;
    (void)client;
    return "464 :You may not reregister";
}

std::string ERR_UNKNOWNMODE(server& server, user& client, const std::string& mode) {
    (void)server;
    (void)client;
    return "472 " + mode + " :is unknown mode char to me";
}
std::string ERR_INVITEONLYCHAN(server& server, user& client, std::string& channel) {
    (void)server;
    (void)client;
    (void)channel;
    return "473 " + Channel + "Cannot join channel (+i)";
}

std::string ERR_BADCHANNELKEY(server& server, user& client, std::string& Channel) {
    (void)server;
    (void)client;
    (void)channel;
    return "475 " + Channel + " :Cannot join channel (+k)";
}


std::string ERR_BADCHANMASK(server& server, user& client, std::string& Channel) {
    (void)server;
    (void)client;
    (void)channel;
    return "476 " + Channel  + " :Cannot join channel";
}

std::string ERR_CHANOPRIVSNEEDED(server& server, user& client, std::string& Channel) {
    (void)server;
    (void)client;
    (void)channel;
    return "482 " + Channel + " :You're not a channel operator";
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
    (void)channel;
    (void)user;
    return message;
}
std::string RPL_NOTICE(server& server, user& client, const std::string& channel, const std::string& message) {
    (void)server;
    (void)client;
    return " NOTICE " + channel + " :" + message;
}
std::string RPL_PRIVMSG(const std::string& message) {
    return message;
}
std::string HI_BOT(const std::string& message){
    return message;
}
