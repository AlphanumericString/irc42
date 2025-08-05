/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoulard <bgoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 12:58:32 by bgoulard          #+#    #+#             */
/*   Updated: 2025/08/05 17:25:26 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client() : sockFD_(-1) {
}

Client::Client(Client const &original) {
	// when are we gonna use this ?!
	(void)original;
}

Client::~Client() {}

Client &Client::operator=(Client const &original) {
	(void)original;
	return (*this);
}

void	Client::advanceOutputBuffer(int length) {
	(void)length;
}

void	Client::appendInputBuffer(char *buffer, int length) {
	(void)buffer;
	(void)length;
}

std::string&	Client::getOutputBuffer() {
	return (outputBuffer_);
}

int	Client::getSockFD() {
	return (sockFD_);
}

void	Client::processInput() {
}

int	Client::setOutputBuffer(char* str) {
	int	ret = 0;

	(void)str;

	return (ret);
}

int	Client::setOutputBuffer(char* str, int length) {
	int	ret = 0;

	(void)str;
	(void)length;

	return (ret);
}

void	Client::setSockFD(int fd) {
	this->sockFD_ = fd;
}
