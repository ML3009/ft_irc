/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purple <purple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 11:34:34 by purple            #+#    #+#             */
/*   Updated: 2023/12/21 11:45:53 by purple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

void	handle_signal(int signal) {

	(void)signal;
	handleSignal = true;
	std::cout << "\x1b[31m \x1b[3m [Interruption detected] Stopping... \x1b[0m" << std::endl;
	return;
}