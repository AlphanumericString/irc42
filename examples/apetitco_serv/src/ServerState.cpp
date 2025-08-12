#include "ServerState.hpp"

ServerState::ServerState(std::string port, const std::string password, std::string name, Server* master)
	: _status(STARTING),
	  _name(name),
	  _password(password),
	  _port(port),
	  _master(master) {
}

ServerState::~ServerState() {
}

std::list< Client >	ServerState::getClients() {
	return (this->_clients);
}

std::string const	&ServerState::getPort() const
{
	return (this->_port);
}

ServerState::Status ServerState::getStatus(void) const {
	return (this->_status);
}

void ServerState::setStatus(Status status) {
	this->_status = status;
}
