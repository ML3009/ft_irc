/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purple <purple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:06:57 by mvautrot          #+#    #+#             */
/*   Updated: 2024/01/18 16:21:29 by purple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.hpp"

int	parseCmdJoin(server &Server, user &Client, std::vector<std::string>& argument) {

	int	count = 0;
	for (std::vector<std::string>::iterator it = argument.begin(); it != argument.end(); ++it, ++count);
	if (count != 2 && count != 3){

		return Server.sendMsg(Server, Client, ERR_NEEDMOREPARAMS(Client)), -1;
	}
	if (count == 3)
		return 1;
	return 0;
}

int	parseChannelName(server &Server, user &Client, std::vector<std::string>& channel_tmp) {

	for (unsigned long i = 0; i < channel_tmp.size(); ++i) {
		if (channel_tmp[i][0] != '&' && channel_tmp[i][0] != '#')
			return Server.sendMsg(Server, Client, ERR_BADCHANMASK(Server, Client, channel_tmp[i])), -1;
		if (channel_tmp[i].find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789[]\\`_^{|}-#&") != std::string::npos)
			return Server.sendMsg(Server, Client, ERR_BADCHANMASK(Server, Client, channel_tmp[i])), -1;
	}
	return 0;

}

int	parseChannelKeyword(server &Server, user &Client, std::vector<std::string>& key_tmp, std::vector<std::string>& channel_tmp) {

	int	key = 0;
	for (unsigned long i = 0; i < key_tmp.size(); ++i, ++key) {
		if (key_tmp[i].find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789[]\\`_^{|}-#&") != std::string::npos)
			return Server.sendMsg(Server, Client, ERR_BADCHANMASK(Server, Client, key_tmp[i])), -1; //
	}
	if (channel_tmp.size() < key_tmp.size())
		return Server.sendMsg(Server, Client, ERR_NEEDMOREPARAMS(Client)), -1;
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

		Channel.setChannelUser(Client);
		Server.sendMsgToChannel(Server, Client, "JOIN :" + Channel.getChannelName(), Channel.getChannelName());
		if (Channel.isInvited(Client.getUsername())){
			std::vector<std::string>::iterator it = std::find(Channel.getInviteList().begin(), Channel.getInviteList().end(), Client.getUsername());
			Channel.getInviteList().erase(it);
		}
		Server.sendMsgToUser(Server, Client, Client, "JOIN :" + Channel.getChannelName());
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
