/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoulard <bgoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:14:36 by bgoulard          #+#    #+#             */
/*   Updated: 2025/07/07 13:14:36 by bgoulard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>
#include <cstdlib>
#include <iostream>
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
	std::cout << "Use: ./ircserv <port> <password>" << std::endl;
	*it = (*it)++;
	std::cout << "Options:" << std::endl;
	std::cout << "  --version\t\tPrints the version of the server."
			  << std::endl;
	std::cout << "  --help\t\tPrints this help message." << std::endl;
	exit(EXIT_SUCCESS);
}

static void print_err(const std::string &s) {
	std::cerr << BRED << "[Error] " << s << COLOR_RESET << std::endl;
}

static void print_warning(const std::string &s) {
	std::cerr << BYEL << "[Warning] " << s << COLOR_RESET << std::endl;
}

static bool port_ok(const std::string &port) {
	int p_i;

	if (port.find_first_not_of(NUM) != std::string::npos || port.length() > 10)
		return (print_err(
					"Port must be a valid positive integer number without signs"
					" comprised in the range [1024, 65535]."),
				false);
	p_i = std::atoi(port.c_str());
	if (p_i < 1024)
		return (print_err("Ports below 1024 are system reserved."), false);
	if (p_i > 65535)
		return (print_err("Ports above 65535 are invalid."), false);

	if (p_i < 6665 || p_i > 6669)
		print_warning("Recomended ports for IRC are in range [6665, 6669].");
	return (true);
}

static bool pwd_ok(const std::string &pwd) {
	if (pwd.length() < 6 || pwd.length() > 64)
		return (print_err("Password must be between 6 and 64 characters."),
				false);
	if (std::string(ALPHA).find(pwd.at(0)) == std::string::npos)
		return (print_err("Password must start with an alphabetic character."),
				false);
	if (pwd.find_first_not_of(ALNUM) != std::string::npos) {
		return (
			print_err(std::string(
						  "Password must only contain alphanumeric characters."
						  " Invalid char '") +
					  pwd.at(pwd.find_first_not_of(ALNUM)) + "'."),
			false);
	}
	return (true);
}

static bool __attribute_maybe_unused__
parse_args(std::vector< std::string > &args, std::string *pwd, std::string *p) {
	std::vector< std::string >::iterator it;
	std::pair< std::string, int (*)(std::vector< std::string >::iterator *) >
		opts[] = {
			std::make_pair("--version", version_handl),
			std::make_pair("--help", help_handl),
		};

	it = args.begin();
	it++;
	for (; it != args.end(); it++) {
		if (it->find("--") != 0)
			break;
		for (size_t i = 0; i < CTAB_SIZE(opts); i++)
			if (opts[i].first.compare(*it) == 0)
				opts[i].second(&it);
	}
	if (args.size() - std::distance(args.begin(), it) < 2) {
		if (args.size() - std::distance(args.begin(), it) < 1) {
			print_warning("Using default value for port of: " +
						  to_string(SERVER_PORT_DFLT));
			args.push_back(to_string(SERVER_PORT_DFLT));
		}
		print_warning("Using default value for password of: " SERVER_PWD_DFLT);
		args.push_back(SERVER_PWD_DFLT);

		it = args.end() - 2;
	}
	*p = *(it++);
	*pwd = *(it++);
	if (pwd->empty() || p->empty())
		return (print_err("Password and port must not be empty."), false);
	if (port_ok(*p) != true || pwd_ok(*pwd) != true)
		return (false);
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
		server.run();
		return (server.exit_state());
	} catch (...) {
		print_err("Unhandled critical error in server :(");
	}
	return (EXIT_FAILURE);
}
