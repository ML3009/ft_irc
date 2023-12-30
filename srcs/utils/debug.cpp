/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purple <medpurple@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 17:31:43 by purple            #+#    #+#             */
/*   Updated: 2023/12/29 21:23:26 by purple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

void debug(std::string msg, int type){
    if (DEBUG == -1)
        return ;
    std::ofstream logfile("logs.txt", std::ios::out | std::ios::app);
    (logfile.is_open()) ? void() : (std::perror("open"), throw openException());

    if (type == BEGIN && LOG == STDOUT)
        std::cout << "--> \e[0;35m [ Entering ] Function : " << msg << "\e[0m" << std::endl;
    else if (type == END && LOG == STDOUT)
        std::cout << "<-- \e[0;36m [ Leaving ]  Function : " << msg << " \e[0m" << std::endl;
    else if (type == BEGIN && LOG == LOGFILE)
        logfile << "--> [ Entering ] Function : " << msg << std::endl;
    else if (type == END && LOG == LOGFILE)
        logfile << "<-- [ Leaving ]  Function : " << msg << std::endl;
    else 
        std::cout << "\e[0;35m DEBUG HERE " << " \e[0m" << std::endl;
    logfile.close();
        
}

void display_constructor(std::string msg){
    
    if (CONSTRUCTOR == -1)
        return ;
    std::ofstream logfile("logs.txt", std::ios::out | std::ios::app);
    (logfile.is_open()) ? void() : (std::perror("open"), throw openException());
    
    if (LOG == STDOUT)
        std::cout << "\x1b[33m \x1b[3m" << msg << "\x1b[0m" << std::endl;
    else
        logfile << msg << std::endl;
    logfile.close();

}