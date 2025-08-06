/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerState.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoulard <bgoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:14:31 by bgoulard          #+#    #+#             */
/*   Updated: 2025/08/06 16:39:46 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ServerState.hpp"

#include <fcntl.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/epoll.h>

#include <list>
#include <iostream>
#include <ostream>
#include <sstream>

#include "Channel.hpp"
#include "Client.hpp"
#include "Server.hpp"

ServerState::ServerState(int p, const std::string pwd, Server &m)
	: _password(pwd), _port(p) {
	this->_master = &m;
	this->_channels = std::list< Channel >();
	this->_clients = std::list< Client >();
	this->_name = SERVER_NAME_DFLT;
	this->_port = (p);
	this->_status = STARTING;
	this->_stop = false;
}

ServerState::~ServerState() {
}

ServerState	&ServerState::operator=(const ServerState &st)
{
	this->_stop = st._stop;
	this->_master = st._master;
	this->_status = st._status;
	this->_name = st._name;
	this->_password = st._password;
	this->_port = st._port;
	this->_clients = st._clients;
	this->_channels = st._channels;
	return (*this);
}

bool ServerState::operator==(const ServerState &st) const {
	return (this->_name == st._name && this->_port == st._port &&
			this->_password == st._password && this->_status == st._status);
}
bool ServerState::operator!=(const ServerState &st) const {
	return (!(*this == st));
}

/// @todo Implement function
void	ServerState::deleteClient(Client &client) {
	std::cout << "Client " << client.getHost() << " [" << client.getIPAddress() <<
	"]: has disconnected." << std::endl;
}

void ServerState::setStatus(ServerState::Status status) {
	this->_status = status;
}

ServerState::Status ServerState::getStatus(void) const {
	return (this->_status);
}

std::list< Client >&	ServerState::getClients() {
	return (_clients);
}

std::string const &ServerState::getName() const {
	return (this->_name);
}

std::string const &ServerState::getPassword() const {
	return (this->_password);
}

int const &ServerState::getPort() const {
	return (this->_port);
}

std::string ServerState::getMinimalInfo(void) const {
	std::stringstream ss;
	ss << "[" << this->getName() << "] at 127.0.0.1 : " << this->getPort();
	return (ss.str());
}
bool				*ServerState::getStopPtr(void) {
	return &(this->_stop);
}

Client*	ServerState::idClient(int fd) {
	std::list< Client >::iterator	nav = this->_clients.begin();

	while (nav != this->_clients.end()) {
		if (nav->getSockFD() == fd) {
			return (&(*nav));	// What the fuck is that ??? (I hate iterators so much).
		}
		++nav;
	}
	return (NULL);
}

int	ServerState::makeSocketNonBlocking(int fd) {
	int flags = fcntl(fd, F_GETFL, 0);
	if (flags == -1) {
		return (-1);
	}
	return (fcntl(fd, F_SETFL, flags | O_NONBLOCK));
}

std::ostream &operator<<(std::ostream &os, const ServerState sst) {
	os << sst.getMinimalInfo();
	return (os);
}

void	ServerState::newClient(int fd, char* ipAddress) {
	struct	epoll_event	currentEvent;
	Client				newClient(fd, ipAddress);


	if (makeSocketNonBlocking(fd) == -1) {
		close(fd);
		throw std::runtime_error("couldn't make socket non blocking");
	}
	currentEvent.events = EPOLLIN | EPOLLOUT | EPOLLHUP | EPOLLRDHUP;
	currentEvent.data.fd = fd;
	if (epoll_ctl(this->_master->getEpollFD(), EPOLL_CTL_ADD, fd, &currentEvent) == -1) {
		close(fd);
		throw std::runtime_error("epoll_ctl");
	}
	this->_clients.push_back(newClient);
}
