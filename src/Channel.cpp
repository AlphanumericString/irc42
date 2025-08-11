/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoulard <bgoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 12:58:52 by bgoulard          #+#    #+#             */
/*   Updated: 2025/08/11 18:41:46 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

/// @todo Exception handling
Channel::Channel(std::string const& name, Client& owner) : owner_(owner), name_(name) {
}

Channel::Channel(Channel const &original) : owner_(original.owner_) {
	*this = original;
}; // when are we gonna use this ?!

Channel::~Channel() {};

Client const&	Channel::getOwner() const {
	return (this->owner_);
}

/// @todo Copies
Channel &Channel::operator=(Channel const &original) {
	this->owner_ = original.getOwner();
	return (*this);
};


const char* Channel::ChannelInvalidNameException::what() const throw() {
	return ("Error: Channel name is invalid");
};

const char*	Channel::ChannelNameTooLongException::what() const throw() {
	return ("Error: Channel name is too long");
};
