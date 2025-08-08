/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoulard <bgoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:14:33 by bgoulard          #+#    #+#             */
/*   Updated: 2025/08/08 18:45:02 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

#include <fcntl.h>
#include <arpa/inet.h>
#include <ostream>
#include <stdexcept>
#include <string>
#include <sys/epoll.h>
#include <errno.h>

#include <csignal>
#include <cstdlib>
#include <iostream>

#include "ShellServerHandler.hpp"
#include "smart_ptr.hpp"

#define BUFFER_LEN 8192

static char BUFFER[BUFFER_LEN];

namespace sig {
bool *stop = NULLPTR;
int	  g_sig = 0;
} // namespace sig

static void sig_hdl(int sig) {
	if (sig == SIGINT || sig == SIGTERM || sig == SIGQUIT) {
		std::cerr << "Handled signal: " << sig << std::endl;
		std::cout << std::endl;
		if (sig::stop != NULLPTR)
			*sig::stop = true;
		sig::g_sig = sig;
	} else {
		std::cerr << "Unhandled signal: " << sig << std::endl;
	}
}

Server::Server(int port, const std::string password)
	: serverState_(port, password, *this) {
	this->serverFD_ = -1;
	this->epollFD_ = -1;	   // not set
	this->clients_ = NULLPTR;  // not set
	this->channels_ = NULLPTR; // not set
	// this->_channels = _serverState.getChannelsPtr();
	// this->_clients = _serverState.getClientsPtr();
}

Server::~Server() {
}

void	Server::addStdInToMultiplexing() {
	struct	epoll_event	currentEvent;

	if (ServerState::makeSocketNonBlocking(STDIN_FILENO) == -1) {
		close(STDIN_FILENO);
		throw std::runtime_error("couldn't make socket non blocking");
	}
	currentEvent.events = EPOLLIN;
	currentEvent.data.fd = STDIN_FILENO;
	if (epoll_ctl(this->epollFD_, EPOLL_CTL_ADD, STDIN_FILENO, &currentEvent) == -1) {
		close(STDIN_FILENO);
		throw std::runtime_error("epoll_ctl");
	}
}

void	Server::bindSocket() {
	struct sockaddr_in	sock_add;

	sock_add.sin_family = AF_INET;
	sock_add.sin_addr.s_addr = INADDR_ANY;
	sock_add.sin_port = htons(this->getServerState().getPort());

	if (bind(this->serverFD_, (struct sockaddr*)&sock_add, sizeof(sock_add)) == -1) {
		close(this->serverFD_);
		std::cerr << "Failed to bind" << std::endl;
		return ;
	}
}

#define MAX_BACKLOG 20

vecEvent	Server::collectReadyEvents() {
	struct epoll_event events[MAX_BACKLOG];

	int nfds = epoll_wait(this->epollFD_, events, MAX_BACKLOG, 1000);
	if (nfds == -1 && errno != EINTR) {
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

int Server::exit_state(void) {
	// todo :: not impl ->
	// _serverState -> get_status
	//	-> set status when parsing commands ?
	return (serverState_.getStatus() == ServerState::STOPPING ? 0 : 1);
}

int	Server::getEpollFD() const {
	return (this->epollFD_);
}

int	Server::getServerFD() const {
	return (this->serverFD_);
}

const ServerState &Server::getServerState(void) const {
	return (this->serverState_);
}

void	Server::handleNewConnection() {
	sockaddr_in	peerSockAddr;
	socklen_t	addrlen = sizeof(peerSockAddr);
	
	int new_clientFD = accept(this->serverFD_, (struct sockaddr*)&peerSockAddr, &addrlen);
	if (new_clientFD == -1) {
		throw std::runtime_error("accept() error");
	}
	char*	ip_str = inet_ntoa(peerSockAddr.sin_addr);
	std::cout << "NEW CONNECTION from: " << ip_str << std::endl;
	this->serverState_.newClient(new_clientFD, ip_str);
}

void	Server::init(int *flgs) {
	*flgs = fcntl(STDIN_FILENO, F_GETFL);
	fcntl(STDIN_FILENO, F_SETFL, *flgs | O_NONBLOCK);
	sig::stop = this->serverState_.getStopPtr();
	signal(SIGINT, sig_hdl);
	signal(SIGTERM, sig_hdl);
	signal(SIGQUIT, sig_hdl);

	this->serverFD_ = socket(AF_INET, SOCK_STREAM, 0);
	bindSocket();
	if (listen(this->serverFD_, 10) == -1) {
		std::cerr << "Couldn't listen" << std::endl;
		std::exit(1);
	}
	fcntl(this->serverFD_, F_SETFL, *flgs);
	initiateMultiplexing();
	setServerState(ServerState::RUNNING);
}

void	Server::handleClientDisconnect(Client& client) {
	int	clientFD = client.getSockFD();
	epoll_ctl(this->epollFD_, EPOLL_CTL_DEL, clientFD, NULL);
	close(clientFD);
	this->serverState_.deleteClient(client);
}

void	Server::handleClientRead(Client& client) {
	int	clientFD = client.getSockFD();
	int	res = recv(clientFD, BUFFER, BUFFER_LEN, 0);
	if (res < 0) {
		epoll_ctl(this->epollFD_, EPOLL_CTL_DEL, clientFD, NULL);
		close(clientFD);
		this->serverState_.deleteClient(client);
	}
	client.appendInputBuffer(BUFFER, res);
}

void	Server::handleClientWrite(Client& client) {
	int	clientFD = client.getSockFD();
	int	len = client.setOutputBuffer(BUFFER, BUFFER_LEN);
	int	res = send(clientFD, BUFFER, len, 0);
	if (res < 0) {
		epoll_ctl(this->epollFD_, EPOLL_CTL_DEL, clientFD, NULL);
		close(clientFD);
		this->serverState_.deleteClient(client);
	}
	client.advanceOutputBuffer(res);
}

void	Server::initiateMultiplexing() {
	this->epollFD_ = epoll_create(1);	// Passing 1 as size because parameter is ignored
	if (this->epollFD_ == -1) {
		return ;
	}
	struct	epoll_event	currentEvent;

	currentEvent.events = EPOLLIN | EPOLLOUT | EPOLLHUP | EPOLLRDHUP;
	currentEvent.data.fd = this->serverFD_;
	epoll_ctl(this->epollFD_, EPOLL_CTL_ADD, this->serverFD_, &currentEvent);
	addStdInToMultiplexing();
	std::cout << "$> " << std::flush;
}

void	Server::handleStdinInput() {
	int res = read(STDIN_FILENO, BUFFER, BUFFER_LEN);
	if (res < 0) {
		throw std::runtime_error("Read stdin: error");
	}
	this->stdinBuffer.append(&BUFFER[0], &BUFFER[res]);

	for (std::string::size_type line = this->stdinBuffer.find('\n') ;
	line != std::string::npos ;
	this->stdinBuffer.erase(this->stdinBuffer.begin(), this->stdinBuffer.begin() + line + 1),
	line = this->stdinBuffer.find('\n'))
	{
		std::string extracted(this->stdinBuffer.begin(), this->stdinBuffer.begin() + line);
		ShellServerHandler::cmdHandler(*this, extracted);
	}
}

void Server::mainLoop(void) {
	int	flags;

	this->init(&flags);

	while (ServerState::RUNNING == this->serverState_.getStatus()) {

		vecEvent readyEvents = this->collectReadyEvents();

		for (vecEvent::iterator it = readyEvents.begin(); it != readyEvents.end(); it++)
		{
			int				fd = it->first;
			eventType	ev = it->second;

			if (fd == this->serverFD_ && ev == EVENT_READ) {
				handleNewConnection();
			} else if (fd == STDIN_FILENO && ev == EVENT_READ) {
				/// @todo Handle STDI stop at null byteN -> Not sure still relevant
				handleStdinInput();
			} else {
				Client *client = this->serverState_.idClient(fd);
				if (client == NULL) {
					close(fd);
					continue;
				}
				if (ev == EVENT_READ)
					handleClientRead(*client);
				else if (ev == EVENT_WRITE)
					handleClientWrite(*client);
				else if (ev == EVENT_HANGUP)
					handleClientDisconnect(*client);
			}
		}
		for (std::list<Client>::iterator it = this->serverState_.getClients().begin() ;
		it != this->serverState_.getClients().end() ;
		it++)
		{
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
	// Is this still relevant ? (apetitco)
	fcntl(STDIN_FILENO, F_SETFL, flags);
	return;
}

Server &Server::operator=(Server const &original) {
	(void)original;
	return (*this);
}

void Server::setServerState(ServerState::Status state) {
	this->serverState_.setStatus(state);
}

