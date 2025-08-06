/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoulard <bgoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 12:58:29 by bgoulard          #+#    #+#             */
/*   Updated: 2025/08/06 17:18:58 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/// @file Server.hpp
/// @brief

#pragma once

#include <vector>

#include "Channel.hpp"
#include "Client.hpp"
#include "ServerState.hpp"

#define SERVER_PORT_DFLT	8080
#define SERVER_PWD_DFLT		"password"
#define SERVER_NAME_DFLT	"42irc_server_apbg"

/// @enum e_event_type
/// @brief
typedef enum e_event_type {
	EVENT_READ,
	EVENT_WRITE,
	EVENT_HANGUP,
} t_event_type;

typedef std::vector<std::pair<int, t_event_type> > vecEvent;

/// @class Server
/// @brief Represents the server. Is the main class.
class Server {
  public:
	/// @brief Default constructor.
	/// @param port The port on which the server will listen for inbounds connections.
	/// @param password The password to be able to access the server.
	Server(int port = SERVER_PORT_DFLT, std::string password = SERVER_PWD_DFLT);

	/// @brief
	~Server();

	/// @brief
	/// @param original
	/// @return
	Server	&operator=(const Server &original);

	/// @brief
	void	addStdInToMultiplexing();

	/// @brief
	void	bindSocket();

	/// @brief
	/// @return
	int	exit_state(void);

	/// @brief Accessor for the epollFD_ field.
	/// @return The value of epollFD_.
	int	getEpollFD() const;

	/// @brief
	/// @return
	const ServerState	&getServerState(void) const;

	/// @brief Accessor for the serverFD_ attribute.
	/// @return The value of serverFD_.
	int		getServerFD() const;

	/// @brief
	/// @param flgs
	void	init(int *flgs);

	/// @brief
	void	initiateMultiplexing();

	/// @brief Main loop of the server.
	void	mainLoop(void);

	/// @brief
	void	newUser(void);

	/// @brief Stores the pending events in a buffer implemented as a vector.
	///
	/// This function calls epoll_wait() and populate a local epoll_event array
	/// with the pending events. Then it iterates through this array to add
	/// those events to a vector of pairs of fd (int) and t_event_type (enum).
	/// @return Returns a vector of pairs of fd (int) and t_event_type (enum).
	vecEvent	polling(void);

	/// @brief
	/// @param state
	void	setServerState(ServerState::Status state);

  private:
	int			_serverFD;		///<
	int			_epollFD;		///<
	Client	   *_clients;		///< Pointer to _serverState's list of clients.
	Channel	   *_channels;		///< Pointer to _serverState's list of channels.
	ServerState _serverState;	///< Self-explanatory
								/// Event Loop
								/// Main loop
};
