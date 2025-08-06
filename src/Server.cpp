/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoulard <bgoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:14:33 by bgoulard          #+#    #+#             */
/*   Updated: 2025/08/06 17:19:01 by apetitco         ###   ########.fr       */
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

void	Server::addStdInToMultiplexing() {
	struct	epoll_event	currentEvent;

	if (ServerState::makeSocketNonBlocking(STDIN_FILENO) == -1) {
		close(STDIN_FILENO);
		throw std::runtime_error("couldn't make socket non blocking");
	}
	currentEvent.events = EPOLLIN | EPOLLOUT | EPOLLHUP | EPOLLRDHUP;
	currentEvent.data.fd = STDIN_FILENO;
	if (epoll_ctl(this->_epollFD, EPOLL_CTL_ADD, STDIN_FILENO, &currentEvent) == -1) {
		close(STDIN_FILENO);
		throw std::runtime_error("epoll_ctl");
	}
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

int	Server::getEpollFD() const {
	return (this->_epollFD);
}

int	Server::getServerFD() const {
	return (this->_serverFD);
}

void	Server::init(int *flgs) {
	*flgs = fcntl(STDIN_FILENO, F_GETFL);
	fcntl(STDIN_FILENO, F_SETFL, *flgs | O_NONBLOCK);
	sig::stop = this->_serverState.getStopPtr();
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
	struct	epoll_event	currentEvent;

	currentEvent.events = EPOLLIN | EPOLLOUT | EPOLLHUP | EPOLLRDHUP;
	currentEvent.data.fd = this->_serverFD;
	epoll_ctl(this->_epollFD, EPOLL_CTL_ADD, this->_serverFD, &currentEvent);
}

#define BUFFER_LEN 8192

void Server::mainLoop(void) {
	int	flags;

	this->init(&flags);

	setServerState(ServerState::RUNNING);
	addStdInToMultiplexing();
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
				if (new_clientFD == -1) {
					throw std::runtime_error("accept() error");
				}
				char*	ip_str = inet_ntoa(peerSockAddr.sin_addr);
				std::cout << "NEW CONNECTION from: " << ip_str << std::endl;
				this->_serverState.newClient(new_clientFD, ip_str);
			} else if (fd == STDIN_FILENO) {
				/// @todo Handle STDIN
				ShellServerHandler::cmdHandler(*this);
			} else {
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
					int len = client->setOutputBuffer(BUFFER, BUFFER_LEN);
					int res;
					res = send(fd, BUFFER, len, 0);
					if (res < 0)
					{
						epoll_ctl(this->_epollFD, EPOLL_CTL_DEL, fd, NULL);
						close(fd);
						this->_serverState.deleteClient(*client);
					}
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
		if (*sig::stop) {
			setServerState(ServerState::STOPPING);
		}
	}
	std::cout << "Server is stopping..." << std::endl;
	fcntl(STDIN_FILENO, F_SETFL, flags);
	return;
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

