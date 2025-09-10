/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoulard <bgoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 12:58:52 by bgoulard          #+#    #+#             */
/*   Updated: 2025/09/10 17:49:38 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

#include <list>

#include "Client.hpp"
#include "Server.hpp"
#include "ServerState.hpp"
#include "ansi.h"
#include "generics.hpp"

std::ostream &operator<<(std::ostream &os, ChanMod m) {
	switch (m) {
	case MODE_L:
		os << "l";
		break;
	case MODE_T:
		os << "t";
		break;
	case MODE_I:
		os << "i";
		break;
	case MODE_K:
		os << "k";
		break;
	case MODE_O:
		os << "o";
		break;
	case MODE_UNKNOWN:
	case MODE_NUMBER:
	default:
		os << "?";
		break;
	}
	return (os);
}

void operator|=(ChanMod &a, ChanMod b) {
	a = static_cast< ChanMod >(static_cast< int >(a) | static_cast< int >(b));
}
ChanMod operator|(const ChanMod a, const ChanMod b) {
	return (
		static_cast< ChanMod >(static_cast< int >(a) | static_cast< int >(b)));
}
ChanMod operator&(const ChanMod a, const ChanMod b) {
	return (
		static_cast< ChanMod >(static_cast< int >(a) & static_cast< int >(b)));
}

/// @todo Exception handling
Channel::Channel(std::string const &name, Client &creator) : name_(name) {
	members_.push_back(creator);
	invited_.clear();
	operators_.push_back(creator);
	topic_ = "";
	userLimit_ = 0;
	mode_ = MODE_UNKNOWN;
}

Channel::Channel(Channel const &original) {
	*this = original;
};
Channel::~Channel() {};
Channel &Channel::operator=(Channel const &original) {
	if (this != &original) {
		this->name_ = original.name_;
		this->members_ = original.members_;
		this->operators_ = original.operators_;
		this->invited_ = original.invited_;
		this->topic_ = original.topic_;
		this->userLimit_ = original.userLimit_;
		this->mode_ = original.mode_;
	}
	return (*this);
};

/// @todo Prettify
std::ostream &operator<<(std::ostream &o, const Channel &c) {
	o << c.getName() << "\t[" << 
		HGRN << c.getName() << WHT <<
		YEL "\t+" WHT << c.getMode() << "\t" <<
		(c.getTopic() != "" ? c.getTopic() : "no topic") <<
		MAG "\tmax:" WHT << c.getUserLimit() <<
		MAG "\tcurent:" WHT << c.getMembers().size() <<
		RED "\tops:" WHT << c.getOperators().size() << "]";
	return (o);
}

// [broadcast]
void Channel::broadcast_full(const std::string &s, Server &ser) {
	if (s.empty())
		return;
	if (s.find("\r\n") == std::string::npos)
		throw std::runtime_error("Broadcast message must end with \\r\\n");

	for (std::list< Client >::iterator it =
			 ser.getServerState().getClients().begin();
		 it != ser.getServerState().getClients().end(); ++it) {
		if (this->hasMember(*it)) {
			it->appendToOutputBuffer(s);
		}
	}
}
void Channel::broadcast(const std::string &s, const Client &origin,
						Server &ser) {
	if (s.empty())
		return;
	if (s.find("\r\n") == std::string::npos)
		throw std::runtime_error("Broadcast message must end with \\r\\n");

	for (std::list< Client >::iterator it =
			 ser.getServerState().getClients().begin();
		 it != ser.getServerState().getClients().end(); ++it) {
		if (this->hasMember(*it) && *it != origin) {
			it->appendToOutputBuffer(s);
		}
	}
}
void Channel::updateNick(const Client &c, const std::string &newNick,
						 Server &serv) {

	if (hasMember(c)) {
		for (std::list< Client >::iterator it = getMembers().begin();
			 it != getMembers().end(); ++it) {
			if (*it == c.getSockFD()) {
				it->setNickname(newNick);
				break;
			}
		}
		for (std::list< Client >::iterator it = getOperators().begin();
			 it != getOperators().end(); ++it) {
			if (*it == c.getSockFD()) {
				it->setNickname(newNick);
				break;
			}
		}
		broadcast(":" + c.getNick() + " NICK :" + newNick + "\r\n", c, serv);
	}
	if (isInvited(c)) {
		for (std::list< Client >::iterator it = getInvited().begin();
			 it != getInvited().end(); ++it) {
			if (*it == c.getSockFD()) {
				it->setNickname(newNick);
				break;
			}
		}
	}
}

// [checks]
bool Channel::isFull() const {
	if (!(this->mode_ & MODE_L))
		return (false);
	if (this->userLimit_ <= 0)
		return (true);
	return (this->members_.size() >=
			static_cast< unsigned int >(this->userLimit_));
}
bool Channel::isEmpty() const {
	return (this->members_.empty());
}
bool Channel::operator==(Channel const &other) const {
	return (this->name_ == other.name_);
}
bool Channel::operator==(std::string const &name) const {
	return (this->name_ == name);
}

// [members] {has, add, remove, get}
bool Channel::hasMember(const Client &client) const {
	try {
		searchInList< Client >(this->members_, client);
		return (true);
	} catch (...) {
		return (false);
	}
}
void Channel::removeMember(const Client &c) {
	members_.remove(c);
	if (isOperator(c))
		removeOperator(c);
}
void Channel::addMember(Client &c) {
	if (this->hasMember(c))
		return;
	members_.push_back(c);
}
std::list< Client > &Channel::getMembers() {
	return (this->members_);
}
std::list< Client > const &Channel::getMembers() const {
	return (this->members_);
}

Client &Channel::getMember(const std::string &nick) {
	for (std::list< Client >::iterator it = this->members_.begin();
		 it != this->members_.end(); ++it) {
		if (it->getNick() == nick)
			return (*it);
	}
	throw std::runtime_error("No such client in channel");
}
const Client &Channel::getMember(const std::string &nick) const {
	for (std::list< Client >::const_iterator it = this->members_.begin();
		 it != this->members_.end(); ++it) {
		if (it->getNick() == nick)
			return (*it);
	}
	throw std::runtime_error("No such client in channel");
}
Client &Channel::getMember(const Client &c) {
	for (std::list< Client >::iterator it = this->members_.begin();
		 it != this->members_.end(); ++it) {
		if (*it == c)
			return (*it);
	}
	throw std::runtime_error("No such client in channel");
}
const Client &Channel::getMember(const Client &c) const {
	try {
		return (searchInList< Client >(this->members_, c));
	} catch (...) {
		throw std::runtime_error("No such client in channel");
	}
}

// [operators] {is, add, remove, get}
bool Channel::isOperator(const Client &client) const {
	try {
		searchInList< Client >(this->operators_, client);
		return (true);
	} catch (...) {
	}
	return (false);
}
void Channel::addOperator(Client &c) {
	if (!this->hasMember(c))
		throw std::runtime_error("Operator must be a member of the channel");
	if (this->isOperator(c))
		return;
	this->operators_.push_back(c);
}
void Channel::removeOperator(const Client &c) {
	this->operators_.remove(c);
}
std::list< Client > &Channel::getOperators() {
	return (this->operators_);
}
const std::list< Client > &Channel::getOperators() const {
	return (this->operators_);
}

// [invites] {is, add, remove, get}
bool Channel::isInvited(const Client &client) const {
	try {
		searchInList(this->invited_, client);
		return (false);
	} catch (...) {
		return (false);
	}
}
void Channel::addInvite(const Client &c) {
	if (this->isInvited(c) == true)
		return;
	std::cerr << "added invite!" << std::endl;
	this->invited_.push_back(c);
}
void Channel::removeInvite(const Client &c) {
	this->invited_.remove(c);
}
std::list< Client > &Channel::getInvited() {
	return (this->invited_);
}
const std::list< Client > &Channel::getInvited() const {
	return (this->invited_);
}

// get/set
// [name]
void Channel::setName(const std::string &n) {
	if (n.empty() || n.length() > MAX_CHAN_NAME_LEN)
		throw std::runtime_error("Invalid channel name");
	this->name_ = n;
}
const std::string &Channel::getName() const {
	return (this->name_);
}

// [topic]
void Channel::setTopic(const std::string &t) {
	this->topic_ = t;
}
const std::string &Channel::getTopic() const {
	return (this->topic_);
}

// [other] {user limit, mode}
std::string Channel::getModeStrFormat(std::string *mode_params_ret) const {
	std::string mode_str = "+";
	std::string mode_params = "";

	if (this->mode_ & MODE_I)
		mode_str += "i";
	if (this->mode_ & MODE_T) {
		mode_str += "t";
		if (!this->topic_.empty())
			mode_params += this->topic_;
	}
	if (this->mode_ & MODE_K) {
		mode_str += "k";
		if (!this->key_.empty()) {
			if (!mode_params.empty())
				mode_params += " ";
			mode_params += this->key_;
		}
	}
	if (this->mode_ & MODE_L) {
		mode_str += "l";
		if (this->userLimit_ > 0) {
			if (!mode_params.empty())
				mode_params += " ";
			mode_params += to_string(this->userLimit_);
		}
	}
	if (mode_str == "+")
		mode_str = "";
	if (mode_params_ret)
		*mode_params_ret = mode_params;
	return (mode_str);
}

int Channel::getUserLimit() const {
	return (this->userLimit_);
}
void Channel::setUserLimit(int limit) {
	this->userLimit_ = limit;
}

ChanMod Channel::getMode() const {
	return (this->mode_);
}
void Channel::setMode(ChanMod m) {
	this->mode_ = m;
}
void Channel::unsetMode(const ChanMod m) {
	this->mode_ = static_cast< ChanMod >(static_cast< int >(this->mode_) &
										 ~static_cast< int >(m));
}

const std::string &Channel::getKey() const {
	return (this->key_);
}
void Channel::setKey(const std::string &k) {
	this->key_ = k;
}
