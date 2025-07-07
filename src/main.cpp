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

#include <cstdlib>
#include <iostream>

#include "Server.hpp"

static bool	parse_args(char *argv[], int argc)
{
	if (argc < 2)
		std::cout 
			<< "Using default value for port of:" << SERVER_PORT_DFLT << std::endl
			<< "Using default value for password of:" << SERVER_PWD_DFLT << std::endl;
	for (size_t i = 0; argv[1][i] ; i++)
	{
		if (argv[1][i] < '0' || argv[1][i] > '9')
			return false;
	}

	// TODO: Check for correct password (no white spaces for instance)

	return (true);
}

int	main(int argc, char *argv[])
{
	Server	*server;

	// maybe in parse arg ? + what is the use of default values if this is here?
	if (argc != 3)
		return (std::cerr << "Use: ./ircserv <port> <password>" << std::endl, 1);

	if (parse_args(argv, argc) == false)
		return (1);
	server = new Server(std::atoi(argv[1]), argv[2]);
	delete server;
}
