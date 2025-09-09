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

#include <arpa/inet.h>
#include <cstring>
#include <exception>
#include <iostream>
#include <netdb.h>
#include <stdexcept>
#include <string>
#include <sys/socket.h>
#include <vector>

#include "ConnectionState.hpp"
#include "ICmd.hpp"
#include "IError.hpp"
#include "IRPL.hpp"

std::ostream &operator<<(std::ostream &o, const t_conState &c) {
	switch (c) {
	case NOT_LOGGED:
		o << "NOT_LOGGED";
		break;
	case REGISTERING:
		o << "REGISTERING";
		break;
	case REGISTERED:
		o << "REGISTERED";
		break;
	case TIMED_OUT:
		o << "TIMED_OUT";
		break;
	case DISCONNECTED:
		o << "DISCONNECTED";
		break;
	case DISCONNECTING:
		o << "DISCONNECTING";
		break;
	default:
		o << "UNKNOWN_STATE";
		break;
	}
	return (o);
}

Client::Client() : sockFD_(-1) {
	nick_ = "*";
	connectionState_ = NOT_LOGGED;
	hasNick = false;
	hasUser = false;
	hasPass = false;
}
Client::Client(int fd, char *ipAddress, Server *server)
	: sockFD_(fd), serv_(server), ipAddress_(ipAddress) {
	if (server->getServerState().isDebug())
		std::cout << "New client[" << "fd:" << this->sockFD_ << "|"
			<< "ip:" << this->ipAddress_ << "]" << std::endl;
	nick_ = "*";
	connectionState_ = NOT_LOGGED;
	hasNick = false;
	hasUser = false;
	hasPass = false;
	resetIdleSince();
	realname_ = "unknown";
	host_ = ipAddress_;
	if (ipAddress_ == "127.0.0.1" || ipAddress_ == "localhost") {
		host_ = "localhost";
	}
}
Client::Client(Client const &original) {
	*this = original;
}
Client::~Client() {}

Client &Client::operator=(Client const &original) {
	if (this != &original) {
		this->sockFD_ = original.getSockFD();
		this->ipAddress_ = original.getIPAddress();
		this->nick_ = original.nick_;
		this->connectionState_ = original.connectionState_;
		this->host_ = original.host_;
		this->username_ = original.username_;
		this->realname_ = original.realname_;
		this->serv_ = original.serv_;
		this->inputBuffer_ = original.inputBuffer_;
		this->outputBuffer_ = original.outputBuffer_;
		this->hasNick = original.hasNick;
		this->hasUser = original.hasUser;
		this->hasPass = original.hasPass;
		this->serv_ = original.serv_;
		this->idleSince_ = original.idleSince_;
	}
	return (*this);
}

std::ostream &operator<<(std::ostream &o, const Client &c) {
	o << c.getNick() << "\t[fd:" << c.getSockFD() << "|ip:" << c.getIPAddress()
	  << "|nname:" << c.getNick() << "|uname:" << c.getUserName()
	  << "|hname:" << c.getHost() << "|rname:" << c.getRealName()
	  << "|state:" << c.getConState() << "]";
	return (o);
}

std::string Client::infostr(void) const {
	return (this->nick_ + "!" + this->username_ + "@" + this->host_);
}

// members functions
// [input buffer]
void Client::appendInputBuffer(const char *str, unsigned int length) {
	if (str) {
		this->inputBuffer_.append(str, length);
	}
}

// [output buffer]
void Client::advanceOutputBuffer(unsigned int length) {
	this->outputBuffer_.erase(0, length);
}
void Client::appendToOutputBuffer(const std::string &s) {
	this->outputBuffer_ += s;
}
std::string &Client::getOutputBuffer() {
	return (outputBuffer_);
}
int Client::setOutputBuffer(char *buffer, unsigned int maxLength) {
	memset(buffer, 0, maxLength);
	strncpy(buffer, this->outputBuffer_.c_str(), maxLength);
	return (strlen(buffer));
}

#define CHECKCMD(line, cmd)                                                    \
	(line.compare(0, cmd::predicate().length(), cmd::predicate()) == 0)

