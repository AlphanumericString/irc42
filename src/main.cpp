/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoulard <bgoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:14:36 by bgoulard          #+#    #+#             */
/*   Updated: 2025/09/17 11:10:06 by bgoulard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <vector>

#include "Server.hpp"
#include "ansi.h"
#include "generics.hpp"
#include "smart_ptr.hpp"

static int version_handl(std::vector< std::string >::iterator *it) {
	std::cout << "Version " << IRC_SERVER_VERSION << " by "
			  << IRC_SERVER_AUTHORS << "." << std::endl;
	*it = (*it)++;
	return (0);
}

static int help_handl(std::vector< std::string >::iterator *it) {
	std::cerr << "Use: ./ircserv <port> <password>" << std::endl;
	*it = (*it)++;
	return (0);
}

static bool parse_args(std::vector< std::string > &args, std::string *pwd,
					   std::string *p) {
	std::vector< std::string >::iterator it;
	std::pair< std::string, int (*)(std::vector< std::string >::iterator *) >
		opts[] = {
			std::make_pair("--version", version_handl),
			std::make_pair("--help", help_handl),
		};

	if (args.size() < 3)
		return (std::cerr << "Use: ./ircserv <port> <password>" << std::endl,
				false);
	if (args.size() < 2) {
		std::cout << "Using default value for port of:" << SERVER_PORT_DFLT
				  << std::endl
				  << "Using default value for password of:" << SERVER_PWD_DFLT
				  << std::endl;
		args.push_back(to_string(SERVER_PORT_DFLT));
		args.push_back(SERVER_PWD_DFLT);
	}
	it = args.begin();
	it++;
	for (; it != args.end() - 2; it++) {
		for (size_t i = 0; i < CTAB_SIZE(opts); i++)
			if (opts[i].first.compare(*it) != 0)
				opts[i].second(&it);
	}
	*p = *(it++);
	*pwd = *(it++);

	if (std::atoi(p->c_str()) < 1024 || std::atoi(p->c_str()) > 49151)
	{
		std::cout << "port outside of accessible ranges. "
			"[try standard IRC port such as 6667]" << std::endl;
		return (false);
	}
	if (pwd->find_first_not_of(ALNUM, 0) != std::string::npos)
	{
		std::cout << "Password must be comprised only of alpha numeric characters."
			"[try a standard Password such as `password`]." << std::endl;
		return (false);
	}
	return (true);
}

int main(int argc, char *argv[]) {
	std::vector< std::string > args(argv, argv + argc);
	std::string				   passwd;
	std::string				   port;

	if (parse_args(args, &passwd, &port) == false)
		return (EXIT_FAILURE);
	Server server(std::atoi(port.c_str()), passwd);
	try {
		server.mainLoop();
		close(server.getServerFD());
		return (server.exit_state());
	} catch (...) {
		std::cerr << "unhandled critical error in server :(" << std::endl;
		std::cerr << "Exiting..." << std::endl;
	}
	return (EXIT_FAILURE);
}
