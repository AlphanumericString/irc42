/// @file Server.hpp
/// @brief Header for the Server class
/// @ingroup ServerGroup

#ifndef SERVER_HPP
#define SERVER_HPP

#include <sys/epoll.h>

#include "ServerState.hpp"

/// @brief Maximum number of pending connections in the queue.
#define BACKLOG 10

/// @class Server
/// @brief Represents the core IRC server managing clients, channels, and network events.
///
/// The Server class encapsulates the setup and lifecycle management of an IRC server
/// using epoll for multiplexing I/O events. It manages clients and channels through
/// pointers to its ServerState object.
class Server
{
private:
	int			_serverFD;		///< File descriptor for the server's listening socket.
	int			_epollFD;		///< File descriptor for the epoll instance used in event multiplexing.
	epoll_event	_events[64];	///< Array of epoll events to monitor for incoming I/O.
	Client		*_clients;		///< Pointer to the list of connected clients, managed by ServerState.
	Channel		*_channels;		///< Pointer to the list of active channels, managed by ServerState.
	ServerState	*_serverState;	///< Pointer to the internal server state container.

public:
	/// @brief Default constructor. Initializes the server object without starting it.
	Server();

	/// @brief Copy constructor.
	/// @param other The server object to copy.
	Server(const Server &other);

	/// @brief Destructor. Cleans up resources and closes sockets if needed.
	~Server();

	/// @brief Assignment operator overload.
	/// @param other The server object to assign.
	/// @return A reference to the modified server.
	Server&			operator=(const Server &other);

	/// @brief Binds the server socket to the server's port and prepares it
	/// for listening.
	void			bindSocket();

	/// @brief Gets the file descriptor for the epoll instance.
	/// @return A constant reference to the epoll FD.
	int const&		getEpollFD() const;

	/// @brief Gets the server's listening socket file descriptor.
	/// @return A constant reference to the server FD.
	int	const&		getServerFD() const;

	/// @brief
	/// @return
	ServerState*	getServerState() const;

	/// @brief
	void			handleEvent();

	/// @brief Initializes the epoll instance and adds the server socket to
	/// watch list.
	void			initiateMultiplexing();

	/// @brief Sets the epoll instance file descriptor.
	/// @param epollFD fd The new epoll FD.
	void			setEpollFD(int fd);

	/// @brief Sets the server's listening socket file descriptor.
	/// @param fd The new server FD.
	void			setServerFD(int fd);

	/// @brief Sets up the entire server: socket, epoll, state, etc.
	void			setUpServer();
};

#endif // SERVER_HPP
