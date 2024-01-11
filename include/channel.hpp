/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purple <purple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 16:15:19 by mvautrot          #+#    #+#             */
/*   Updated: 2024/01/11 10:33:09 by purple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "irc.hpp"

class channel {

	public:
//Coplien
		channel();
		channel(std::string channelName);
		channel(const channel& rhs);
		channel& operator=(const channel& rhs);
		~channel();

// Setter / Getter
		std::string					getChannelName() const;
		std::vector<user>			&getChannelUser();
		std::vector<std::string>	getChannelOperators() const;
		std::string&				getKeyword();
		std::set<char>				&getMode();
		std::vector<std::string> 	&getInviteList();
		
		void						setOperator(std::string channelOperator) ;
		void						setChannelUser(user& Client);
		void						setKeyword(std::string keyword);
		void						setMode(std::string mode);
		void						unsetMode(std::string mode);



		void						display_operators(std::vector<std::string> channelOperator);
		void						display_users(std::vector<user> channelUser);
//INVITE
		bool						isInvited(std::string name);

//MODE
		bool						search_mode(char mode);
		std::string					display_mode();


		bool						isAlreadyinChannel(user &Client);
		bool						isOperator(user &Client);
		int 						getTopicStatus(channel &canal, user &client, server &server);
		bool						isFull(server &Server, user &Client);
		bool						isInvited(server &Server, user &Client);
		bool						isValidPass(server &Server, user &Client, std::vector<std::string> key_tmp, int pos);
		int							parseCmdJoin(server &Server, user &Client, std::vector<std::string>& argument);


//operator


	private:
		std::string					_channelName;
		std::vector<user>			_channelUser;
		std::vector<std::string>  	_invitedUser;
		std::vector<std::string>	_channelOperator;
		std::string					_topic;
		std::string					_keyword;
		std::set<char>				_mode;


};

