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

#include "IRPL.hpp"

#include <iomanip>
#include <sstream>

#include "IError.hpp"
#include "IError_populated.hpp"
#include "IRPL_populated.hpp"
#include "Server.hpp"

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
	: IRPL(002, "Your host is " SERVER_NAME_DFLT ", running version 1.0") {};
RPL_YOURHOST::~RPL_YOURHOST(void) {};

RPL_CREATED::RPL_CREATED()
	: IRPL(003, "This server was created by " IRC_SERVER_AUTHORS " and is "
				"running on a custom IRC server implementation "
				"(version:" IRC_SERVER_VERSION ".") {};
RPL_CREATED::~RPL_CREATED(void) {};

RPL_MYINFO::RPL_MYINFO()
	: IRPL(004, SERVER_NAME_DFLT
		   " " IRC_SERVER_VERSION
		   " " /* available user modes   available chanel modes*/) {}
RPL_MYINFO::~RPL_MYINFO() {};

RPL_BOUNCE::RPL_BOUNCE()
	: IRPL(005, ""){
	// TODO:
	// implement when server is multi-server capable
	//	- pick a server not full in list of connected server,
	//	- set _s to "Try server <server_name>, port <port_number>"
	//	end.
};
RPL_BOUNCE::~RPL_BOUNCE(){};



////////////////////////////////////////////////////////////////////////////////
//									 ------									  //
//									 errors									  //
//									 ------									  //
////////////////////////////////////////////////////////////////////////////////

ERR_UNKNOWNCOMMAND::ERR_UNKNOWNCOMMAND(const std::string &cmd_predicate)
	: IError(421, cmd_predicate + ": Unknown command") {};
ERR_UNKNOWNCOMMAND::~ERR_UNKNOWNCOMMAND(void) throw() {}

ERR_NONICKNAMEGIVEN::ERR_NONICKNAMEGIVEN() : IError(431, "No nick given") {};
ERR_NONICKNAMEGIVEN::~ERR_NONICKNAMEGIVEN() throw() {}

ERR_ERRONEUSNICKNAME::ERR_ERRONEUSNICKNAME(const std::string &nick)
	: IError(432, nick + ": Erroneous nickname") {}
ERR_ERRONEUSNICKNAME::~ERR_ERRONEUSNICKNAME(void) throw() {}

ERR_NICKNAMEINUSE::ERR_NICKNAMEINUSE(const std::string &nick)
	: IError(433, nick + ": Nickname is already in use") {}
ERR_NICKNAMEINUSE::~ERR_NICKNAMEINUSE(void) throw() {}

ERR_NEEDMOREPARAMS::ERR_NEEDMOREPARAMS(const std::string &cmd)
	: IError(461, cmd + ": Not enough parameters") {}
ERR_NEEDMOREPARAMS::~ERR_NEEDMOREPARAMS(void) throw() {}

ERR_ALREADYREGISTERED::ERR_ALREADYREGISTERED()
	: IError(462, "You may not reregister") {};
ERR_ALREADYREGISTERED::~ERR_ALREADYREGISTERED(void) throw() {}

ERR_PASSWDMISMATCH::ERR_PASSWDMISMATCH()
	: IError(464, "Password incorrect") {};
ERR_PASSWDMISMATCH::~ERR_PASSWDMISMATCH(void) throw() {}

