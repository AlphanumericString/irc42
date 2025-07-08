/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoulard <bgoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 12:58:29 by bgoulard          #+#    #+#             */
/*   Updated: 2025/07/07 12:58:29 by bgoulard         ###   ########.fr       */
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

class Server {
  private:
	int			_epollFD;	  //->
	Client	   *_clients;	  //-> Pointer	to _serverState's list of clients.
	Channel	   *_channels;	  //-> Pointer to _serverState's list of channels.
	ServerState _serverState; //-> Self-explanatory
							  // Event Loop
							  // Main loop

  public:
	// Constructors
	Server(int port = SERVER_PORT_DFLT, std::string password = SERVER_PWD_DFLT);
	// Destructors
	~Server();
	// Operator overloads
	Server &operator=(const Server &original);
	void	run(void);
	int		exit_state(void);
	void	setServerState(ServerState::Status state);
	const ServerState	&getServerState(void) const;
};
