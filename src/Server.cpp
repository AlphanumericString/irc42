/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoulard <bgoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:14:33 by bgoulard          #+#    #+#             */
/*   Updated: 2025/07/07 13:14:33 by bgoulard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

#include <cerrno>
#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <fcntl.h>
#include <iostream>
#include <unistd.h>

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

void Server::run(void) {
	// if shell-server is dropped this display serv info when change occur
	// ServerState prev = this->_serverState;
	bool							   stop = false;
	int								   flgs;

	// -- move to init
	flgs = fcntl(STDIN_FILENO, F_GETFL);
	fcntl(STDIN_FILENO, F_SETFL, flgs | O_NONBLOCK);
	sig::stop = &stop;
	signal(SIGINT, sig_hdl);
	signal(SIGTERM, sig_hdl);
	signal(SIGQUIT, sig_hdl);
	// -- move to init

	setServerState(ServerState::RUNNING);
	std::cout << "$> ";
	while (ServerState::RUNNING == this->_serverState.getStatus()) {
		ShellServerHandler::cmdHandler(*this);

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