// [cmd processing]
// utility function to create command from input line
static std::vector< IRPL * > try_create(const std::string &line, Client &client,
										Server &s) {
	std::vector< IRPL * > ret;

	try {
		// registration core
		if (CHECKCMD(line, CMD_CAP))
			return (CMD_CAP(line).execute(s, client));
		if (CHECKCMD(line, CMD_PASS))
			return (CMD_PASS(line).execute(s, client));
		if (CHECKCMD(line, CMD_USER))
			return (CMD_USER(line).execute(s, client));
		if (CHECKCMD(line, CMD_NICK))
			return (CMD_NICK(line).execute(s, client));
		if (CHECKCMD(line, CMD_QUIT))
			return (CMD_QUIT(line).execute(s, client));

		// msg core
		if (CHECKCMD(line, CMD_JOIN))
			return (CMD_JOIN(line).execute(s, client));
		if (CHECKCMD(line, CMD_PART))
			return (CMD_PART(line).execute(s, client));
		if (CHECKCMD(line, CMD_PRIVMSG))
			return (CMD_PRIVMSG(line).execute(s, client));

		// info core
		if (CHECKCMD(line, CMD_PING))
			return (CMD_PING(line).execute(s, client));
		if (CHECKCMD(line, CMD_WHOIS))
			return (CMD_WHOIS(line).execute(s, client));
		if (CHECKCMD(line, CMD_WHOWAS))
			return (CMD_WHOWAS(line).execute(s, client));
		if (CHECKCMD(line, CMD_VERSION))
			return (CMD_VERSION(line).execute(s, client));

		// operator core
		if (CHECKCMD(line, CMD_KICK))
			return (CMD_KICK(line).execute(s, client));
		if (CHECKCMD(line, CMD_MODE))
			return (CMD_MODE(line).execute(s, client));
		if (CHECKCMD(line, CMD_INVITE))
			return (CMD_INVITE(line).execute(s, client));
		if (CHECKCMD(line, CMD_TOPIC))
			return (CMD_TOPIC(line).execute(s, client));

		// unknown command
		ret.push_back(new ERR_UNKNOWNCOMMAND(line.substr(0, line.find(" "))));
		return (ret);
	} catch (IError *ir) { // in case of known error we just forward it to
		ret.push_back(ir); // the client to put in the output buffer
	} catch (std::exception &e) { // in case of unknown exception we just
								  // pretend the command is unknown
		std::cerr << "Exception in try_create: " << e.what() << std::endl;
		ret.push_back(new ERR_UNKNOWNCOMMAND(line.substr(0, line.find(" "))));
	}
	return (ret);
}

// process input buffer, execute commands and fill output buffer
void Client::processInput(Server &s) {
	std::vector< IRPL * > resp;
	try {
		while (1) {
			std::string line;

			if (this->inputBuffer_.find("\r\n") == std::string::npos)
				return;
			line = inputBuffer_.substr(0, inputBuffer_.find("\r\n"));
			this->inputBuffer_.erase(0, line.length() + 2);
			resp = try_create(line, *this, s);
			for (std::vector< IRPL * >::iterator it = resp.begin();
				 it != resp.end(); ++it) {

				this->outputBuffer_ += (*it)->toString(s, *this);
				delete (*it);
			}
			line.clear();
			resp.clear();
		}
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
		for (std::vector< IRPL * >::iterator it = resp.begin();
			 it != resp.end(); it++)
			delete (*it);
	}
}

// checks
bool Client::operator==(const Client &o) const {
	return (*this == o.getSockFD());
}
bool Client::operator==(int sock_fd) const { // fd = unique key with epoll
	return (this->getSockFD() == sock_fd);
}

bool Client::operator!=(const Client &o) const {
	return (!(*this == o));
}
// bool Client::operator==(
// 	const std::string nick) const { // nick = unique key in irc rfc
// 	return (this->getNick() == nick);
// }

// getters / setters

// [connection]
const std::string &Client::getIPAddress() const { // ip
	return (this->ipAddress_);
}
t_conState Client::getConState() const { // state
	return this->connectionState_;
}
void Client::setConState(t_conState state) {
	this->connectionState_ = state;
}
const std::string &Client::getHost() const { // host
	return (this->host_);
}
void Client::setHost(std::string &clien_hostname) {
	this->host_ = clien_hostname;
}
int Client::getSockFD() const { // Socket FD
	return (sockFD_);
}
void Client::setSockFD(int fd) {
	this->sockFD_ = fd;
}

// [names]
const std::string &Client::getNick() const { // nick
	return this->nick_;
}
void Client::setNickname(std::string const &newNickname) {
	if (newNickname.length() > MAX_NICKNAME_LENGTH) {
		throw std::runtime_error("Nickname too long");
	}
	this->nick_ = newNickname;
}
const std::string &Client::getUserName(void) const { // user
	return this->username_;
}
void Client::setUserName(const std::string &name) {
	this->username_ = name;
}
const std::string &Client::getRealName(void) const { // realname
	return this->realname_;
}
void Client::setRealname(const std::string &realname) {
	this->realname_ = realname;
}

// [idle/ time]
clock_t Client::getIdleSince() const {
	return (this->idleSince_);
}
void Client::setIdleSince(clock_t t) {
	this->idleSince_ = t;
}
void Client::resetIdleSince() {
	this->idleSince_ = clock();
}

// [server]
Server *Client::getServer() const {
	return (this->serv_);
}
void Client::setServer(Server *s) {
	this->serv_ = s;
}
