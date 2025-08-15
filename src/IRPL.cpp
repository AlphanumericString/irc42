/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRPL.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoulard <bgoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 13:41:24 by bgoulard          #+#    #+#             */
/*   Updated: 2025/08/15 13:41:24 by bgoulard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iomanip>
#include <sstream>

#include "IRPL.hpp"

std::string IRPL::toString(const Server &s, const Client &c) {
	std::stringstream ss;

	ss << ":" << s.getServerState().getName() << " ";
	ss << std::setw(3) << std::setfill('0') << _code;
	ss << " " << c.getNick() << " :" << string << "\r\n";
	return ss.str();
}

RPL_WELCOME::RPL_WELCOME(const std::string &nick, const std::string &c_hostname)
	: IRPL(001, "Welcome to the Internet Relay Network " + nick + "!" + nick +
					"@" + c_hostname) {};
RPL_WELCOME::~RPL_WELCOME(void) {};

RPL_YOURHOST::RPL_YOURHOST()
	: IRPL(002, "Your host is ircserv, running version 1.0") {};
RPL_YOURHOST::~RPL_YOURHOST(void) {};

RPL_CREATED::RPL_CREATED()
	: IRPL(003, "This server was created by bgoulard & apetitco and is "
				"running on a custom IRC server implementation.") {};
RPL_CREATED::~RPL_CREATED(void) {};
