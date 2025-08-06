/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoulard <bgoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 12:58:32 by bgoulard          #+#    #+#             */
/*   Updated: 2025/08/06 12:44:28 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client() : sockFD_(-1) {
}

Client::Client(int fd) : sockFD_(fd) {
}

Client::Client(Client const &original) {
	// when are we gonna use this ?!
	(void)original;
}

Client::~Client() {
}

/// @todo Implement this function.
Client &Client::operator=(Client const &original) {
	(void)original;
	return (*this);
}

void	Client::advanceOutputBuffer(unsigned int length) {
	this->outputBuffer_.erase(length);
}

void	Client::appendInputBuffer(char *str, int length) {
	if (str) {
		this->inputBuffer_.append(str, length);
	}
}

std::string&	Client::getOutputBuffer() {
	return (outputBuffer_);
}

int	Client::getSockFD() {
	return (sockFD_);
}

/// @todo Implement this function.
void	Client::processInput() {
}

int	Client::setOutputBuffer(char* str, int length) {
	if (str) {
		this->outputBuffer_.assign(str, length);
	}
	return (this->outputBuffer_.length());
}

void	Client::setSockFD(int fd) {
	this->sockFD_ = fd;
}
