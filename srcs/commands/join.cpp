/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purple <purple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:06:57 by mvautrot          #+#    #+#             */
/*   Updated: 2024/01/10 14:17:19 by purple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.hpp"

int	parseCmdJoin(server &Server, user &Client, std::vector<std::string>& argument) {

	int	count = 0;
	for (std::vector<std::string>::iterator it = argument.begin(); it != argument.end(); ++it, ++count);
	if (count != 2 && count != 3)
		return Server.sendMsg(Client, Server, "461", "", ""), -1;
	if (count == 3)
		return 1;
	return 0;
}

int	parseChannelName(server &Server, user &Client, std::vector<std::string>& channel_tmp) {

	for (unsigned long i = 0; i < channel_tmp.size(); ++i) {
		if (channel_tmp[i][0] != '&' && channel_tmp[i][0] != '#')
			return Server.sendMsg(Client, Server, "476", "", ""), -1;
		if (channel_tmp[i].find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789[]\\`_^{|}-#&") != std::string::npos)
			return Server.sendMsg(Client, Server, "476", "", ""), -1;
	}
	return 0;

}

int	parseChannelKeyword(server &Server, user &Client, std::vector<std::string>& key_tmp, std::vector<std::string>& channel_tmp) {

	int	key = 0;
	for (unsigned long i = 0; i < key_tmp.size(); ++i, ++key) {
		if (key_tmp[i].find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789[]\\`_^{|}-#&") != std::string::npos)
			return Server.sendMsg(Client, Server, "476", "", ""), -1;
	}
	if (channel_tmp.size() < key_tmp.size())
		return Server.sendMsg(Client, Server, "461", "", ""), -1;
	return key;
}

int	isValidUser(server &Server, user &Client, channel &Channel, std::vector<std::string> key_tmp, int pos) {
	if (Channel.isAlreadyinChannel(Client) == true)
		return USR_IN_CHANNEL;
	if (Channel.search_mode('l') == true && Channel.isFull(Server, Client) == true)
		return CHANNELISFULL;
	if (Channel.search_mode('i') == true && Channel.isInvited(Server, Client) == false)
		return INVITEONLYCHAN;
	if (Channel.search_mode('k') == true && Channel.isValidPass(Server, Client, key_tmp, pos) == false)
		return	BADCHANNELKEY;
	return ISVALIDUSER;

// l depassement limite utilisateur
// i invite only
// k regarder mdp
// t TOPIC : est ce que tt le monde peut le changer ou pas.

// o donner retirer le privilege de loperateur cnal

}

void	UserJoinChannel(server &Server, user &Client, channel &Channel) {

		Channel.setChannelUser(Client);
		Server.sendMsgToUser(Client, Client, Server, "WELCOME", "You are now connected on the channel " + Channel.getChannelName() + ". Say hi to everyone");
}

std::vector<std::string> splitCmdJoin(std::string buffer){
    debug("splitCmdJoin", BEGIN);
    std::vector<std::string> args;
    char *arg = strtok((char *)buffer.c_str(), ",");
    while (arg != NULL && !buffer.empty())
    {
        args.push_back(arg);
        arg = strtok(NULL, ",");
    }
    debug("splitsplitCmdJoin", END);
    return args;
}
