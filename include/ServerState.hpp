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
	std::string			_password;
	int					_port;
	std::list<Client>	_clients;
	std::list<Channel>	_channels;

public:
	// Constructors
	ServerState();
	ServerState(ServerState const &original);
	ServerState(int port, const std::string password);
	// Destructors
	~ServerState();
	// Operator overloads
	ServerState	&operator=(ServerState const &original);
	// Getters
	std::string const	&getName() const;
	std::string const	&getPassword() const;
	int const			&getPort() const;
	// Setters
	// Member functions
	// Exceptions
};

#endif // !SERVERSTATE_HPP
