/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purple <medpurple@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:56:05 by purple            #+#    #+#             */
/*   Updated: 2024/01/07 21:48:04 by purple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "irc.hpp"


class bot
{
    public			:
    // Coplien
                bot();
                bot(const bot& rhs);
                bot &operator=(const bot& rhs);
                ~bot();

    // Operator
    // Setter / Getter
                void        getfact(server &server, user &client, int i);
                std::string getName() const;
    // Function
                void        help(server &server, user &client);
                void        sayhello(server &server, user &client);
    protected   	:

    private     	:
                        std::map<int, std::string> _factmap;
                        std::string _name;

};