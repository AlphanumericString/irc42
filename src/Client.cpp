/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoulard <bgoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 12:58:32 by bgoulard          #+#    #+#             */
/*   Updated: 2025/08/11 18:42:12 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

#include <cstring>
#include <iostream>
#include <string>

#include "ISendable.hpp"

Client::Client() : sockFD_(-1) {
	nick_ = "*";
}

Client::Client(int fd, char *ipAddress, Server *server)
	: sockFD_(fd), connectedServer_(server), ipAddress_(ipAddress) {
	std::cout << "Nouveau client:" << std::endl
			  << "fd: " << this->sockFD_ << std::endl
			  << "ip address: " << this->ipAddress_ << std::endl;
	nick_ = "*";
}

Client::Client(Client const &original) {
	*this = original;
}

Client::~Client() {}

void Client::advanceOutputBuffer(unsigned int length) {
	this->outputBuffer_.erase(length);
}

void Client::appendInputBuffer(const char *str, unsigned int length) {
	if (str) {
		this->inputBuffer_.append(str, length);
	}
}

void Client::setHost(std::string &clien_hostname) {
	this->host_ = clien_hostname;
}

const std::string &Client::getHost() const {
	return (this->host_);
}

const std::string &Client::getIPAddress() const {
	return (this->ipAddress_);
}

std::string &Client::getOutputBuffer() {
	return (outputBuffer_);
}

int Client::getSockFD() const {
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

// pb: isendable is an abstract class so need either '&' or '*'
// cant '&' on temp obj (obj are considered temp as created only in the
// function) so need to pass by '*' if im already doing '*' with all that 'new'
// keyword it may be usefull to do a factory for ISendable
//
static ISendable *try_exec(const std::string &line) {
	try {
		if (line.compare(0, CMD_PASS::predicate().length(),
						 CMD_PASS::predicate()) == 0)
			return (new CMD_PASS(line));
		if (line.compare(0, CMD_USER::predicate().length(),
						 CMD_USER::predicate()) == 0)
			return (new CMD_USER(line));
		if (line.compare(0, CMD_NICK::predicate().length(),
						 CMD_NICK::predicate()) == 0)
			return (new CMD_NICK(line));
		throw(new ERR_UNKNOWNCOMMAND("toto"));
	} catch (IError *ir) {
		return (ir);
	}
}

/// @todo Implement this function.
/// todo:
///  - check if string has no \n
///  -> ?y => go out - return
///  get line
///  split line by delim ' '
///  send to
///		CommandProcessor() -> 'ISendable &' {ICommand || IError}
///	take ISendable and add to OutputBuffer via virtual toString inherited by
/// ICommand and IError
void Client::processInput(Server &s) {
	std::string line;
	if (this->inputBuffer_.find("\r\n") == std::string::npos)
		return;
	line = inputBuffer_.substr(inputBuffer_.find("\r\n"));
	ISendable *resp = try_exec(line);
	this->outputBuffer_ += resp->toString(s, *this);
	delete (resp);
}

#define MAX_NICKNAME_LENGTH 9

const std::string &Client::getNick() const {
	return this->nick_;
}

void Client::setNickname(std::string const &newNickname) {
	if (newNickname.length() > MAX_NICKNAME_LENGTH) {
		throw NicknameTooLongException();
	}
	this->nick_ = newNickname;
}

int Client::setOutputBuffer(char *buffer, unsigned int maxLength) {
	memset(buffer, 0, maxLength);
	strncpy(buffer, this->outputBuffer_.c_str(), maxLength);
	return (strlen(buffer));
}

void Client::setSockFD(int fd) {
	this->sockFD_ = fd;
}

const char *Client::NicknameTooLongException::what() const throw() {
	return ("Error: New nickname is too long.");
}

t_conState Client::getConState() const {
	return this->connectionState_;
}
const std::string &Client::getRealName(void) const {
	return this->realname_;
}
void Client::setRealname(const std::string &realname) {
	this->realname_ = realname;
}

const std::string &Client::getName(void) const {
	return this->name_;
}
void Client::setName(const std::string &name) {
	this->name_ = name;
}
