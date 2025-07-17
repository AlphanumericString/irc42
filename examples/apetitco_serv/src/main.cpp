#include <iostream>

#include "ANSI.hpp"
#include "Server.hpp"

#define BUF_SIZE 1024

void	splash_screen()
{
	std::cout << ANSI_CYAN "\rWelcome to the Death Stranding!" ANSI_RESET <<  std::endl;
}

int	main()
{
	Server	server;

	splash_screen();

	server.setUpServer();

	return (0);
}
