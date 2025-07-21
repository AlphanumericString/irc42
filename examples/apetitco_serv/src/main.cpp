#include <iostream>

#include "ANSI.hpp"
#include "Server.hpp"

#define BUF_SIZE 1024

void	splash_screen()
{
	std::cout << ANSI_CYAN "\rWelcome to the Death Stranding!" ANSI_RESET <<  std::endl;
}

/// @brief The main function.
/// @return Returns 0 if everything went well, any non-null value otherwise.
int	main()
{
	Server	server;

	splash_screen();

	server.setUpServer();

	while (server.getServerState()->getStatus() == ServerState::RUNNING) {
		server.handleEvent();
	}

	return (0);
}
