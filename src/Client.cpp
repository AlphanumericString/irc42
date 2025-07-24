/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoulard <bgoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 12:58:32 by bgoulard          #+#    #+#             */
/*   Updated: 2025/07/07 12:58:32 by bgoulard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

// dont we need the 'key' to id those when we create them ? aka the fd?
Client::Client() {
	message.clear();
}
Client::Client(Client const &original) {
	// when are we gonna use this ?!
	(void)original;
}

Client::~Client() {
	message.clear();
}

Client &Client::operator=(Client const &original) {
	(void)original;
	return (*this);
}
bool Client::isMessageFinished(void) {
	if (message.find('\n') != std::string::npos)
		return (true);
	return (false);
}

const std::string &Client::getNick(void) const {
	return this->nick;
}
const std::string &Client::getName(void) const {
	return this->name;
}
const std::string &Client::getHost(void) const {
	return this->host;
}

const t_conState &Client::getConState(void) const {
	return this->connectionState;
}
const t_authState &Client::getAuthState(void) const {
	return this->authState;
}

void Client::setNick(const std::string &nick) {
	this->nick = nick;
}
void Client::setName(const std::string &name) {
	this->name = name;
}
void Client::setHost(const std::string &host) {
	this->host = host;
}

void Client::setConState(const t_conState &cstate) {
	this->connectionState = cstate;
}
void Client::setAuthState(const t_authState &astate) {
	this->authState = astate;
}
