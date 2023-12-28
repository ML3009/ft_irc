/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc_fct.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purple <medpurple@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 11:28:38 by purple            #+#    #+#             */
/*   Updated: 2023/12/28 20:32:32 by purple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

void	try_args(int ac, char **av);
void	handle_signal(int signal);
void	debug(std::string msg, int type);
void 	display_constructor(std::string msg);
