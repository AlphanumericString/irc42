/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerState.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoulard <bgoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 12:58:26 by bgoulard          #+#    #+#             */
/*   Updated: 2025/08/05 17:05:11 by apetitco         ###   ########.fr       */
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

	/// @brief
	/// @param client The client we want to disconnect and delete.
	void	deleteClient(Client& client);

	/// @brief
	/// @param fd The file descriptor we are looking for to be associated to
	/// a client.
	/// @return NULL if no Client matched. Otherwise the address of the Client
	/// that matched.
	Client*	idClient(int fd);

	/// @brief
	/// @param fd The file descriptor of the new Client.
	void	newClient(int fd);

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
