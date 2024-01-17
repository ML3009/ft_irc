/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvautrot <mvautrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 10:07:01 by purple            #+#    #+#             */
/*   Updated: 2024/01/17 11:26:07 by mvautrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

bool completeCommand(std::string msg, int opt){
	int i = msg.size();
	while (msg[i] == '\0')
		i--;
	if (msg[i] == '\n')
	{
		if (msg[i - 1] != '\r' && opt == 1)
			std::cout << "\e[0;33m" << "[You are using nc without -C. I'll not trying to detect a \\r]\x1b[0m" << std::endl;
		return COMPLETE;
	}
	return INCOMPLETE;
}

std::vector<std::string> splitArgs(std::string buffer){
    debug("splitArgs", BEGIN);
    std::vector<std::string> args;
    char *arg = strtok((char *)buffer.c_str(), "\r\n ");
    while (arg != NULL && !buffer.empty())
    {
        args.push_back(arg);
        arg = strtok(NULL, "\r\n ");
    }
    debug("splitArgs", END);
    return args;
}
