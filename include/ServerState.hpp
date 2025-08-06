/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerState.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoulard <bgoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 12:58:26 by bgoulard          #+#    #+#             */
/*   Updated: 2025/08/06 18:18:29 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/// @file ServerState.hpp
/// @brief

#pragma once

#include <list>
#include <string>

#include "Channel.hpp"
#include "Client.hpp"

class Server;

/// @class ServerState
/// @brief Holds data reprensenting the server status as well as current users
/// and channels.
class ServerState {
  public:
	typedef enum {
		STARTING,
		RUNNING,
		STOPPING,
		// PAUSED, ? maybe
		ERROR
	} Status;

	/// @brief Constructor initiating the port_, password_ and master_ fields.
	/// @param port The port the server will listen on.
	/// @param password The password needed to authentify on the server.
	/// @param master The Server to which the current ServerState is related to.
	ServerState(int port, const std::string password, Server &master);

	/// @brief Default destructor
	~ServerState();

	/// @brief Accessor for the clients_ attribute.
	/// @return A reference to a std::list of Client.
	std::list< Client >&	getClients();

	/// @brief
	/// @return
	std::string				getMinimalInfo(void) const;

	/// @brief Accessor for the name_ attribute.
	/// @return A constant reference to a string.
	std::string const&		getName() const;

	/// @brief Accessor for the password_ attribute.
	/// @return A constant reference to a string.
	std::string const&		getPassword() const;

	/// @brief Accessor for the port_ attribute.
	/// @return A constant reference to an int.
	/// @todo Switch to non-const ret ?
	int const&				getPort() const;

	/// @brief Accessor for the status_ attribute.
	/// @return A Status object.
	Status					getStatus(void) const;

	/// @brief
	/// @return
	bool*					getStopPtr(void);

	/// @brief Delete a client that has disconnected from all pertinent spaces.
	/// @param client The client we want to disconnect and delete.
	void					deleteClient(Client &client);

	/// @brief Retrieves a Client through its associated file descriptor.
	/// @param fd The file descriptor we are looking for to be associated to
	/// a client.
	/// @return NULL if no Client matched. Otherwise the address of the Client
	/// that matched.
	Client*					idClient(int fd);

	/// @brief Uses fcntl() to set the O_NONBLOCK option on the provided
	/// file descriptor.
	/// @param fd The file descriptor on which we want to set O_NONBLOCK to.
	/// @return The return value of fcntl().
	static int				makeSocketNonBlocking(int fd);

	/// @brief Creates a new client associated with the file descriptor 'fd'
	/// and fills its fields.
	/// @param fd The file descriptor of the new client.
	/// @param ipAddress The IPv4 address of the new client.
	void					newClient(int fd, char* ipAddress);

	/// @brief Assignment operator overload
	/// @param original The ServerState object we want to assign from.
	/// @return A reference to a ServerState object.
	ServerState&			operator=(const ServerState &original);

	/// @brief Is equal operator overload
	/// @param original The ServerState object we want to compare to.
	/// @return TRUE if both ServerState objects are equal (as defined per
	/// implementation), FALSE otherwise.
	bool					operator==(const ServerState &original) const;

	/// @brief Is different operator overload
	/// @param original The ServerState object we want to compare to.
	/// @return TRUE if both ServerState objects are different (as defined per
	/// implementation), FALSE otherwise.
	bool					operator!=(const ServerState &original) const;

	/// @brief Setter for the status_ attribute.
	/// @param status The status we want to set to.
	void					setStatus(Status status);

  private:
	bool					_stop;		///< Flag indicating if server has to stop.
	ServerState::Status		_status;	///< Current status of the Server.
	std::string				_name;		///< Name of the Server.
	std::string				_password;	///< Password to authentify to the Server.
	int						_port;		///< Port of the Server.
	std::list< Client >		_clients;	///< Clients connected to the Server.
	std::list< Channel >	_channels;	///< Channels active on the Server.
	Server*					_master;	///< Server object to which the current ServerStatus belongs to.
};
std::ostream &operator<<(std::ostream &os, const ServerState sst);
