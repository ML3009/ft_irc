/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc_fct.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purple <purple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 11:28:38 by purple            #+#    #+#             */
/*   Updated: 2024/01/02 16:12:07 by purple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

/* PARSING */
void	                try_args(int ac, char **av);

/* SIGNAL  */
void	                handle_signal(int signal);

/* DEBUG   */
void	                debug(std::string msg, int type);
void 	                display_constructor(std::string msg);

/* UTILS   */
bool                     completeCommand(std::string msg);
std::vector<std::string> splitArgs(std::string buffer);

