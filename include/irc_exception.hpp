/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc_exception.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purple <purple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 11:23:07 by purple            #+#    #+#             */
/*   Updated: 2023/12/28 15:46:43 by purple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

class NumberArgException : public std::exception {
	const char *what() const throw(){
   		return ("\x1b[31m \x1b[3m Usage : ./ircserv <port> <password> \x1b[0m");}
};

class TypeArgException : public std::exception {
	const char *what() const throw(){
    	return ("\x1b[31m \x1b[3m Error: port must be included between 1024 and 65535. \x1b[0m");}
};

class socketException : public std::exception {
	const char *what() const throw(){
    	return ("\x1b[31m \x1b[3m Error: socket creation failed. \x1b[0m");}
};

class bindException : public std::exception {
	const char *what() const throw(){
    	return ("\x1b[31m \x1b[3m Error: bind failed. \x1b[0m");}
};

class listenException : public std::exception {
	const char *what() const throw(){
    	return ("\x1b[31m \x1b[3m Error: listen failed. \x1b[0m");}
};

class socketoptException : public std::exception {
	const char *what() const throw(){
    	return ("\x1b[31m \x1b[3m Error: socket option failed. \x1b[0m");}
};

class fcntlException : public std::exception {
	const char *what() const throw(){
    	return ("\x1b[31m \x1b[3m Error: fcntl failed. \x1b[0m");}
};

class pollException : public std::exception {
	const char *what() const throw(){
    	return ("\x1b[31m \x1b[3m Error: poll failed. \x1b[0m");}
};

class acceptException : public std::exception {
	const char *what() const throw(){
    	return ("\x1b[31m \x1b[3m Error: poll failed. \x1b[0m");}
};

class userException : public std::exception {
	const char *what() const throw(){
    	return ("\x1b[31m \x1b[3m Error: user not found. \x1b[0m");}
};