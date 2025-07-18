/**
 * @file ServerState.hpp
 * @brief Defines the ServerState class, which tracks the runtime state of the
 * IRC server.
 *
 * This file is part of the core logic of the IRC server implementation.
 * It provides the ServerState class that encapsulates connected clients,
 * active channels, and the server's status. ServerState acts as a state
 * container, facilitating access to core data during server runtime.
 *
 * @ingroup ServerGroup
 * @author
 * apetitco
 */

#ifndef SERVERSTATE_HPP
#define SERVERSTATE_HPP

#include <list>
#include <string>

#include "Channel.hpp"
#include "Client.hpp"

/// @brief Default port on which the server listens.
#define SERVER_PORT_DFLT	"2106"

/// @brief Default password required to connect to the server.
#define SERVER_PWD_DFLT		"password"

/// @brief Default name used to identify the server instance.
#define SERVER_NAME_DFLT	"42irc_server_apbg"

class Server;

/**
 * @class ServerState
 * @brief Represents the internal state of the IRC server, including its clients,
 * channels and operational status.
 *
 * This class encapsulates the runtime data of the server, such as connected clients, open channels,
 * and current status (e.g., RUNNING or ERROR). It acts as the central state
 * manager and is linked to the owning Server instance.
 *
 */
class ServerState
{
public:
	/**
	* @enum Status
	* @brief Represents the current lifecycle stage of the server.
	*/
	typedef enum
	{
		STARTING,	///< Server is booting up
		RUNNING,	///< Server is fully operational
		STOPPING,	///< Server is shutting down
		// PAUSED,	///< (Optional) Could represent a paused or maintenance state
		ERROR		///< Server encountered a fatal error
	} Status;

  private:
	/// @brief Current operational status of the server.
	ServerState::Status	 _status;

	/// @brief Server name.
	std::string			 _name;

	/// @brief Server password.
	std::string			 _password;

	/// @brief Port on which the server is listening.
	std::string			 _port;

	/// @brief List of currently connected clients.
	std::list< Client >	 _clients;

	/// @brief List of active IRC channels.
	std::list< Channel > _channels;

	/// @brief Pointer to the Server instance that owns this ServerState.
	Server				*_master;

public:

	/**
	 * @brief Constructs a ServerState instance.
	 * @param port Port number on which the server is running.
	 * @param password Password required to join the server.
	 * @param master Reference to the master Server object owning this state.
	 */
	ServerState(int port, const std::string password, Server &master);

	/**
	 * @brief Destructor. Cleans up internal state.
	 */
	~ServerState();

	/**
	 * @brief Assignment operator.
	 * @param other The ServerState to copy.
	 * @return A reference to the current ServerState.
	 */
	ServerState &operator=(const ServerState &other);

	/**
	 * @brief Retrieves the name of the server.
	 * @return Constant reference to the server name.
	 */
	std::string const &getName() const;

	/**
	 * @brief Retrieves the server's password.
	 * @return Constant reference to the password.
	 */
	std::string const &getPassword() const;

	/**
	 * @brief Retrieves the port the server is listening on.
	 * @return Constant reference to the port string.
	 */
	std::string const		  &getPort() const;

	/**
	 * @brief Retrieves a minimal summary of the server's state.
	 * @return A formatted string representing essential server info.
	 */
	std::string		   getMinimalInfo(void) const;

	/**
	 * @brief Gets the current server status.
	 * @return The server's operational status.
	 */
	Status getStatus(void) const;

	/**
	 * @brief Sets the current server status.
	 * @param status The new status to apply.
	 */
	void setStatus(Status status);
};

#endif // !SERVERSTATE_HPP
