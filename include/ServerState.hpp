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

#include <fstream>
#include <list>
#include <string>

#include "Channel.hpp"
#include "Client.hpp"
#include "smart_ptr.hpp"

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
	bool		 operator==(const ServerState &original) const;
	bool		 operator!=(const ServerState &original) const;
	~ServerState();

	std::string const &getName() const;
	std::string const &getPassword() const;
	int const		  &getPort() const;
	const std::string &getHost() const;
	std::string		   getMinimalInfo(void) const;

	void   setStatus(Status status);
	Status getStatus(void) const;

	std::list< ShrdSmartPtr< Client > > &getClients(void);
	std::list< ShrdSmartPtr< Channel > > &getChanels(void);

  private:
	std::ofstream	  _logfile;
	// general infos
	std::string		  _name;
	std::string		  _password;
	int				  _port;
	const std::string _host;

	// server utils infos
	std::list< ShrdSmartPtr< Client > >	 _clients;
	std::list< ShrdSmartPtr< Channel > > _channels;

	// server state
	ServerState::Status _status;
	Server			   *_master;
};
std::ostream &operator<<(std::ostream &os, const ServerState &sst);
