/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerState.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoulard <bgoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 12:58:26 by bgoulard          #+#    #+#             */
/*   Updated: 2025/07/25 21:39:18 by bgoulard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <list>
#include <string>

#include "Channel.hpp"
#include "Client.hpp"

class Server;

class ServerState {
  public:
	typedef enum {
		STARTING,
		RUNNING,
		STOPPING,
		// PAUSED, ? maybe
		ERROR
	} Status;

	ServerState(int port, const std::string password, Server &master);
	ServerState &operator=(const ServerState &original);
	bool operator==(const ServerState &original) const;
	bool operator!=(const ServerState &original) const;
	~ServerState();

	std::list< Client >& getClients();
	std::string const &getName() const;
	std::string const &getPassword() const;
	int const		  &getPort() const;
	std::string		   getMinimalInfo(void) const;

	Client*	idClient(int fd);

	void setStatus(Status status);
	Status getStatus(void) const;

  private:
	ServerState::Status	 _status;
	std::string			 _name;
	std::string			 _password;
	int					 _port;
	std::list< Client >	 _clients;
	std::list< Channel > _channels;
	Server				*_master;
};
std::ostream &operator<<(std::ostream &os, const ServerState sst);
