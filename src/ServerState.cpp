/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerState.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoulard <bgoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:14:31 by bgoulard          #+#    #+#             */
/*   Updated: 2025/08/11 16:25:37 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ServerState.hpp"

#include <fcntl.h>
#include <unistd.h>
#include <sys/epoll.h>

#include <iostream>
#include <sstream>

#include "Server.hpp"

ServerState::ServerState(int p, const std::string pwd, Server &m)
	: password_(pwd), port_(p) {
	this->master_ = &m;
	this->channels_ = std::list< Channel >();
	this->clients_ = std::list< Client >();
	this->name_ = SERVER_NAME_DFLT;
	this->port_ = (p);
	this->status_ = STARTING;
	this->stop_ = false;
}

ServerState::~ServerState() {
}

/// @todo Implement function
void	ServerState::deleteClient(Client &client) {
	std::cout << "Client " << client.getHost() << " [" << client.getIPAddress() <<
	"]: has disconnected." << std::endl;
}

std::list< Client >&	ServerState::getClients() {
	return (clients_);
}

std::string ServerState::getMinimalInfo(void) const {
	std::stringstream ss;
	ss << "[" << this->getName() << "] at 127.0.0.1 : " << this->getPort();
	return (ss.str());
}
bool				*ServerState::getStopPtr(void) {
	return &(this->stop_);
}

std::string const&	ServerState::getName() const {
	return (this->name_);
}

std::string const &ServerState::getPassword() const {
	return (this->password_);
}

int const &ServerState::getPort() const {
	return (this->port_);
}

ServerState::Status ServerState::getStatus(void) const {
	return (this->status_);
}

Client*	ServerState::idClient(int fd) {
	std::list< Client >::iterator	nav = this->clients_.begin();

	while (nav != this->clients_.end()) {
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

void	ServerState::newClient(int fd, char* ipAddress) {
	struct	epoll_event	currentEvent;
	Client				newClient(fd, ipAddress, this->master_);


	if (makeSocketNonBlocking(fd) == -1) {
		close(fd);
		throw std::runtime_error("couldn't make socket non blocking");
	}
	currentEvent.events = EPOLLIN | EPOLLOUT | EPOLLHUP | EPOLLRDHUP;
	currentEvent.data.fd = fd;
	if (epoll_ctl(this->master_->getEpollFD(), EPOLL_CTL_ADD, fd, &currentEvent) == -1) {
		close(fd);
		throw std::runtime_error("epoll_ctl");
	}
	this->clients_.push_back(newClient);
}

ServerState	&ServerState::operator=(const ServerState &st)
{
	this->stop_ = st.stop_;
	this->master_ = st.master_;
	this->status_ = st.status_;
	this->name_ = st.name_;
	this->password_ = st.password_;
	this->port_ = st.port_;
	this->clients_ = st.clients_;
	this->channels_ = st.channels_;
	return (*this);
}

bool ServerState::operator==(const ServerState &st) const {
	return (this->name_ == st.name_ && this->port_ == st.port_ &&
			this->password_ == st.password_ && this->status_ == st.status_);
}
bool ServerState::operator!=(const ServerState &st) const {
	return (!(*this == st));
}

void ServerState::setStatus(ServerState::Status status) {
	this->status_= status;
}

std::ostream &operator<<(std::ostream &os, const ServerState sst) {
	os << sst.getMinimalInfo();
	return (os);
}

