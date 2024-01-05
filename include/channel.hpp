/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvautrot <mvautrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 16:15:19 by mvautrot          #+#    #+#             */
/*   Updated: 2024/01/03 10:29:18 by mvautrot         ###   ########.fr       */
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
		std::string	getChannelName() const;
		void	setOperator(user& Client) ;

//operator
		bool operator<(const channel& other) const;
	
	private:
		std::string	_channelName;
		std::vector<std::string>	_operatorName;

};

