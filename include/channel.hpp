/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvautrot <mvautrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 16:15:19 by mvautrot          #+#    #+#             */
/*   Updated: 2024/01/10 12:01:52 by mvautrot         ###   ########.fr       */
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
		std::vector<user>			getChannelUser() const;
		std::vector<std::string>	getChannelOperators() const;
		std::string&				getKeyword();
		std::set<char>				getMode() const;

		void						setOperator(std::string channelOperator) ;
		void						setChannelUser(user& Client);
		void						setKeyword(std::string keyword);
		void						setMode(std::string mode);
		void						unsetMode(std::string mode);



		void						display_operators(std::vector<std::string> channelOperator);
		void						display_users(std::vector<user> channelUser);


//MODE
		bool						search_mode(std::set<char>	searchMode, char mode);


		bool						isAlreadyinChannel(user &Client);
		bool						isFull(server &Server, user &Client);
		bool						isInvited(server &Server, user &Client);
		bool						isValidPass(server &Server, user &Client, std::vector<std::string> key_tmp, int pos);

		int							parseCmdJoin(server &Server, user &Client, std::vector<std::string>& argument);


//operator


	private:
		std::string					_channelName;
		std::vector<user>			_channelUser;
		std::vector<std::string>	_channelOperator;
		std::string					_keyword;
		std::set<char>				_mode;


};

