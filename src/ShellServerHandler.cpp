/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShellServerHandler.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoulard <bgoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:04:59 by bgoulard          #+#    #+#             */
/*   Updated: 2025/09/10 17:28:26 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShellServerHandler.hpp"

#include <cerrno>
#include <iostream>
#include <ostream>
#include <string>

#include "Channel.hpp"
#include "Client.hpp"
#include "ConnectionState.hpp"
#include "generics.hpp"
#include "smart_ptr.hpp"

void ShellServerHandler::cmdHandler(Server &server, std::string line) {
	ShellServerHandler::strToCmd(line, server);
	if (server.getServerState().isDebug() == false &&
		server.getServerState().getStatus() == ServerState::RUNNING)
		std::cout << "$> " << std::flush;
}

int ShellServerHandler::handle_monitor(std::string s, Server &serv) {
	(void)s; // maybe flags to display chanels list + user lists ? idk
	std::cout << serv.getServerState() << std::endl;
	return (0);
}

int ShellServerHandler::handle_quit(std::string s, Server &serv) {
	(void)s;
	serv.setServerState(ServerState::STOPPING);
	return (0);
}

static void dump_client(const Client *c) {
	std::cout << BBLU "-------------------------[client]-" WHT << std::endl;
	if (c == NULLPTR)
		return;
	std::cout << *c << std::endl;
}

/// @todo Prettify
static void dump_channel(const Channel *ch_) {
	std::cout << BBLU "------------------------[channel]-" WHT << std::endl;
	if (ch_ == NULLPTR)
		return;
	const Channel &ch = *ch_;

	std::cout << ch << std::endl;
	if (ch.getMode() & MODE_I) {
		if (!ch.getInvited().size())
			return (std::cout << "no invite on chan" << std::endl, (void)0);
		std::cout << "Invited users:" << std::endl;
		for (std::list< Client >::const_iterator it = ch.getInvited().begin();
			 it != ch.getInvited().end(); it++) {
			std::cout << "\t" << *it << std::endl;
		}
	}
}

int ShellServerHandler::handle_dump(std::string s, Server &serv) {

	std::vector< std::string > args = split(s, " ");

	if (args.size() < 2 || args.size() > 3) {
		std::cout
			<< "Usage: dump [channel|ch|client|c] <client nick|channel name>"
			<< std::endl;
		std::cout << serv.getServerState() << std::endl;
		return (1);
	} else if ((args[1] == "channel" || args[1] == "ch" || args[1] == "c" ||
				args[1] == "client") &&
			   args.size() < 3) {
		std::cout << "Usage: dump ";
		if (args[1] == "channel" || args[1] == "ch")
			std::cout << "channel <channel";
		else
			std::cout << "client <client";
		std::cout << " nick/name>" << std::endl;
		return (1);
	}

	if (args[1] != "channel" && args[1] != "ch" && args[1] != "client" &&
		args[1] != "c") {
		std::cout
			<< "Warning: dump target not specified, dumping any matching name"
			<< std::endl;
		dump_client(serv.getServerState().getClient(args[1]));
		if (args[1][0] != '#')
			args[1] = "#" + args[1];
		dump_channel(serv.getServerState().getChannel(args[1]));
	} else if (args[1] == "channel" || args[1] == "ch") {
		if (args[2][0] != '#')
			args[2] = "#" + args[2];
		dump_channel(serv.getServerState().getChannel(args[2]));
	} else {
		dump_client(serv.getServerState().getClient(args[2]));
	}
	return (0);
}

int ShellServerHandler::handle_test(std::string s, Server &serv) {
	(void)s;
	(void)serv;

	return (0);
}

int ShellServerHandler::handle_dbg(std::string s, Server &serv) {
	(void)s; // maybe use to get level of dbg?
	serv.getServerState().setDebug(!serv.getServerState().isDebug());
	if (!serv.getServerState().isDebug())
		return (0);
	std::cout << "Debug mode enabled" << std::endl;
	std::cout << "feel free to disable it again with 'dbg' or 'debug' command"
			  << std::endl;
	return (0);
}

ShellServerHandler::ShellServerCmd ShellServerHandler::strToCmd(std::string s,
																Server &serv) {
	std::vector< std::string > args = split(s, " ");

	if (serv.getServerState().isDebug() && s != "dbg" && s != "debug")
		return (ShellServerHandler::UNKNOWN);
	if (s.empty())
		return (ShellServerHandler::UNKNOWN);
	if (!s.compare("test") || !s.compare("t"))
		return (ShellServerHandler::handle_test(s, serv),
				ShellServerHandler::DISPLAY_INFO);
	if (!s.compare("monitor") || !s.compare("mon"))
		return (ShellServerHandler::handle_monitor(s, serv),
				ShellServerHandler::DISPLAY_INFO);
	if (!s.compare("debug") || !s.compare("dbg"))
		return (ShellServerHandler::handle_dbg(s, serv),
				ShellServerHandler::DISPLAY_INFO);
	if (!s.compare("quit") || !s.compare("exit"))
		return (ShellServerHandler::handle_quit(s, serv),
				ShellServerHandler::QUIT);
	if (!args[0].compare("dump") || !args[0].compare("d"))
		return (ShellServerHandler::handle_dump(s, serv),
				ShellServerHandler::DISPLAY_INFO);
	std::cout << "Error:Unknown command:" << s << std::endl;
	return (ShellServerHandler::UNKNOWN);
}
