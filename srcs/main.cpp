/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purple <medpurple@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 17:31:58 by purple            #+#    #+#             */
/*   Updated: 2023/12/27 22:15:08 by purple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

bool handleSignal	= false;
bool DEBUG			= false;
bool CONSTRUCTOR	= true;

int main(int ac, char **av){

	try{
		try_args(ac, av);
		std::signal(SIGINT, handle_signal);
		server Server(atoi(av[1]), std::string(av[2]));
		Server.init_server();

		while (!handleSignal){
			Server.run_server();
		}
	}
	catch (const std::exception &e){
		std::cout << e.what() << std::endl;
	}
	return 0;
}

