/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerState.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoulard <bgoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:14:31 by bgoulard          #+#    #+#             */
/*   Updated: 2025/07/07 13:14:31 by bgoulard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ServerState.hpp"

#include <list>
#include <ostream>
#include <sstream>

#include "Channel.hpp"
#include "Client.hpp"
#include "Server.hpp"

ServerState::ServerState(int p, const std::string pwd, Server &m)
	: _password(pwd), _port(p), _host("localhost") {
	this->_master = &m;
	this->_channels = std::list< ShrdSmartPtr < Channel > >();
	this->_clients = std::list< ShrdSmartPtr < Client > >();
	this->_name = SERVER_NAME_DFLT;
	this->_port = (p);
	this->_status = STARTING;
	this->_logfile.open(SERVER_NAME_DFLT".log");
	if (this->_logfile.is_open() == false)
		this->_status = ServerState::ERROR;
}

ServerState &ServerState::operator=(const ServerState &st) {
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

void ServerState::setStatus(ServerState::Status status) {
	this->_status = status;
}

ServerState::Status ServerState::getStatus(void) const {
	return (this->_status);
}

std::list< ShrdSmartPtr < Client > > &ServerState::getClients(void) {
	return (this->_clients);
}

std::list< ShrdSmartPtr < Channel > > &ServerState::getChanels(void) {
	return (this->_channels);
}

ServerState::~ServerState() {}

std::string const &ServerState::getName() const {
	return (this->_name);
}

std::string const &ServerState::getPassword() const {
	return (this->_password);
}

int const &ServerState::getPort() const {
	return (this->_port);
}

const std::string &ServerState::getHost() const {
	return (this->_host);
}

std::string ServerState::getMinimalInfo(void) const {
	std::stringstream ss;
	ss << "[" << this->getName() << "] at 127.0.0.1 : " << this->getPort();
	return (ss.str());
}

std::ostream &operator<<(std::ostream &os, const ServerState &sst) {
	os << sst.getMinimalInfo();
	return (os);
}
