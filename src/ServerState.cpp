/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerState.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoulard <bgoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:14:31 by bgoulard          #+#    #+#             */
/*   Updated: 2025/07/07 13:14:31 by bgoulard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ServerState.hpp"
#include "Channel.hpp"
#include "Client.hpp"
#include "Server.hpp"
#include <list>

///CONSTRUCTORS/////////////////////////////////////////////////////////////////
ServerState::ServerState(const ServerState &original)
{
	(void) original;
}

ServerState::ServerState(int p, const std::string pwd, Server &m) : _password(pwd), _port(p)
{
	this->_master = &m;
	this->_channels = std::list<Channel>();
	this->_clients	= std::list<Client>();
}

///DESTRUCTORS//////////////////////////////////////////////////////////////////
ServerState::~ServerState()
{

}

///OPERATOR OVERLOADS///////////////////////////////////////////////////////////
ServerState	&ServerState::operator=(const ServerState &original)
{
	(void) original;
	return (*this);
}

///GETTERS//////////////////////////////////////////////////////////////////////
std::string const	&ServerState::getName() const
{
	return (this->_name);
}

std::string const	&ServerState::getPassword() const
{
	return (this->_password);
}

int const			&ServerState::getPort() const
{
	return (this->_port);
}

///SETTERS//////////////////////////////////////////////////////////////////////

///MEMBER FUNCTIONS/////////////////////////////////////////////////////////////

///EXCEPTIONS///////////////////////////////////////////////////////////////////


