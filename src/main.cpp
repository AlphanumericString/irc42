#include <cstdlib>
#include <iostream>

#include "Server.hpp"

bool	parse_args(char *argv[], int argc)
{
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

	if (argc != 3)
		return (std::cerr << "Use: ./ircserv <port> <password>" << std::endl, 1);

	if (parse_args(argv, argc) == false)
		return (1);
	server = new Server(std::atoi(argv[1]), argv[2]);





	delete server;
}
