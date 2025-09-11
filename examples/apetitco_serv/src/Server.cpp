/// @file
/// @ingroup ServerGroup
/// @brief Implementation of the Server class' methods.

/// @defgroup ServerGroup Module Server.
/// @brief Everything touching to the IRC server.

#include <fcntl.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>

#include <cstdlib>
#include <cstring>
#include <iostream>

#include "Server.hpp"
#include "Client.hpp"
#include "ServerState.hpp"

Server::Server() : _epollFD(-1) {
	_serverState = new ServerState();

	this.setClients()
}

Server::~Server() {
	if (_serverState)
		delete _serverState;
}

Server &Server::operator=(const Server &other)
{
	if (this != &other)
	{

	}
	return (*this);
}

std::list< Client >*	Server::getClients() {
	return (this->_clients);
}

int const&	Server::getEpollFD() const
{
	return (this->_epollFD);
}

int	const&	Server::getServerFD() const
{
	return (this->_serverFD);
}

ServerState*	Server::getServerState() const {
	if (this->_serverState == NULL)
		std::cerr << "Warning, this->_serverState == NULL" << std::endl;
	return (this->_serverState);
}

#define MAX_EVENT 10
void	Server::handleEvent() {
	struct epoll_event	ev, events[MAX_EVENT];
	int	epollfd = this->getEpollFD();
	int	listen_sock	= this->getServerFD();
	int					conn_sock, nfds;
	sockaddr_storage	addr;
	socklen_t			addrlen;
	char				buf[1024];

	ev.events = EPOLLIN;
	ev.data.fd = listen_sock;
	if (epoll_ctl(epollfd, EPOLL_CTL_ADD, listen_sock, &ev) == -1) {
		return ;
	}

	for (;;) {
		nfds = epoll_wait(epollfd, events, MAX_EVENT, -1);
		if (nfds == -1) {
			return ;
		}

		for (int n = 0 ; n < nfds ; ++n) {
			if (events[n].data.fd == listen_sock) {
				handleNewUser(events[n].data.fd);
				conn_sock = accept(listen_sock, (struct sockaddr*) &addr, &addrlen);
				if (conn_sock == -1) {
					return ;
				}
				ev.events = EPOLLIN | EPOLLET;
				ev.data.fd = conn_sock;
				if (epoll_ctl(epollfd, EPOLL_CTL_ADD, conn_sock, &ev) == -1) {
					return ;
				}
			} else {
				memset(buf, 0, sizeof(buf));
				recv(events[n].data.fd, buf, sizeof(buf) - 1, 0);
				std::cout << buf << std::endl;
			}
		}
	}
}


void	Server::handleNewUser(const int fd) {
	char	buffer[BUFSIZ];
	int		nbytes;
	Client	*newClient = new Client;

	this->getClients()->insert();

	std::cout << "NEW USER" << std::endl;
	nbytes = recv(fd, buffer, sizeof(buffer) - 1, 0);
	if (nbytes == -1)
		return ;

	std::string	cap_ls = "CAP * LS: multi-prefix sasl";
	send(fd, cap_ls.c_str(), cap_ls.size(), 0);

	// cap_ls = "CAP * LS :multi-prefix sasl\r\n";
	// send(fd, cap_ls.c_str(), sizeof(cap_ls), 0);
	// std::string	cap_ack = "CAP * ACK multi-prefix\r\n";
	// send(fd, cap_ack.c_str(), sizeof(cap_ack), 0);

	// std::string	cap_ls = "CAP * LS :multi-prefix sasl\r\n";
	// send(newFD, cap_ls.c_str(), sizeof(cap_ls), 0);
	// 	std::string	cap_ack = "CAP * ACK multi-prefix\r\n";
	// 	send(newFD, cap_ack.c_str(), sizeof(cap_ack), 0);
}

void	Server::setEpollFD(int fd) {
	this->_epollFD = fd;
}

void	Server::setServerFD(int fd) {
	this->_serverFD = fd;
}

void	Server::bindSocket() {
	struct sockaddr_in sock_add;

	sock_add.sin_family = AF_INET;
	sock_add.sin_addr.s_addr = INADDR_ANY;
	const char	*tmp = this->_serverState->getPort().c_str();
	sock_add.sin_port = htons(std::atoi(tmp));

	std::cout << "Looking for a bind-able socket address..." << std::endl;

	if (bind(this->getServerFD(), (struct sockaddr *)&sock_add, sizeof(sock_add)) == -1)
	{
		close(this->getServerFD());
		perror("server: bind");
		return;
	}
	std::cout << "Binded address to socket" << std::endl;
}

void	Server::initiateMultiplexing()
{
	this->setEpollFD(epoll_create1(0));
	if (this->getEpollFD() == -1) {
		return ;
	}
}

void			Server::setClients(const std::list< Client >* list) {
	this->_clients = (std::list< Client>*)list;
}

void	Server::setUpServer() {
	std::cout << "Setting server up..." << std::endl;
	this->setServerFD(socket(AF_INET, SOCK_STREAM, 0));
	bindSocket();
	if (listen(this->getServerFD(), BACKLOG) == -1) {
		perror("listen");
		std::exit(1);
	}
	int	flags = fcntl(this->getServerFD(), F_GETFL, 0);
	fcntl(this->getServerFD(), F_SETFL, flags | O_NONBLOCK);
	this->getServerState()->setStatus(ServerState::RUNNING);
	std::cout << "Server state: RUNNING" << std::endl;
	initiateMultiplexing();
}

