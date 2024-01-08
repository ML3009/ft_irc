/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvautrot <mvautrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 17:31:58 by purple            #+#    #+#             */
/*   Updated: 2024/01/08 16:49:01 by mvautrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

bool handleSignal	= false;
int DEBUG			= NO;
int CONSTRUCTOR		= NO;
int	LOG				= LOGFILE;
//std::map<std::string, channel> channelMap;

//std::map<std::string channel, std::vector<channel> > channelMap;

//Channel {

// 	public:
// 		getUsername
// 		display user

// 	private :

// 	std::vector<user> user;
// }



int main(int ac, char **av){
	std::remove("logs.txt");
	try{
		try_args(ac, av);
		std::signal(SIGINT, handle_signal);
		server Server(atoi(av[1]), std::string(av[2]));
		Server.init_server();

		while (!handleSignal){
			Server.run_server();
		}
		Server.closeServerSocket();
	}
	catch (const std::exception &e){
		std::cout << e.what() << std::endl;
	}
	return 0;
}

