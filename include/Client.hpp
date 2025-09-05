/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoulard <bgoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 12:58:32 by bgoulard          #+#    #+#             */
/*   Updated: 2025/08/12 15:14:05 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/// @file Client.hpp
/// @brief

#pragma once

#include <ctime>
#include <string>

#include "AuthState.hpp"
#include "ConnectionState.hpp"

#define UNUSED __attribute__((unused))

class Channel;
class Server;
class ICmd;
class IRPL;

#define MAX_NICKNAME_LENGTH 9

/// @class Client
/// @brief Represents a connected user.
///
/// Represents a connected user with their socket file descriptor, connection
/// state, authentication status, nickname, username, hostname, and current
/// channels. It manages partial message buffering since non-blocking reads
/// might receive incomplete IRC messages. Each client has input/output buffers
/// and tracks registration state.
class Client {
  public:
	Client();
	Client(int fd, char *ipAddress, Server *server);
	Client(Client const &original);
	~Client();
	Client &operator=(Client const &original);

	// [print]
	friend std::ostream &operator<<(std::ostream &o, const Client &c);

	// [ buffers ]
	// ibuf
	void		 appendInputBuffer(const char *str, unsigned int length);
	// obuf
	void		 appendToOutputBuffer(const std::string &str);
	void		 advanceOutputBuffer(unsigned int length);
	std::string &getOutputBuffer();
	int			 setOutputBuffer(char *buffer, unsigned int maxLength);

	// cmds
	std::string infostr(void) const; // nick!user@host
	void		processInput(Server &s);

	// checks
	bool operator==(const Client &o) const;
	bool operator==(int sock_fd) const;
	bool operator!=(const Client &o) const;
	bool operator==(const std::string nick) const;

	// get/set
	// [connection]
	const std::string &getIPAddress() const;
	t_conState		   getConState() const;
	void			   setConState(t_conState state);
	void			   setHost(std::string &host);
	const std::string &getHost() const;
	void			   setSockFD(int fd);
	int				   getSockFD() const;

	// [names]
	const std::string &getRealName(void) const;
	void			   setRealname(const std::string &);
	const std::string &getUserName(void) const;
	void			   setUserName(const std::string &);
	void			   setNickname(std::string const &newNickname);
	const std::string &getNick() const;

	// [idle/ time]
	clock_t getIdleSince() const;
	void	setIdleSince(clock_t t);
	void	resetIdleSince();

	// [server]
	Server *getServer() const;
	void	setServer(Server *s);

	// [away]
	const std::string &getAwayMsg() const;
	void			   setAwayMsg(const std::string &msg);

	bool hasNick;
	bool hasUser;
	bool hasPass;

  private:
	int				   sockFD_; /// -1 if not set.
	t_conState		   connectionState_;
	UNUSED t_authState authState_;

	clock_t idleSince_;

	std::string nick_;
	std::string host_;
	std::string username_;
	std::string realname_;

	std::string awayMsg_;

	Server	   *serv_;		/// Pointer to the server instance.
	std::string ipAddress_; ///< IPv4 address of the client.

	std::string inputBuffer_;  ///< Input buffer.
	std::string outputBuffer_; ///< Output buffer.
};

#undef UNUSED
