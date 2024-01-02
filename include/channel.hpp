/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvautrot <mvautrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 16:15:19 by mvautrot          #+#    #+#             */
/*   Updated: 2024/01/02 16:15:21 by mvautrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>


class channel {

	public:
		channel();
		channel(const channel& rhs);
		channel& operator=(const channel& rhs);
		~channel();

	private:

};

std::ostream& operator<<(std::ostream& o, const channel& rhs);
