/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purple <purple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 17:31:43 by purple            #+#    #+#             */
/*   Updated: 2023/12/28 11:16:28 by purple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

void debug(std::string msg, int type){
    if (!DEBUG)
        return ;
    if (type == BEGIN)
        std::cout << "\e[0;35m Entering the function : " << msg << "\e[0m" << std::endl;
    else if (type == END)
        std::cout << "\e[0;35m Leaving the function : " << msg << " \e[0m" << std::endl;
    else 
        std::cout << "\e[0;35m DEBUG HERE " << " \e[0m" << std::endl;
}