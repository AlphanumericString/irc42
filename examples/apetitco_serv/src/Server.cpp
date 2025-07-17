#include <cstring>
#include <cstdlib>
#include <iostream>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <stdio.h>

#include "Server.hpp"
#include "ServerState.hpp"

///CONSTRUCTORS/////////////////////////////////////////////////////////////////
Server::Server() : _epollFD(-1)
{

}

///DESTRUCTORS//////////////////////////////////////////////////////////////////
Server::~Server()
{}

///OPERATOR OVERLOADS///////////////////////////////////////////////////////////
///GETTERS//////////////////////////////////////////////////////////////////////
int const	&Server::getEpollFD() const
{
	return (this->_epollFD);
}

///SETTERS//////////////////////////////////////////////////////////////////////
void	Server::setEpollFD(int epollFD)
{
	this->_epollFD = epollFD;
}

///MEMBER FUNCTIONS/////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @brief
/// Sets up hints for the socket.
/// @param hints
/// Pointer to the hints structure that we want to set up.
/// @details
/// Sets up the preffered protocol family for the socket (IPv4, IPv6 or both),
/// as well as the socket type (SOCK_STREAM or SOCK_DGRAM) and the input flags.
////////////////////////////////////////////////////////////////////////////////
void	Server::hintsSetUp(struct addrinfo *hints)
{
	std::cout << "Setting up hints" << std::endl;

	memset(hints, 0, sizeof(*hints));
	hints->ai_family = AF_INET;
	hints->ai_socktype = SOCK_STREAM;
	hints->ai_flags = AI_PASSIVE;
}

void	*getInAddr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET)
	{
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}

	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

void	Server::capHandling()
{
		//
}

void	Server::bindAddress()
{
	struct sockaddr_in sock_add;

	sock_add.sin_family = AF_INET;
	sock_add.sin_port = htons(std::atoi(this->_serverState->getPort().c_str()));
	sock_add.sin_addr.s_addr = INADDR_ANY;

	std::cout << "Looking for a bind-able socket address..." << std::endl;

	if (bind(this->getEpollFD(), (struct sockaddr *)&sock_add, sizeof(sock_add)) == -1)
	{
		close(this->getEpollFD());
		perror("server: bind");
		return;
	}
}

////////////////////////////////////////////////////////////////////////////////
/// @brief
/// Sets the server up.
/// @details
////////////////////////////////////////////////////////////////////////////////
void	Server::setUpServer()
{

	std::cout << "Setting server up..." << std::endl;

	bindAddress();

	if (listen(this->getEpollFD(), BACKLOG) == -1)
	{
		perror("listen");
		std::exit(1);
	}

	std::cout << "Server is up!" << std::endl;

}

void	Server::woINpr()
{
	int	newFD;
	struct sockaddr_storage	theirAddr;
	socklen_t	sinSize;
	char	s[INET_ADDRSTRLEN];
	std::cout << "Waiting for connections..." << std::endl;

	char	buffer[1024];
	int numbytes;
	memset(buffer, 0, sizeof(buffer));
	sinSize = sizeof(theirAddr);
	newFD = accept(this->getEpollFD(), (struct sockaddr*)&theirAddr, &sinSize);
	if (newFD == -1)
	{
		perror("accept");
	}

	inet_ntop(theirAddr.ss_family, getInAddr((struct sockaddr*)&theirAddr), s, sizeof(s));
	std::cout << "server: got connection from " << s << std::endl;

	//CAP handling
	capHandling();
	std::string	cap_ls = "CAP * LS :multi-prefix sasl\r\n";
	send(newFD, cap_ls.c_str(), sizeof(cap_ls), 0);
	std::string	cap_ack = "CAP * ACK multi-prefix\r\n";
	send(newFD, cap_ack.c_str(), sizeof(cap_ack), 0);

	while (1)
	{
		bzero(buffer,sizeof(buffer));
		if ((numbytes = recv(newFD, buffer, sizeof(buffer) - 1, 0)) == -1)
			perror("recv");
		buffer[numbytes] = 0;

		if (buffer[0] != '\0')
		{
			std::cout << "Server received: " << buffer << std::endl;
			send(newFD, buffer, sizeof(buffer), 0);
		}
	}
}

///EXCEPTIONS///////////////////////////////////////////////////////////////////
