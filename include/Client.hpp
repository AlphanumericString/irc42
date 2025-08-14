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

#include <exception>
#include <string>

#include "AuthState.hpp"
#include "Channel.hpp"
#include "ConnectionState.hpp"

#define UNUSED __attribute__((unused))

class Channel;

class Server;

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
	/// @brief Default constructor.
	Client();

	/// @brief Constructor that takes the client's fd and his IPv4 address.
	/// @param fd The file descriptor associated to the client.
	/// @param ipAddress The IPv4 address of the client.
	/// @param server The server to which the client is connected.
	Client(int fd, char *ipAddress, Server *server);

	/// @brief Copy constructor
	/// @param original The Client object that is to be copied.
	Client(Client const &original);

	/// @brief Default destructor
	~Client();

	/// @brief Erase 'length' characters of the output buffer.
	/// @param length The number of characters to erase.
	void advanceOutputBuffer(unsigned int length);
	/// @brief Appends 'length' char of string 'str' to the client's input
	/// buffer.
	/// @param str The content we want to append to the client's input buffer.
	/// @param length The number of characters we want to append.
	void appendInputBuffer(const char *str, unsigned int length);

	/// @brief Accessor to the host_ attribute.
	/// @return A constant reference to the std::string containing the host
	/// name.
	const std::string &getHost() const;
	void			   setHost(std::string &host);

	/// @brief Accessor to the ipAddress_ attribute.
	/// @return A constant reference to the std::string containing the IPv4
	/// address.
	const std::string &getIPAddress() const;

	/// @brief Accessor for the outputBuffer_ attribute.
	/// @return A reference to the output buffer.
	std::string &getOutputBuffer();

	/// @brief Accessor for the sockFD_ attribute.
	/// @return Returns the value of sockFD_.
	int getSockFD() const;

	t_conState getConState() const;

	const std::string &getRealName(void) const;
	void			   setRealname(const std::string &);

	const std::string &getName(void) const;
	void			   setName(const std::string &);

	/// @brief Assignment operator overload.
	/// @param original The Client object we want to assign from
	/// @return A reference to a Client object.
	Client &operator=(Client const &original);

	/// @brief Processes the commands inside the Client's inputBuffer_
	/// attribute.
	void processInput(Server &s);

	/// @brief Fills or updates the nick_ attribute with the string
	/// `newNickname`.
	/// @param newNickname The newNickname to set.
	void			   setNickname(std::string const &newNickname);
	const std::string &getNick() const;

	/// @brief Fills the client's output buffer with 'length' characters of
	/// string 'str'.
	/// @param buffer The data we want to fill the client's output buffer with.
	/// @param maxLength The maximum number of characters we want to put inside
	/// the client's output buffer.
	/// @return Returns the number of bytes written.
	int setOutputBuffer(char *buffer, unsigned int maxLength);

	/// @brief Setter for the sockFD_ attribute.
	/// @param fd The file descriptor that will be associated with the current
	/// Client object.
	void setSockFD(int fd);

	void inviteClientToChannel(Client &client, Channel &channel);
	void kickClientFromChannel(Client &client, Channel const &channel);

	void changeChannelMode(Channel &channel, ChanMod const mode);
	void changeChannelTopic(Channel &channel, std::string const &topic);

	class NicknameTooLongException : public std::exception {
	  public:
		const char *what() const throw();
	};

  private:
	int				   sockFD_; ///< Socket file descriptor, -1 if not set.
	UNUSED t_conState  connectionState_; ///< Connection state
	UNUSED t_authState authState_;		 ///< Authentication status

	std::string nick_; ///< Unique identifier to distinguish a client amongs
					   /// others, must be unique, 9 characters long.
	std::string host_; ///< Real name of the host that the client is running on.
	std::string name_; ///< Username of the client on the aforementionned host.
	std::string realname_;	  ///< Realname of the client.
	Server *connectedServer_; ///< The server to which this client is connected.
	std::string ipAddress_;	  ///< IPv4 address of the client.
	std::string inputBuffer_; ///< Input buffer.
	std::string outputBuffer_; ///< Output buffer.
	// and current channels. todo! --> ?shared pointer?
	//	- maybe a secondary list for chanels he has mod power into?
};

#undef UNUSED
