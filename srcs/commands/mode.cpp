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

int isValidArgMod(char mod) {
	
	char ptr_mod[5] = {'i', 't', 'o', 'k', 'l'};

	for (int i = 0; i < 5; ++i) {
		if (mod == ptr_mod[i])
			return i;
	}
	return UNKNOW_MODE;
}
