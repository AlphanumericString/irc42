/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoulard <bgoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 12:58:29 by bgoulard          #+#    #+#             */
/*   Updated: 2025/07/25 21:28:58 by bgoulard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Channel.hpp"
#include "Client.hpp"
#include "ServerState.hpp"
#include "smart_ptr.hpp"

#define SERVER_PORT_DFLT	8080
#define SERVER_PWD_DFLT		"password"
#define SERVER_NAME_DFLT	"42irc_server_apbg"

/// @class Server
/// @brief
class Server {
  public:
	/// @brief
	/// @param port
	/// @param password
	Server(int port = SERVER_PORT_DFLT, std::string password = SERVER_PWD_DFLT);

	/// @brief
	~Server();

	/// @brief
	/// @param original
	Server	&operator=(const Server &original);

	/// @brief
	void	bindSocket();

	/// @brief
	/// @return
	int	exit_state(void);

	/// @brief
	/// @return
	const ServerState	&getServerState(void) const;

	/// @brief
	void	handleEvent();

	/// @brief
	/// @param fd
	void	handleNewUser(const int fd);

	/// @brief
	/// @param buffer
	/// @param fd
	void	handleMessage(char* buffer, int fd);

	/// @brief
	void	init(int *flgs);

	/// @brief
	void	initiateMultiplexing();

	/// @brief
	void	run(void);

	/// @brief
	/// @param state
	void	setServerState(ServerState::Status state);

  private:
	/// @brief
	int	makeSocketNonBlocking(int fd);

	int			_serverFD;		///<
	int			_epollFD;		///<
	Client	   *_clients;		///< Pointer to _serverState's list of clients.
	Channel	   *_channels;		///< Pointer to _serverState's list of channels.
	ServerState _serverState;	///< Self-explanatory
								/// Event Loop
								/// Main loop
};
