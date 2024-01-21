/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purple <medpurple@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 10:07:01 by purple            #+#    #+#             */
/*   Updated: 2024/01/20 23:14:33 by purple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

bool completeCommand(std::string msg){
    std::size_t found = msg.find_first_of("\n");
    if (found != std::string::npos)
        return COMPLETE;
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

int botcmd(std::string arg){
    std::string cmd[4] = {"HELP", "FACT", "HI", "QUIZZ"};
    for (int i = 0; i < 4; i++){
        if (cmd[i] == arg)
            return i;
    }
    return -1;
}