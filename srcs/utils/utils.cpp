/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvautrot <mvautrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 10:07:01 by purple            #+#    #+#             */
/*   Updated: 2024/01/03 14:10:38 by mvautrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

bool completeCommand(std::string msg){
    if (msg.length() > 2 && msg[msg.length() - 1] == '\n' && msg[msg.length() - 2] == '\r')
        return COMPLETE;
    else if (msg.length() > 1 && msg[msg.length() - 1] == '\n')
    {
        std::cout << "\e[0;33m" << "[You are using nc without -C. I'll not trying to detect a \\r]\x1b[0m" << std::endl;
        return COMPLETE;
    }
    return INCOMPLETE;
}

std::vector<std::string> splitArgs(std::string buffer){
    debug("splitArgs", BEGIN);
    std::vector<std::string> args;
    char *arg = strtok((char *)buffer.c_str(), "\n\r ");
    while (arg != NULL && !buffer.empty())
    {
        args.push_back(arg);
        arg = strtok(NULL, "\n\r ");
    }
    debug("splitArgs", END);
    return args;
}
