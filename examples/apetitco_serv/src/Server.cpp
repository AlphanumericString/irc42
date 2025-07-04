#include <strings.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <poll.h>
#include <netdb.h>
#include <sys/poll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#include "Server.hpp"

///CONSTRUCTORS/////////////////////////////////////////////////////////////////
Server::Server() : _serverPort(std::atoi(SERV_PORT)), _serverSocketFD(-1)
{

}

///DESTRUCTORS//////////////////////////////////////////////////////////////////
Server::~Server()
{}

///OPERATOR OVERLOADS///////////////////////////////////////////////////////////
///GETTERS//////////////////////////////////////////////////////////////////////
int const	&Server::getServerSocketFD() const
{
	return (this->_serverSocketFD);
}
///SETTERS//////////////////////////////////////////////////////////////////////
///MEMBER FUNCTIONS/////////////////////////////////////////////////////////////
void	Server::hintsSetUp()
{
}

void	*getInAddr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET)
	{
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}

	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

void	Server::setUpServer()
{
	int	sockFD, newFD;
	struct addrinfo	hints, *servInfo, *p;
	struct sockaddr_storage	theirAddr;
	socklen_t	sinSize;
	int yes = 1;
	char	s[INET_ADDRSTRLEN];
	int	rv;

	std::cout << "Setting server up..." << std::endl;

	std::cout << "Setting up hints" << std::endl;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	if ((rv = getaddrinfo(NULL, SERV_PORT, &hints, &servInfo)) != 0)
	{
		std::cerr << "getaddrinfo: " << gai_strerror(rv) << std::endl;
		//throw
	}

	for (p = servInfo ; p != NULL ; p = p->ai_next)
	{
		if ((sockFD = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == 1)
		{
			perror("server: socket");
			continue;
		}
		if (setsockopt(sockFD, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
		{
			perror("setsockopt");
			std::exit(1);
		}
		if (bind(sockFD, p->ai_addr, p->ai_addrlen) == -1)
		{
			close(sockFD);
			perror("server: bind");
			continue;
		}
		break ;
	}

	freeaddrinfo(servInfo);

	if (p == NULL)
	{
		std::cerr << "server: failed to bind" << std::endl;
		std::exit(1);
	}

	if (listen(sockFD, BACKLOG) == -1)
	{
		perror("listen");
		std::exit(1);
	}

	std::cout << "Server is up!" << std::endl;
	std::cout << "Waiting for connections..." << std::endl;

	char	buffer[1024];
	int numbytes;
	memset(buffer, 0, sizeof(buffer));
	sinSize = sizeof(theirAddr);
	newFD = accept(sockFD, (struct sockaddr*)&theirAddr, &sinSize);
	if (newFD == -1)
	{
		perror("accept");
	}

	inet_ntop(theirAddr.ss_family, getInAddr((struct sockaddr*)&theirAddr), s, sizeof(s));
	std::cout << "server: got connection from " << s << std::endl;

	while (1)
	{
		bzero(buffer,sizeof(buffer));
		if ((numbytes = recv(newFD, buffer, sizeof(buffer) - 1, 0)) == -1)
			perror("recv");
		buffer[numbytes] = 0;

		if (buffer[0] != '\0')
			std::cout << "Server received: " << buffer << std::endl;
	}
}

///EXCEPTIONS///////////////////////////////////////////////////////////////////
