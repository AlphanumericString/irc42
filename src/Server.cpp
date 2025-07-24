/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoulard <bgoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:14:33 by bgoulard          #+#    #+#             */
/*   Updated: 2025/07/24 23:08:12 by bgoulard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

#include <cstring>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/epoll.h>

#include <cerrno>
#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "ServerState.hpp"
#include "ShellServerHandler.hpp"

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

#define MAX_EVENT 10
void	Server::handleEvent() {
	struct	epoll_event	ev, events[MAX_EVENT];
	int					conn_sock, nfds;
	sockaddr_storage	addr;
	socklen_t			addrlen;
	char				buf[1024];

	ev.events = EPOLLIN;
	ev.data.fd = this->_serverFD;
	if (epoll_ctl(this->_epollFD, EPOLL_CTL_ADD, this->_serverFD, &ev) == -1) {
		return ;
	}

	for (;;) {
		nfds = epoll_wait(this->_epollFD, events, MAX_EVENT, -1);
		if (nfds == -1) {
			return ;
		}
		for (int n = 0 ; n < nfds ; ++n) {
			if (events[n].data.fd == this->_serverFD) {
				handleNewUser(events[n].data.fd);
				conn_sock = accept(this->_serverFD, (struct sockaddr*)&addr, &addrlen);
				if (conn_sock == -1) {
					return ;
				}
				ev.events = EPOLLIN | EPOLLET;
				ev.data.fd = conn_sock;
				if (epoll_ctl(this->_epollFD, EPOLL_CTL_ADD, conn_sock, &ev) == -1) {
					return ;
				}
			} else {
				memset(buf, 0, sizeof(buf));
				recv(events[n].data.fd, buf, sizeof(buf) -1, 0);
				std::cout << buf << std::endl;
			}
		}
	}
}

void	Server::handleNewUser(const int fd) {
	char	buf[1024];
	int		nbytes;
	Client*	newClient = new Client;

	/// @todo insert correctly into list.
	this->getServerState().getClients().insert();

	nbytes = recv(fd, buf, sizeof(buf) - 1, 0);
	if (nbytes == -1) {
		return ;
	}

	/// @todo handle CAP command
}

void	Server::init() {
	bool	stop = false;
	int		flgs;

	flgs = fcntl(STDIN_FILENO, F_GETFL);
	fcntl(STDIN_FILENO, F_SETFL, flgs | O_NONBLOCK);
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
	fcntl(this->_serverFD, F_SETFL, flgs);
	initiateMultiplexing();
}

void	Server::initiateMultiplexing() {
	this->_epollFD = epoll_create1(0);
	if (this->_epollFD == -1) {
		return ;
	}
}

void Server::run(void) {
	// if shell-server is dropped this display serv info when change occur
	// ServerState prev = this->_serverState;
	bool							   stop = false;
	int								   flgs;

	this->init();
	// -- move to init
	// flgs = fcntl(STDIN_FILENO, F_GETFL);
	// fcntl(STDIN_FILENO, F_SETFL, flgs | O_NONBLOCK);
	// sig::stop = &stop;
	// signal(SIGINT, sig_hdl);
	// signal(SIGTERM, sig_hdl);
	// signal(SIGQUIT, sig_hdl);
	// -- move to init

	setServerState(ServerState::RUNNING);
	std::cout << "$> ";
	while (ServerState::RUNNING == this->_serverState.getStatus()) {
		ShellServerHandler::cmdHandler(*this);

		/// @todo
		handleEvent();

		// if shell-server is dropped this display serv info when change occur
		// if (prev != this->_serverState)
		// 	std::cout << _serverState << std::endl;
		// prev = this->_serverState;
		if (stop) {
			setServerState(ServerState::STOPPING);
		}
	}
	std::cout << "Server is stopping..." << std::endl;
	fcntl(STDIN_FILENO, F_SETFL, flgs);
	return;
}

int Server::exit_state(void) {
	// todo :: not impl ->
	// _serverState -> get_status
	//	-> set status when parsing commands ?
	return (_serverState.getStatus() == ServerState::STOPPING ? 0 : 1);
}
