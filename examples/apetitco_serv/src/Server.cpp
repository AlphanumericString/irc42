/**
 * @file
 * @ingroup ServerGroup
 * @brief Implementation of the Server class' methods.
 */

/**
 * @defgroup ServerGroup Module Server.
 * @brief Everything touching to the IRC server.
 */

#include <cstring>
#include <cstdlib>
#include <fcntl.h>
#include <iostream>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <stdio.h>

#include "Server.hpp"
#include "ServerState.hpp"

/**
 * @brief Default constructor for the Server class.
 */
Server::Server() : _epollFD(-1)
{

}

/**
 * @brief Default destructor for the Server class.
 */
Server::~Server()
{}

/**
 * @brief Server's operator overload for the equal operator.
 *
 * @param original The Server instance we want to assign from.
 * @return A reference to the assigned Server instance.
 */
Server &Server::operator=(const Server &other)
{
	if (this != &other)
	{

	}
	return (*this);
}

/**
 * @brief The getter for the _epollFD field.
 *
 * @return The value of this->_epollFD.
 */
int const	&Server::getEpollFD() const
{
	return (this->_epollFD);
}

/**
 * @brief The getter for the _serverFD field.
 *
 * @return The value of this->serverFD.
 */
int	const	&Server::getServerFD() const
{
	return (this->_serverFD);
}

/**
 * @brief The setter for the _epollFD field.
 *
 * @param fd The file descriptor we want to assign to this->_epollFD.
 */
void	Server::setEpollFD(int fd)
{
	this->_epollFD = fd;
}

/**
 * @brief The setter for the _serverFD field.
 *
 * @param fd The file descriptor we want to assign to this->_serverFD.
 */
void	Server::setServerFD(int fd)
{
	this->_serverFD = fd;
}

/**
 * @brief Binds this->_serverFD to any inbound address.
 */
void	Server::bindSocket()
{
	struct sockaddr_in sock_add;

	sock_add.sin_family = AF_INET;
	sock_add.sin_addr.s_addr = INADDR_ANY;
	sock_add.sin_port = htons(std::atoi(this->_serverState->getPort().c_str()));

	std::cout << "Looking for a bind-able socket address..." << std::endl;

	if (bind(this->getServerFD(), (struct sockaddr *)&sock_add, sizeof(sock_add)) == -1)
	{
		close(this->getServerFD());
		perror("server: bind");
		return;
	}
}

/**
 * @brief Initiate multiplexing for this->_epollFD.
 */
void	Server::initiateMultiplexing()
{
	this->setEpollFD(epoll_create1(0));

	epoll_event	ev;
	ev.events = EPOLLIN;
	ev.data.fd = this->getServerFD();
	epoll_ctl(this->getEpollFD(), EPOLL_CTL_ADD, this->getServerFD(), &ev);

	epoll_event	events[64];
}

/**
 * @brief Sets the server up.
 */
void	Server::setUpServer()
{

	std::cout << "Setting server up..." << std::endl;

	//Create socket
	this->setServerFD(socket(AF_INET, SOCK_STREAM, 0));

	//Bind socket
	bindSocket();

	// Listen
	if (listen(this->getServerFD(), BACKLOG) == -1)
	{
		perror("listen");
		std::exit(1);
	}

	int	flags = fcntl(this->getServerFD(), F_GETFL, 0);
	fcntl(this->getServerFD(), F_SETFL, flags | O_NONBLOCK);

	initiateMultiplexing();

	std::cout << "Server is up!" << std::endl;
}

// void	Server::woINpr()
// {
// 	int	newFD;
// 	struct sockaddr_storage	theirAddr;
// 	socklen_t	sinSize;
// 	char	s[INET_ADDRSTRLEN];
// 	std::cout << "Waiting for connections..." << std::endl;
//
// 	char	buffer[1024];
// 	int numbytes;
// 	memset(buffer, 0, sizeof(buffer));
// 	sinSize = sizeof(theirAddr);
// 	newFD = accept(this->getEpollFD(), (struct sockaddr*)&theirAddr, &sinSize);
// 	if (newFD == -1)
// 	{
// 		perror("accept");
// 	}
//
// 	inet_ntop(theirAddr.ss_family, getInAddr((struct sockaddr*)&theirAddr), s, sizeof(s));
// 	std::cout << "server: got connection from " << s << std::endl;
//
// 	//CAP handling
// 	capHandling();
// 	std::string	cap_ls = "CAP * LS :multi-prefix sasl\r\n";
// 	send(newFD, cap_ls.c_str(), sizeof(cap_ls), 0);
// 	std::string	cap_ack = "CAP * ACK multi-prefix\r\n";
// 	send(newFD, cap_ack.c_str(), sizeof(cap_ack), 0);
//
// 	while (1)
// 	{
// 		bzero(buffer,sizeof(buffer));
// 		if ((numbytes = recv(newFD, buffer, sizeof(buffer) - 1, 0)) == -1)
// 			perror("recv");
// 		buffer[numbytes] = 0;
//
// 		if (buffer[0] != '\0')
// 		{
// 			std::cout << "Server received: " << buffer << std::endl;
// 			send(newFD, buffer, sizeof(buffer), 0);
// 		}
// 	}
// }

