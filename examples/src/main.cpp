#include "ANSI.hpp"
#include "Server.hpp"
#include <iostream>
#include <ostream>
#include <sys/socket.h>

#define BUF_SIZE 1024

void	splash_screen()
{
	std::cout << CYAN "\rWelcome to the Death Stranding!" RESET <<  std::endl;
}

int	main()
{
	Server	server;

	splash_screen();

	server.setUpServer();

	return (0);
}
