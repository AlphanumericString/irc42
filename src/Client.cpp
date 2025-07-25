/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoulard <bgoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 12:58:32 by bgoulard          #+#    #+#             */
/*   Updated: 2025/07/25 21:31:17 by bgoulard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client() {}
Client::Client(Client const &original) {
	// when are we gonna use this ?!
	(void)original;
}

Client::~Client() {}

Client &Client::operator=(Client const &original) {
	(void)original;
	return (*this);
}

int	Client::getSockFD() {
	return (sockFD_);
}

void	Client::setSockFD(int fd) {
	this->sockFD_ = fd;
}
