/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purple <medpurple@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 17:33:39 by purple            #+#    #+#             */
/*   Updated: 2023/12/27 22:16:39 by purple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "irc.hpp"


class user
{
public :
// Coplien
            user();
            user(const user& rhs);
            user &operator=(const user& rhs);
            ~user();

// Operator
// Setter / Getter
// Function
protected :

private :
    		void 				_display_constructor(std::string msg);
};


#define USER_DC "[Default] Constructor called for USER CLASS"
#define USER_PC "[Parametric] Constructor called for USER CLASS"
#define USER_CC "[Copy] Constructor called for USER CLASS"
#define USER_AO "[Attribution] Operator called for USER CLASS"
#define USER_DD "[Default] Destructor called for USER CLASS"