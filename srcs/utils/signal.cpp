/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purple <purple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 11:34:34 by purple            #+#    #+#             */
/*   Updated: 2023/12/28 11:19:10 by purple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

void	handle_signal(int signal) {

	debug("handle_signal", BEGIN);	
	(void)signal;
	handleSignal = true;
	std::cout << "\x1b[31m \x1b[3m [Interruption detected] Stopping... \x1b[0m" << std::endl;
	debug("handle_signal", END);	
	return;
}