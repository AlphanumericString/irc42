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
#include <vector>

#include "PrevClients.hpp"
#include "smart_ptr.hpp"

class Client;
class Channel;
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
	~ServerState();

	std::list< Client >		  &getClients();
	const std::list< Client > &getClients() const;

	std::list< Channel >	   &getChannels();
	const std::list< Channel > &getChannels() const;
	const Channel			   *getChannel(const std::string &name) const;
	Channel					   *getChannel(const std::string &name);

	std::string getMinimalInfo(void) const;

	std::string const &getName() const;
	std::string const &getPassword() const;
	int const		  &getPort() const;
	const std::string &getHostname(void) const;

	bool *getStopPtr(void);

	void   setStatus(Status status);
	Status getStatus(void) const;

	void	newClient(int fd, char *ipAddress);
	void	deleteClient(Client &client);
	Client *idClient(int fd);

	ServerState &operator=(const ServerState &original);
	bool		 operator==(const ServerState &original) const;
	bool		 operator!=(const ServerState &original) const;

	Client		 *getClient(const std::string &name);
	Client		 *getClient(int fd);
	const Client *getClient(const std::string &name) const;
	const Client *getClient(int fd) const;

	const std::string &getDescription() const;
	void			   setDescription(const std::string &desc);

	void							  addPrevClient(const Client &c);
	const std::vector< PrevClients > &getPrevClients() const;
	std::vector< PrevClients > getPrevClients(const std::string &name) const;

	bool isDebug() const {
		return dbg_;
	}
	void setDebug(bool dbg) {
		dbg_ = dbg;
	}

  private:
	bool dbg_;

	std::string			 desc;		///< Description of the Server.
	bool				 stop_;		///< Flag indicating if server has to stop.
	ServerState::Status	 status_;	///< Current status of the Server.
	std::string			 name_;		///< Name of the Server.
	std::string			 password_; ///< Password to authentify to the Server.
	int					 port_;		///< Port of the Server.
	std::list< Client >	 clients_;	///< Clients connected to the Server.
	std::list< Channel > channels_; ///< Channels active on the Server.
	Server *master_; ///< Server object to which the current ServerStatus
					 ///< belongs to.
	const std::string		   hostname_;
	std::vector< PrevClients > prevClients_; // whowas util
};
std::ostream &operator<<(std::ostream &os, const ServerState sst);
