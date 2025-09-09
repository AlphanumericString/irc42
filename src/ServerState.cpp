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

#include <algorithm>
#include <fcntl.h>
#include <iostream>
#include <sstream>
#include <sys/epoll.h>
#include <unistd.h>

#include "Channel.hpp"
#include "Client.hpp"
#include "Server.hpp"

ServerState::ServerState(int p, const std::string pwd, Server &m)
	: password_(pwd), port_(p), hostname_("localhost") {
	this->master_ = &m;
	this->channels_ = std::list< Channel >();
	this->clients_ = std::list< Client >();
	this->name_ = SERVER_NAME_DFLT;
	this->port_ = (p);
	this->status_ = STARTING;
	this->stop_ = false;
	setDescription("A simple IRC server made in the context of a school "
				   "project at 42Paris.");
}

ServerState::~ServerState() {}

/// @todo Implement function
void ServerState::deleteClient(Client &client) {
	std::cout << "Client " << client.getHost() << " [" << client.getIPAddress()
			  << "]: has disconnected." << std::endl;
}

std::list< Client > &ServerState::getClients() {
	return (clients_);
}
const std::list< Client > &ServerState::getClients() const {
	return (clients_);
}

std::string ServerState::getMinimalInfo(void) const {
	std::stringstream ss;
	ss << "[" << this->getName() << "] at 127.0.0.1 : " << this->getPort();
	return (ss.str());
}
bool *ServerState::getStopPtr(void) {
	return &(this->stop_);
}

std::string const &ServerState::getName() const {
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

Client *ServerState::idClient(int fd) {
	std::list< Client >::iterator nav = this->clients_.begin();

	while (nav != this->clients_.end()) {
		if (nav->getSockFD() == fd) {
			return (&(
				*nav)); // What the fuck is that ??? (I hate iterators so much).
		}
		++nav;
	}
	return (NULL);
}

static int makeSocketNonBlocking(int fd) {
	int flags = fcntl(fd, F_GETFL, 0);
	if (flags == -1) {
		return (-1);
	}
	return (fcntl(fd, F_SETFL, flags | O_NONBLOCK));
}

void ServerState::newClient(int fd, char *ipAddress) {
	struct epoll_event currentEvent;
	Client			   newClient(fd, ipAddress, this->master_);

	if (makeSocketNonBlocking(fd) == -1) {
		close(fd);
		throw std::runtime_error("couldn't make socket non blocking");
	}
	currentEvent.events = EPOLLIN | EPOLLOUT | EPOLLHUP | EPOLLRDHUP;
	currentEvent.data.fd = fd;
	if (epoll_ctl(this->master_->getEpollFD(), EPOLL_CTL_ADD, fd,
				  &currentEvent) == -1) {
		close(fd);
		throw std::runtime_error("epoll_ctl");
	}
	this->clients_.push_back(newClient);
}

const std::string &ServerState::getHostname(void) const {
	return (hostname_);
}

ServerState &ServerState::operator=(const ServerState &other) {
	this->stop_ = other.stop_;
	this->master_ = other.master_;
	this->status_ = other.status_;
	this->name_ = other.name_;
	this->password_ = other.password_;
	this->port_ = other.port_;
	this->clients_ = other.clients_;
	this->channels_ = other.channels_;
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
	this->status_ = status;
}

std::ostream &operator<<(std::ostream &os, const ServerState sst) {
	os << sst.getMinimalInfo() << std::endl;
	os << sst.getClients().size() << " client(s) connected."
	   << std::endl;
	os << sst.getChannels().size() << " channel(s) created.";
	return (os);
}

std::list< Channel > &ServerState::getChannels() {
	return (channels_);
}
const std::list< Channel > &ServerState::getChannels() const {
	return (channels_);
}

const Channel *ServerState::getChannel(const std::string &name) const {
	for (std::list< Channel >::const_iterator it = channels_.begin();
		 it != channels_.end(); it++) {
		if (it->getName() == name)
			return (&(*it));
	}
	return (NULLPTR);
}
Channel *ServerState::getChannel(const std::string &name) {
	for (std::list< Channel >::iterator it = channels_.begin();
		 it != channels_.end(); it++) {
		if (it->getName() == name)
			return (&(*it));
	}
	return (NULLPTR);
}

Client *ServerState::getClient(const std::string &name) {
	for (std::list< Client >::iterator it = clients_.begin();
		 it != clients_.end(); it++) {
		if (it->getNick() == name)
			return (&(*it));
	}
	return (NULLPTR);
}
const Client *ServerState::getClient(const std::string &name) const {
	for (std::list< Client >::const_iterator it = clients_.begin();
		 it != clients_.end(); it++) {
		if (it->getNick() == name)
			return (&(*it));
	}
	return (NULLPTR);
}

Client *ServerState::getClient(int fd) {
	for (std::list< Client >::iterator it = clients_.begin();
		 it != clients_.end(); it++) {
		if (it->getSockFD() == fd)
			return (&(*it));
	}
	return (NULLPTR);
}
const Client *ServerState::getClient(int fd) const {
	for (std::list< Client >::const_iterator it = clients_.begin();
		 it != clients_.end(); it++) {
		if (it->getSockFD() == fd)
			return (&(*it));
	}
	return (NULLPTR);
}

void ServerState::setDescription(const std::string &desc) {
	this->desc = desc;
}
const std::string &ServerState::getDescription() const {
	return (this->desc);
}

void ServerState::addPrevClient(const Client &c) {
	this->prevClients_.push_back(c);
}
const std::vector< PrevClients > &ServerState::getPrevClients() const {
	return (this->prevClients_);
}
std::vector< PrevClients >
ServerState::getPrevClients(const std::string &name) const {
	std::vector< PrevClients >::const_iterator ci;
	std::vector< PrevClients >				   ret;

	for (ci = std::find(prevClients_.begin(), prevClients_.end(), name);
		 ci != prevClients_.end() && ci->_nick == name; ci++) {
		ret.push_back(*ci);
	}
	return (ret);
}
