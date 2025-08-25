/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoulard <bgoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 12:58:29 by bgoulard          #+#    #+#             */
/*   Updated: 2025/08/08 18:34:29 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/// @file Server.hpp
/// @brief

#pragma once

#include <vector>

#include "ServerState.hpp"

#define SERVER_PORT_DFLT 8080
#define SERVER_PWD_DFLT	 "password"
#define SERVER_NAME_DFLT "42irc_server_apbg"
#define ADMIN_EMAIL_DFLT "bgoulard@student.42.fr"

/// @typedef eventType
/// @brief Represents the different events to be processed.
typedef enum {
	EVENT_READ,	  ///< Read event.
	EVENT_WRITE,  ///< Write event.
	EVENT_HANGUP, ///< Hang up event (disconnected).
} eventType;

/// @typedef vecEvent
/// @brief Vector storing the events that are to be processed.
///
/// Vector of pairs of file descriptor () and eventType.
typedef std::vector< std::pair< int, eventType > > vecEvent;

/// @class Server
/// @brief The main orchestrator.
///
/// The main orchestrator that owns the epoll file descriptor and runs the
/// event loop. It maintains collections of all clients, channels, and handles
/// the core server lifecycle. This class processes epoll events and delegates
/// to appropriate handlers.
class Server {
  public:
	/// @brief Default constructor.
	/// @param port The port on which the server will listen for inbounds
	/// connections.
	/// @param password The password to be able to access the server.
	Server(int port = SERVER_PORT_DFLT, std::string password = SERVER_PWD_DFLT);

	/// @brief Default destructor.
	~Server();

	/// @brief Adds the standard input to the list of monitored file descriptors
	/// of epoll().
	void addStdInToMultiplexing(void);

	/// @brief Bind the server socket to any inbound addresses.
	void bindSocket(void);

	/// @brief Stores the pending events in a buffer implemented as a vector.
	///
	/// This function calls epoll_wait() and populate a local epoll_event array
	/// with the pending events. Then it iterates through this array to add
	/// those events to a vector of pairs of fd (int) and t_event_type (enum).
	/// @return Returns a vector of pairs of fd (int) and t_event_type (enum).
	vecEvent collectReadyEvents(void);

	/// @brief
	/// @return
	int exit_state(void);

	/// @brief Accessor for the epollFD_ attribute.
	/// @return The value of epollFD_.
	int getEpollFD(void) const;

	/// @brief Accessor for the serverFD_ attribute.
	/// @return The value of serverFD_.
	int getServerFD(void) const;

	/// @brief Accessor for the serverState_ attribute.
	/// @return A constant reference to a ServerState object.
	const ServerState &getServerState(void) const;

	/// @brief
	/// @param client
	void handleClientDisconnect(Client &client);

	/// @brief
	/// @param client
	void handleClientRead(Client &client);

	/// @brief
	/// @param client
	void handleClientWrite(Client &client);

	/// @brief
	void handleNewConnection();

	/// @brief
	void handleStdinInput();

	/// @brief Handles the initialisation of the server.
	/// @param flags The flags that are to be set for the file descriptors.
	void init(int *flags);

	/// @brief Initialises epoll()'s multiplexing.
	void initiateMultiplexing(void);

	/// @brief Main loop of the server.
	void mainLoop(void);

	/// @brief Assignment operator overload.
	/// @param original The Server object we want to assign from.
	/// @return A reference to a Server object.
	Server &operator=(const Server &original);

	/// @brief Setter for the serverState_ attribute.
	/// @param state The state to set.
	void setServerState(ServerState::Status state);

  private:
	int			serverFD_;	  ///< File descriptor for te server socket.
	int			epollFD_;	  ///< File descriptor for the multiplexing.
	ServerState serverState_; ///< Self-explanatory
							  /// Event Loop
							  /// Main loop
	std::string stdinBuffer;
};
