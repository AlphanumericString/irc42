/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoulard <bgoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 12:58:32 by bgoulard          #+#    #+#             */
/*   Updated: 2025/08/13 15:07:16 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "AuthState.hpp"

#include <cstring>
#include <iostream>

Client::Client() : sockFD_(-1), authState_(AUTH_NO) {
}

Client::Client(int fd, char* ipAddress, Server* server) :
		sockFD_(fd),
		authState_(AUTH_NO),
		connectedServer_(server),
		ipAddress_(ipAddress) {
	std::cout << "Nouveau client:" << std::endl <<
		"fd: " << this->sockFD_ << std::endl <<
		"ip address: " << this->ipAddress_ << std::endl;
}

Client::Client(Client const &original) {
	*this = original;
}

Client::~Client() {
}


void	Client::advanceOutputBuffer(unsigned int length) {
	this->outputBuffer_.erase(length);
}

void	Client::appendInputBuffer(char *str, unsigned int length) {
	if (str) {
		this->inputBuffer_.append(str, length);
	}
}

const std::string&	Client::getHost() const {
	return (this->host_);
}

const std::string&	Client::getIPAddress() const {
	return (this->ipAddress_);
}

std::string&	Client::getOutputBuffer() {
	return (outputBuffer_);
}

int	Client::getSockFD() const {
	return (sockFD_);
}

/// @todo Implement this function.
Client &Client::operator=(Client const &original) {
	if (this != &original) {
		this->sockFD_ = original.getSockFD();
		this->ipAddress_ = original.getIPAddress();
	}
	return (*this);
}

/// @todo Implement this function.
void	Client::processInput() {
}

#define MAX_NICKNAME_LENGTH 9

void	Client::setNickname(std::string const& newNickname) {
	if (newNickname.length() > MAX_NICKNAME_LENGTH) {
		throw NicknameTooLongException();
	}
	this->nick_ = newNickname;
}

int	Client::setOutputBuffer(char* buffer, unsigned int maxLength) {
	memset(buffer, 0, maxLength);
	strncpy(buffer, this->outputBuffer_.c_str(), maxLength);
	return (strlen(buffer));
}

void	Client::setSockFD(int fd) {
	this->sockFD_ = fd;
}

const char*	Client::NicknameTooLongException::what() const throw() {
	return ("Error: New nickname is too long.");
}
