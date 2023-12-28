/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc_fct.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purple <purple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 11:28:38 by purple            #+#    #+#             */
/*   Updated: 2023/12/28 11:28:39 by purple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

void	try_args(int ac, char **av);
void	handle_signal(int signal);
void	debug(std::string msg, int type);