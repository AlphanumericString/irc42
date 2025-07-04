#ifndef SERVER_HPP
#define SERVER_HPP

#include "Channel.hpp"
#include "Client.hpp"
#include "ServerState.hpp"

class	Server
{
private:
	int			_epollFD;		//->
	Client		*_clients;		//-> Pointer/Reference to _serverState's list of clients.
	Channel		*_channels;		//-> Pointer/Reference to _serverState's list of channels.
	ServerState	_serverState;	//-> Self-explanatory
	//Event Loop
	//Main loop

public:
	// Constructors
	Server();
	Server(const Server &original);
	Server(int port, const std::string password);
	// Destructors
	~Server();
	// Operator overloads
	Server	&operator=(const Server&original);
	// Getters
	// Setters
	// Member functions
	// Exceptions
};

#endif // !SERVER_HPP
