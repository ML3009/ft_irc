/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvautrot <mvautrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:18:24 by mvautrot          #+#    #+#             */
/*   Updated: 2024/01/11 16:57:45 by mvautrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.hpp"

// std::vector<std::string> splitCmdMode(std::vector<std::string> buffer, int pos){
// 	std::vector<std::string> tmp_buffer;
// 	for (unsigned long i = pos; i != buffer.size(); ++i) {
// 		std::cout << "buffer[i]: " << buffer[i] << std::endl;
// 		tmp_buffer.push_back(buffer[i]);
// 	}
// 	return tmp_buffer;
// }

int isValidArgMod(server &Server, user &Client, channel &Channel, char mod) {

	(void)Client;
	(void)Server;
	(void)Channel;
	std::cout << "MOD: " << mod << std::endl;

	if (mod == 'i')
		return MODE_I;
	if (mod == 't')
		return MODE_T;
	if (mod == 'o')
		return MODE_O;
	if (mod == 'k')
		return MODE_K;
	if (mod == 'l')
		return MODE_L;
	return UNKNOW_MODE;
}
