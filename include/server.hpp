/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purple <purple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 11:01:10 by purple            #+#    #+#             */
/*   Updated: 2023/12/21 13:26:24 by purple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "irc.hpp"

class server{
	public:
// Coplien
			server();
			server(int port, std::string password);
			server(const server& rhs);
			server& operator=(const server& rhs);
			~server();

// Fonction
			void init_server(void);
// Getter / Setter
// Exception
	protected:

	private:
			int				_port;
			std::string		_password;
			
			void 			_display_constructor(std::string msg);
};




#define SERVER_DC "[Default] Constructor called for SERVER CLASS"
#define SERVER_PC "[Parametric] Constructor called for SERVER CLASS"
#define SERVER_CC "[Copy] Constructor called for SERVER CLASS"
#define SERVER_AO "[Attribution] Operator called for SERVER CLASS"
#define SERVER_DD "[Default] Destructor called for SERVER CLASS"