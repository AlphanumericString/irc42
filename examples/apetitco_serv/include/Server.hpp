#ifndef SERVER_HPP
#define SERVER_HPP

#include <string>

#include "Channel.hpp"
#include "Client.hpp"
#include "ServerState.hpp"

#define SERVER_PORT_DFLT	"2106"
#define SERVER_PWD_DFLT		"password"
#define SERVER_NAME_DFLT	"42irc_server_apbg"
#define BACKLOG 10

class Server
{
private:
	int			_epollFD;		//-> FD for the listened port.
	Client		*_clients;		//-> Pointer to _serverState's list of clients.
	Channel		*_channels;		//-> Pointer to _serverState's list of channels.
	ServerState	*_serverState;	//-> Pointer to _serverState.

	void	hintsSetUp(struct addrinfo *hints);

public:
	// Constructors
		Server();
		Server(const Server &);
	// Destructors
		~Server();
	// Operator overloads
		Server &operator=(const Server &);
	// Getters
		int const	&getEpollFD() const;
	// Setters
		void	setEpollFD(int epollFD);
	// Member functions
		void	capHandling();
		void	bindAddress();
		void	setUpServer();
		void	work();
		void	woINpr();
	// Exceptions
};

#endif // !SERVER_HPP
