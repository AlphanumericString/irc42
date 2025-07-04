#ifndef SERVERSTATE_HPP
#define SERVERSTATE_HPP

#include <string>
#include <list>

#include "Channel.hpp"
#include "Client.hpp"

class	ServerState
{
private:
	std::string			_name;
	std::list<Client>	_clients;
	std::list<Channel>	_channels;

public:
	// Constructors
	ServerState();
	ServerState(ServerState const &original);
	// Destructors
	~ServerState();
	// Operator overloads
	ServerState	&operator=(ServerState const &original);
	// Getters
	// Setters
	// Member functions
	// Exceptions
};

#endif // !SERVERSTATE_HPP
