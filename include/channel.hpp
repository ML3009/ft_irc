/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purple <purple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 16:15:19 by mvautrot          #+#    #+#             */
/*   Updated: 2024/01/10 11:30:40 by purple           ###   ########.fr       */
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
		std::vector<std::string> getChannelOperators() const;

		void						setOperator(std::string channelOperator) ;
		void						setChannelUser(user& Client);



		void						display_operators(std::vector<std::string> channelOperator);
		void						display_users(std::vector<user> channelUser);
		bool						isAlreadyinChannel(user &Client);
		bool						isOperator(user &Client);
		int 						getTopicStatus(channel &canal, user &client, server &server);


//operator


	private:
		std::string					_channelName;
		std::vector<user>			_channelUser;
		std::vector<std::string>	_channelOperator;
		std::string					_topic;


};

