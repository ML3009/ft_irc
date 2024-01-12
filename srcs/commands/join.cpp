/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purple <purple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:06:57 by mvautrot          #+#    #+#             */
/*   Updated: 2024/01/11 17:23:27 by purple           ###   ########.fr       */
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
	if (Channel.search_mode('i') == true && Channel.isInvited(Client.getUsername()) == false)
		return INVITEONLYCHAN;
	if (Channel.search_mode('k') == true && Channel.isValidPass(key_tmp, pos) == false)
		return	BADCHANNELKEY;
	return ISVALIDUSER;
}

void	UserJoinChannel(server &Server, user &Client, channel &Channel) {

		Server.sendMsgToChannel(Client, Server, "WELCOME" , Client.getNickname() + " join the channel. Be nice to him",    Channel.getChannelName());
		Channel.setChannelUser(Client);
		if (Channel.isInvited(Client.getUsername())){
			std::vector<std::string>::iterator it = std::find(Channel.getInviteList().begin(), Channel.getInviteList().end(), Client.getUsername());
			Channel.getInviteList().erase(it);
		}
		Server.sendMsg(Client, Server, "WELCOME", "You are now connected on the channel " + Channel.getChannelName() + ". Say hi to everyone", "");
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
