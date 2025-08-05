/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoulard <bgoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:14:33 by bgoulard          #+#    #+#             */
/*   Updated: 2025/08/05 17:41:44 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

#include <exception>
#include <fcntl.h>
#include <list>
#include <stdexcept>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <cerrno>
#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

#include "ServerState.hpp"
#include "ShellServerHandler.hpp"
#include "smart_ptr.hpp"

namespace sig {
bool *stop = NULLPTR;
int	  g_sig = 0;
} // namespace sig

static void sig_hdl(int sig) {
	if (sig == SIGINT || sig == SIGTERM || sig == SIGQUIT) {
		std::cout << std::endl;
		if (sig::stop != NULLPTR)
			*sig::stop = true;
		sig::g_sig = sig;
	} else {
		std::cerr << "Unhandled signal: " << sig << std::endl;
	}
}

Server::Server(int port, const std::string password)
	: _serverState(port, password, *this) {
	this->_serverFD = -1;
	this->_epollFD = -1;	   // not set
	this->_clients = NULLPTR;  // not set
	this->_channels = NULLPTR; // not set
	// this->_channels = _serverState.getChannelsPtr();
	// this->_clients = _serverState.getClientsPtr();
}

Server::~Server() {}

Server &Server::operator=(Server const &original) {
	(void)original;
	return (*this);
}

void Server::setServerState(ServerState::Status state) {
	this->_serverState.setStatus(state);
}

const ServerState &Server::getServerState(void) const {
	return (this->_serverState);
}

void	Server::bindSocket() {
	struct sockaddr_in	sock_add;

	sock_add.sin_family = AF_INET;
	sock_add.sin_addr.s_addr = INADDR_ANY;
	sock_add.sin_port = htons(this->getServerState().getPort());

	if (bind(this->_serverFD, (struct sockaddr*)&sock_add, sizeof(sock_add)) == -1) {
		close(this->_serverFD);
		std::cerr << "Failed to bind" << std::endl;
		return ;
	}
}

int Server::exit_state(void) {
	// todo :: not impl ->
	// _serverState -> get_status
	//	-> set status when parsing commands ?
	return (_serverState.getStatus() == ServerState::STOPPING ? 0 : 1);
}

void Server::handleEvent(Client& client) {
	char buffer[1024];

	ssize_t count = recv(client.getSockFD(), buffer, sizeof(buffer) - 1, 0);
	if (count == -1) {
		throw std::runtime_error("recv");
	} else if (count == 0) {
		std::cout << "Client disconnected: fd " << client.getSockFD() << std::endl;
		close(client.getSockFD());
		/// @todo pop Client of the list;
	} else {
		buffer[count] = '\0';
		handleMessage(buffer, client.getSockFD());
	}
}

void	Server::handleMessage(char* buffer, int fd) {
	Client	*sender = this->_serverState.idClient(fd);
	std::cout << "Received from Client (" << sender << "): " << buffer << std::endl;
	/// @todo Handle messages
}

void	Server::handleNewUser(const int fd) {
	char	buf[1024];
	int		nbytes;
	Client	newClient;

	/// @todo Fill Client object info.
	newClient.setSockFD(fd);
	this->_serverState.getClients().push_back(newClient);

	memset(buf, 0, sizeof(buf));
	nbytes = recv(fd, buf, sizeof(buf) - 1, 0);
	if (nbytes == -1) {
		return ;
	}

	/// @todo handle CAP command
}

void	Server::init(int *flgs) {
	bool	stop = false;

	*flgs = fcntl(STDIN_FILENO, F_GETFL);
	fcntl(STDIN_FILENO, F_SETFL, *flgs | O_NONBLOCK);
	sig::stop = &stop;
	signal(SIGINT, sig_hdl);
	signal(SIGTERM, sig_hdl);
	signal(SIGQUIT, sig_hdl);

	this->_serverFD = socket(AF_INET, SOCK_STREAM, 0);
	bindSocket();
	if (listen(this->_serverFD, 10) == -1) {
		std::cerr << "Couldn't listen" << std::endl;
		std::exit(1);
	}
	fcntl(this->_serverFD, F_SETFL, *flgs);
	initiateMultiplexing();
}

void	Server::initiateMultiplexing() {
	this->_epollFD = epoll_create(1);	// Passing 1 as size because parameter is ignored
	if (this->_epollFD == -1) {
		return ;
	}
}

int	Server::makeSocketNonBlocking(int fd) {
	int flags = fcntl(fd, F_GETFL, 0);
	if (flags == -1) {
		return (-1);
	}
	return (fcntl(fd, F_SETFL, flags | O_NONBLOCK));
}


#define BUFFER_LEN 8192

void Server::mainLoop(void) {
	int	flags;

	this->init(&flags);

	setServerState(ServerState::RUNNING);
	std::cout << "$> ";
	while (ServerState::RUNNING == this->_serverState.getStatus()) {
		ShellServerHandler::cmdHandler(*this);

		vecEvent events = this->polling();

		for (vecEvent::iterator it = events.begin(); it != events.end(); it++)
		{
			int				fd = it->first;
			t_event_type	ev = it->second;

			if (fd == this->_serverFD && ev == EVENT_READ)
			{
				sockaddr_in	peerSockAddr;
				socklen_t	addrlen = sizeof(peerSockAddr);

				int new_clientFD = accept(this->_serverFD, (struct sockaddr*)&peerSockAddr, &addrlen);
				this->_serverState.newClient(new_clientFD);
			}
			else {
				Client *client = this->_serverState.idClient(fd);
				if (client == NULL) {
					close(fd);
					continue;
				}
				static char BUFFER[BUFFER_LEN];

				if (ev == EVENT_READ)
				{
					int res;
					res = recv(fd, BUFFER, BUFFER_LEN, 0);
					if (res < 0)
					{
						epoll_ctl(this->_epollFD, EPOLL_CTL_DEL, fd, NULL);
						close(fd);
						this->_serverState.deleteClient(*client);
						continue;
					}
					client->appendInputBuffer(BUFFER, res);
				}
				if (ev == EVENT_WRITE)
				{
					// ask to fill the BUFFER with at most BUFFER_LEN; return the number of bytes written
					int len = client->setOutputBuffer(BUFFER, BUFFER_LEN);
					int res;
					res = send(fd, BUFFER, len, 0);
					if (res < 0)
					{
						epoll_ctl(this->_epollFD, EPOLL_CTL_DEL, fd, NULL);
						close(fd);
						this->_serverState.deleteClient(*client);
					}
					// say that `res` has been sent, please delete them from the output buffer
					client->advanceOutputBuffer(res);
				}
				if (ev == EVENT_HANGUP)
				{
					epoll_ctl(this->_epollFD, EPOLL_CTL_DEL, fd, NULL);
					close(fd);
					this->_serverState.deleteClient(*client);
				}
			}
		}
		for (std::list<Client>::iterator it = this->_serverState.getClients().begin() ;
			it != this->_serverState.getClients().end();
			it++) {
			it->processInput();
		}

		// if shell-server is dropped this display serv info when change occur
		// if (prev != this->_serverState)
		// 	std::cout << _serverState << std::endl;
		// prev = this->_serverState;
		if (sig::stop) {
			setServerState(ServerState::STOPPING);
		}
	}
	std::cout << "Server is stopping..." << std::endl;
	fcntl(STDIN_FILENO, F_SETFL, flags);
	return;
}

void	Server::newUser() {
	struct	epoll_event	currentEvent;
	struct sockaddr_in	peerSockAddr;
	socklen_t			addrlen = sizeof(peerSockAddr);

	int conn_sock = accept(this->_serverFD, (struct sockaddr*)&peerSockAddr, &addrlen);
	if (conn_sock == -1) {
		throw std::runtime_error("accept() error");
	}
	char*	ip_str = inet_ntoa(peerSockAddr.sin_addr);
	std::cout << "NEW CONNECTION from: " << ip_str << std::endl;
	if (makeSocketNonBlocking(conn_sock) == -1) {
		close(conn_sock);
		throw std::runtime_error("couldn't make socket non blocking");
	}
	currentEvent.events = EPOLLIN | EPOLLOUT | EPOLLHUP | EPOLLRDHUP;
	currentEvent.data.fd = conn_sock;
	if (epoll_ctl(this->_epollFD, EPOLL_CTL_ADD, conn_sock, &currentEvent) == -1) {
		perror("epoll_ctl: conn_sock");
		close(conn_sock);
	}
	handleNewUser(conn_sock);
}

#define MAX_BACKLOG 20

vecEvent	Server::polling() {
	struct epoll_event events[MAX_BACKLOG];

	int nfds = epoll_wait(this->_epollFD, events, MAX_BACKLOG, 1000);
	if (nfds == -1) {
		/// @todo throw specific error ?
		throw std::runtime_error("epoll_wait");
	}
	vecEvent ret;
	for (int i = 0 ; i < nfds ; i++) {
		int fd = events[i].data.fd;
		if (events[i].events & EPOLLIN)
			ret.push_back(std::make_pair(fd, EVENT_READ));
		if (events[i].events & EPOLLOUT)
			ret.push_back(std::make_pair(fd, EVENT_WRITE));
		if (events[i].events & (EPOLLHUP | EPOLLRDHUP))
			ret.push_back(std::make_pair(fd, EVENT_HANGUP));
	}
	return (ret);
}

