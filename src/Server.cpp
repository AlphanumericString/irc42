/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoulard <bgoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:14:33 by bgoulard          #+#    #+#             */
/*   Updated: 2025/07/07 13:14:33 by bgoulard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

///CONSTRUCTORS/////////////////////////////////////////////////////////////////
Server::Server(int port, const std::string password) : _serverState(port, password, *this)
{
	this->_epollFD = -1; // not set
	this->_channels = NULL; // not set
	this->_clients = NULL; // not set
}

///DESTRUCTORS//////////////////////////////////////////////////////////////////
Server::~Server()
{

}

///OPERATOR OVERLOADS///////////////////////////////////////////////////////////
Server	&Server::operator=(Server const &original)
{
	(void) original;
	return (*this);
}

///GETTERS//////////////////////////////////////////////////////////////////////

///SETTERS//////////////////////////////////////////////////////////////////////

///MEMBER FUNCTIONS/////////////////////////////////////////////////////////////

///EXCEPTIONS///////////////////////////////////////////////////////////////////

