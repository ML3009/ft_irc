/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purple <medpurple@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 17:31:52 by purple            #+#    #+#             */
/*   Updated: 2023/12/25 17:31:53 by purple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

void try_args(int ac, char **av){
	ac == 3 ? void() : throw NumberArgException();
	for (int i = 0; av[1][i]; i++)
		isdigit(av[1][i]) ? void() : throw TypeArgException();
	!(strtol(av[1], NULL, 10) < 1024 || strtol(av[1], NULL, 10) > 65535) ? void() : throw TypeArgException() ;
	return;
}