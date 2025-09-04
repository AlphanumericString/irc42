/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoulard <bgoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 12:58:52 by bgoulard          #+#    #+#             */
/*   Updated: 2025/08/12 15:22:53 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

#include <list>

#include "Client.hpp"
#include "Server.hpp"
#include "ServerState.hpp"
#include "generics.hpp"

std::ostream &operator<<(std::ostream &os, ChanMod m)
{
	if (m & MODE_L)
		os << "l";
	if (m & MODE_T)
		os << "t";
	if (m & MODE_I)
		os << "i";
	if (m & MODE_S)
		os << "s";
	if (m == MODE_UNKNOWN)
		os << "unknown";
	return (os);
}
/// @todo Exception handling
Channel::Channel(std::string const &name, Client &owner)
	: owner_(owner), name_(name) {
	members_.push_back(owner);
	invited_.clear();
	operators_.push_back(owner);
	topic_ = "";
	topicProtected_ = false;
	userLimit_ = 0;
	mode_ = MODE_UNKNOWN;
}

Channel::Channel(Channel const &original) : owner_(original.owner_) {
	*this = original;
};
Channel::~Channel() {};
Channel &Channel::operator=(Channel const &original) {
	if (this != &original) {
		this->owner_ = original.owner_;
		this->name_ = original.name_;
		this->members_ = original.members_;
		this->operators_ = original.operators_;
		this->invited_ = original.invited_;
		this->topic_ = original.topic_;
		this->topicProtected_ = original.topicProtected_;
		this->userLimit_ = original.userLimit_;
		this->mode_ = original.mode_;
	}
	return (*this);
};

// [broadcast]
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
	if (this->owner_ == c.getSockFD()) {
		this->owner_.setNickname(newNick);
	}
}

// [checks]
bool Channel::isFull() const {
	return (this->userLimit_ != 0 && this->members_.size() >= this->userLimit_);
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
}
void Channel::addMember(Client &c) {
	if (this->hasMember(c))
		return;
	if (this->mode_ & MODE_L && getMembers().size() >= getUserLimit() &&
		getUserLimit() != 0)
		throw std::runtime_error("Channel is full");
	if (this->mode_ & MODE_I && !this->isInvited(c))
		throw std::runtime_error("You must be invited to join this channel");
	members_.push_back(c);
}
std::list< Client > &Channel::getMembers() {
	return (this->members_);
}
std::list< Client > const &Channel::getMembers() const {
	return (this->members_);
}

// [operators] {is, add, remove, get}
bool Channel::isOperator(const Client &client) const {
	if (this->owner_ == client)
		return (true);
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
	if (this->owner_ == c)
		throw std::runtime_error("Cannot remove owner from operators");
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
		searchInList< Client >(this->invited_, client);
		return (true);
	} catch (...) {
		return (false);
	}
}
void Channel::addInvite(const Client &c) {
	if (this->isInvited(c))
		return;
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

// [owner]
Client &Channel::getOwner() {
	return (this->owner_);
}
const Client &Channel::getOwner() const {
	return (this->owner_);
}
void Channel::setOwner(Client &c) {
	if (!this->hasMember(c))
		throw std::runtime_error("New owner must be a member of the channel");
	this->owner_ = c;
	if (!this->isOperator(c))
		this->addOperator(c);
}

// [topic]
void Channel::setTopic(const std::string &t) {
	this->topic_ = t;
}
const std::string &Channel::getTopic() const {
	return (this->topic_);
}
void Channel::setTopicProtected(bool b) {
	this->topicProtected_ = b;
}
bool Channel::isTopicProtected() const {
	return (this->topicProtected_);
}

// [other] {user limit, mode}
unsigned int Channel::getUserLimit() const {
	return (this->userLimit_);
}
void Channel::setUserLimit(unsigned int limit) {
	this->userLimit_ = limit;
}

ChanMod Channel::getMode() const {
	return (this->mode_);
}
void Channel::setMode(ChanMod m) {
	this->mode_ = m;
}
