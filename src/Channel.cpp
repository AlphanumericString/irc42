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

/// @todo Exception handling
Channel::Channel(std::string const& name, Client& owner) : channelOperator_(owner), name_(name) {
}

Channel::Channel(Channel const &original) : channelOperator_(original.channelOperator_) {
	*this = original;
}; // when are we gonna use this ?!

Channel::~Channel() {};

Client const&	Channel::getChannelOperator() const {
	return (this->channelOperator_);
}

Client&	Channel::getChannelOperator() {
	return (this->channelOperator_);
}

/// @todo Copies
Channel &Channel::operator=(Channel const &original) {
	(void)original;
	return (*this);
};


const char* Channel::ChannelInvalidNameException::what() const throw() {
	return ("Error: Channel name is invalid");
};

const char*	Channel::ChannelNameTooLongException::what() const throw() {
	return ("Error: Channel name is too long");
};
