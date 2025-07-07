/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerState.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoulard <bgoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 12:58:26 by bgoulard          #+#    #+#             */
/*   Updated: 2025/07/07 12:58:26 by bgoulard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <list>

#include "Channel.hpp"
#include "Client.hpp"

class	Server;

class	ServerState
{
	private:
		std::string			_name;
		std::string			_password;
		int					_port;
		std::list<Client>	_clients;
		std::list<Channel>	_channels;
		Server				*_master;

	public:
		// Constructors
		ServerState(ServerState const &original);
		ServerState(int port, const std::string password, Server &master);
		// Destructors
		~ServerState();
		// Operator overloads
		ServerState	&operator=(ServerState const &original);
		// Getters
		std::string const	&getName() const;
		std::string const	&getPassword() const;
		int const			&getPort() const;
		// Setters
		// Member functions
		// Exceptions
};

