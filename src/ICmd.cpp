/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ICmd.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoulard <bgoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 16:08:31 by bgoulard          #+#    #+#             */
/*   Updated: 2025/08/15 16:08:31 by bgoulard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ICmd.hpp"
#include "IError.hpp"

std::vector< IRPL > CMD_PASS::execute(Server &s, Client &clien_requesting) {
	std::vector< IRPL > ret;

	if (_args.size() < CMD_PASS::minArg)
		ret.push_back(ERR_NEEDMOREPARAM(_args[0]));
	else if (clien_requesting.getConState() != REGISTERING_PASS &&
			 clien_requesting.getConState() != NOT_LOGGED)
		ret.push_back(ERR_ALREADYREGISTRED());
	else if (s.getServerState().getPassword().compare(_args[1]) != 0)
		ret.push_back(ERR_PASSWDMISMATCH());
	if (ret.size() > 0)
		return ret;
	_response.clear();
	clien_requesting.setConState(REGISTERING_PASS);
	return std::vector< IRPL >(); // return empty
}

std::vector< IRPL > CMD_NICK::execute(Server &s, Client &clien_requesting) {
	std::vector< IRPL > ret;

	if (_args.size() < CMD_NICK::minArg)
		ret.push_back(ERR_NONICKNAMEGIVEN());
	else if (_args[1].find_first_not_of(ALNUM) != std::string::npos ||
			 _args[1].length() > 9)
		ret.push_back(ERR_ERRONEUSNICKNAME(_args[1]));

	for (std::list< Client >::const_iterator it =
			 s.getServerState().getClients().begin();
		 it != s.getServerState().getClients().end() && ret.size() == 0; it++)
		if (it->getNick().compare(_args[1]) == 0)
			ret.push_back(ERR_NICKNAMEINUSE(_args[1]));

	try {
		clien_requesting.setNickname(_args[1]);
	} catch (...) {
		ret.push_back(ERR_ERRONEUSNICKNAME(_args[1]));
	}
	// @TODO:
	//  multi-server setup require to transmit nick to followupservers
	//  and call ERR_NICKCOLISION if nick is already present in other server
	//  theres somthing abou a command kill bu i didnt get it @ 3am lol
	clien_requesting.setConState(REGISTERING_NICK);
	return std::vector< IRPL >(); // return empty
};

std::vector< IRPL > CMD_USER::execute(Server &s, Client &clien_requesting) {
	std::vector< IRPL > ret;
	std::string			_real_name;
	if (clien_requesting.getConState() != REGISTERING_NICK)
		ret.push_back(ERR_ALREADYREGISTRED());
	else if (_raw.find_last_of(":") == std::string::npos ||
			 _args.size() < CMD_USER::minArgs)
		ret.push_back(ERR_NEEDMOREPARAM(_args[0]));

	if (ret.size() > 0)
		return ret;
	// something to do with serve connection & regisetering a new user
	// still dont get the multiserver setup
	(void)s; // unused for now

	_real_name = _raw.substr(_raw.find_last_of(":"));
	clien_requesting.setName(_args[1]);
	clien_requesting.setHost(_args[2]);
	clien_requesting.setRealname(_real_name);
	const std::string c_hostname = clien_requesting.getHost();

	ret.push_back(RPL_WELCOME(clien_requesting.getName(), c_hostname));
	ret.push_back(RPL_YOURHOST());
	ret.push_back(RPL_CREATED());
	return ret;
}

