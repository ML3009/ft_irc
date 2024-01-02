/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purple <medpurple@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 10:07:01 by purple            #+#    #+#             */
/*   Updated: 2024/01/01 17:55:50 by purple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

bool completeCommand(std::string msg){
    if (msg.length() > 2 && msg[msg.length()] == '\n' && msg[msg.length() - 1] == '\r')
        return COMPLETE;
    return INCOMPLETE;
}

std::vector<std::string> splitArgs(std::string buffer){
    std::vector<std::string> args;
    char *arg = strtok((char *)buffer.c_str(), "\n\r ");
    while (arg != NULL && buffer.empty())
    {
        args.push_back(arg);
        arg = strtok((char *)buffer.c_str(), "\n\r ");
    }
    return args;
}