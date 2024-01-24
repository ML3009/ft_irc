/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPL.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purple <purple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 14:50:00 by purple            #+#    #+#             */
/*   Updated: 2024/01/24 16:48:59 by purple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

void displayWelcome(server &server, user &client){

	if (send(client.getfd(), RPL_WELCOME(server, client).c_str(), RPL_WELCOME(server, client).length(), 0) == -1 ||
    	send(client.getfd(), RPL_YOURHOST(server, client).c_str(), RPL_YOURHOST(server, client).length(), 0) == -1 ||
        send(client.getfd(), RPL_CREATED(server, client).c_str(), RPL_CREATED(server, client).length(), 0) == -1 ||
    	send(client.getfd(), RPL_MYINFO(server, client).c_str(), RPL_MYINFO(server, client).length(), 0) == -1)
		std::perror("send:");
}

// response = ":" + this->getHostname() + " " + RPL_WELCOME + " " + client.getNickname() + " :" + WELCOME + " " + client.getNickname() + "!" + client.getUsername() + "@" + client.getIpAddress() + "\r\n";
// 	response += ":" + this->getHostname() + " " + RPL_YOURHOST + " " + client.getNickname() + " :Your host is " + this->getHostname() + ", running version 0.6\r\n";
// 	response += ":" + this->getHostname() + " " + RPL_CREATED + " " + client.getNickname() + " :This server was created sometime in the near future\r\n";

std::string RPL_WELCOME(server &server, user &client){
	(void)server;
    return ":" + server.getID() + " 001 " + client.getNickname() + /*" Welcome" + */" :Welcome to the Internet Relay Network " + client.getNickname() + "!" + client.getUsername() + "@" + client.getIP() + "\r\n";
}

std::string RPL_YOURHOST(server &server, user &client){
    return ":" + server.getID() + " 002 " + client.getNickname() + " :Your host is " + server.getID() + ", running version 0.6\r\n";
}

std::string RPL_CREATED(server &server, user &client) {
    (void)server;
    // std::time_t now = std::time(NULL);
    // std::tm* localTime = std::localtime(&now);

    // if (!localTime) {
        // return "Error.";
    // }
    // char buffer[512];
    // std::strftime(buffer, sizeof(buffer), " :This server was created on \033[0;36m %B %d %Y %H:%M:%S.\033[0m\r\n", localTime);

    return std::string(":" + server.getID() + " 003 " + client.getNickname() + " :This server was created on 2024/01/24\r\n");
}

std::string RPL_MYINFO(server &server, user &client){

	return "004 " + client.getNickname() + " :" + server.getID() + " 1.0 -none- itkol\r\n";
}

/*---------------------------------------------------------------------------------------------------*/

std::string RPL_NOTOPIC(server& server, user& client, std::string channel) {
    (void)server;
    (void)client;
    return "331 "+ channel + " :No topic is set";
}

std::string RPL_TOPIC(server& server, user& client, std::string channel, std::string topic) {
    (void)server;
    (void)client;
    return "TOPIC " + channel + " :" + topic;
}

std::string RPL_INVITING(user &Client, std::string channel){
    return "341 " + Client.getNickname() + " " + channel;
}

std::string RPL_NAMREPLY(std::string message){
    return "355 " + message;
}

std::string ERR_NOSUCHNICK(std::string dest) {
    return "401 " + dest + " :No such nick/channel";
}

std::string ERR_NOSUCHCHANNEL(server& server, user& client, std::string Channel) {
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

    return "421 " + cmd + " :unknown command";
}

std::string  ERR_NICKNAMEINUSE (server& server, user& client, std::string name) {
    (void)server;
    (void)client;
    return "433 " + name + " :Nickname already use";
}


std::string ERR_USERNOTINCHANNEL(server& server, user& client, std::string Channel) {
    (void)server;
    return "441 " + client.getNickname() +  " " + Channel  + " :They aren't on that channel";
}

std::string ERR_NOTONCHANNEL(user& client, std::string Channel) {
    (void)client;
    return "442 " + Channel + " :You're not on that channel";

}

 std::string ERR_NOTREGISTERED(server& server, user& client) {
    (void)server;
    (void)client;
    return "451 :Not registered";
}


std::string ERR_NEEDMOREPARAMS(user& client) {
    return "461 " + client.getNickname() + " :Not enough parameters";
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

std::string ERR_CHANNELISFULL(std::string &channel){
    return "471 " + channel + " :is full";
}

std::string ERR_UNKNOWNMODE(server& server, user& client, std::string mode) {
    (void)server;
    (void)client;
    return "472 " + mode + " :is unknown mode char to me";
}
std::string ERR_INVITEONLYCHAN(std::string channel) {
    return "473 " + channel + " :Cannot join channel (+i)";
}

std::string ERR_BADCHANNELKEY(server& server, user& client, std::string Channel) {
    (void)server;
    (void)client;
    return "475 " + Channel + " :Cannot join channel (+k)";
}


std::string ERR_BADCHANMASK(server& server, user& client, std::string Channel) {
    (void)server;
    (void)client;
    return "476 " + Channel  + " :Cannot join channel";
}

std::string ERR_CHANOPRIVSNEEDED(std::string channel) {

    return "482 " + channel + " :You're not a channel operator";
}






/*--------------------------------------------------------------------------------------*/

std::string RPL_JOIN(server& server, user& client, const std::string channel) {
    (void)server;
    (void)client;
    return ": Bienvenue sur le channel : " + channel;
}
std::string RPL_NICK(server& server, user& client, const std::string oldnick, const std::string newnick) {
    (void)server;
    (void)client;
    return ":" + oldnick + " NICK " + newnick;
}
std::string RPL_QUIT(server& server, user& client) {
    (void)server;
    (void)client;
    return " QUIT";
}
std::string RPL_QUIT_M(server& server, user& client, const std::string message) {
    (void)server;
    (void)client;
    return " QUIT :" + message;
}
std::string RPL_KICK(server& server, user& client, const std::string channel, const std::string user, const std::string message) {
    (void)server;
    (void)client;
    (void)channel;
    (void)user;
    return message;
}
std::string RPL_NOTICE(server& server, user& client, const std::string channel, const std::string message) {
    (void)server;
    (void)client;
    return " NOTICE " + channel + " :" + message;
}
std::string RPL_PRIVMSG(const std::string message) {
    return message;
}
std::string HI_BOT(const std::string message){
    return message;
}
