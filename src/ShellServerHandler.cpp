/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShellServerHandler.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoulard <bgoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:04:59 by bgoulard          #+#    #+#             */
/*   Updated: 2025/08/07 16:27:36 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShellServerHandler.hpp"

#include <cerrno>
#include <iostream>
#include <string>

#include "Channel.hpp"
#include "Client.hpp"

void ShellServerHandler::cmdHandler(Server &server, std::string line) {
	ShellServerHandler::strToCmd(line, server);
	std::cout << "$> " << std::flush;
}

/// @todo Implement this function.
int ShellServerHandler::handle_monitor(std::string s, Server &serv) {
	(void)s; // maybe flags to display chanels list + user lists ? idk
	std::cout << serv.getServerState() << std::endl;
	return (0);
}

/// @todo Implement this function.
int ShellServerHandler::handle_quit(std::string s, Server &serv) {
	(void)s;
	serv.setServerState(ServerState::STOPPING);
	return (0);
}

/// @todo Implement this function.
int ShellServerHandler::handle_test(std::string s, Server &serv) {
	(void)s;
	(void)serv;

	std::string test = "PASS toto42\r\n"
					   "NICK testo\r\n"
					   "USER test 0 * :test\r\n";
	std::cout << "Testing msg with: " << std::endl;
	std::cout << test << std::endl;
	Client t_client = Client();

	t_client.appendInputBuffer(test.c_str(), test.length());
	t_client.processInput(serv);

	std::cout << "Output buffer: " << t_client.getOutputBuffer() << std::endl;

	// step 1:
	//	create users and exit					- check no leaks + no mem errs
	//	create channels and exit				- check no leaks + no mem errs
	//	create users and push them to chanels	- ...
	// step 2:
	//	tests in cli with irssi?
	//	idk too far atm

	return (0);
}

ShellServerHandler::ShellServerCmd ShellServerHandler::strToCmd(std::string s,
																Server &serv) {
	if (!s.compare("test") || !s.compare("t"))
		return (ShellServerHandler::handle_test(s, serv),
				ShellServerHandler::DISPLAY_INFO);
	if (!s.compare("monitor") || !s.compare("mon"))
		return (ShellServerHandler::handle_monitor(s, serv),
				ShellServerHandler::DISPLAY_INFO);
	if (!s.compare("quit") || !s.compare("exit"))
		return (ShellServerHandler::handle_quit(s, serv),
				ShellServerHandler::QUIT);
	std::cout << "Error:Unknown command:" << s << std::endl;
	return (ShellServerHandler::UNKNOWN);
}
