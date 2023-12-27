/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purple <medpurple@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 17:32:31 by purple            #+#    #+#             */
/*   Updated: 2023/12/27 22:18:10 by purple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "user.hpp"




/*----------------- Coplien ------------- */

user::user(){
	CONSTRUCTOR ? _display_constructor(USER_DC) : void ();

}

user::user(const user& rhs){
    
    *this = rhs; 
	CONSTRUCTOR ? _display_constructor(USER_DC) : void ();

}

user&	user::operator=(const user& rhs){

	if (this != &rhs)
		*this = rhs;
	CONSTRUCTOR ? _display_constructor(USER_AO) : void ();
	return *this;
}

user::~user(){
	CONSTRUCTOR ? _display_constructor(SERVER_DD) : void ();

}


/*---------------- Operator ------------- */

/*---------- Getter / Setter ------------ */


/*--------------- Function -------------- */

void user::_display_constructor(std::string msg){
    std::cout << "\x1b[33m \x1b[3m" << msg << "\x1b[0m" << std::endl;
}

/*--------------- Exception ------------- */
