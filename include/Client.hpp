/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoulard <bgoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 12:58:32 by bgoulard          #+#    #+#             */
/*   Updated: 2025/08/06 17:33:48 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/// @file Client.hpp
/// @brief

#pragma once

#include <string>
#include "AuthState.hpp"
#include "ConectionState.hpp"

#define UNUSED __attribute__((unused))

/// @class Client
/// @brief Class representing a single client.
class Client {
  public:
	/// @brief Default constructor.
	Client();

	/// @brief Constructor that takes the client's fd and his IPv4 address.
	/// @param fd The file descriptor associated to the client.
	/// @param ipAddress The IPv4 address of the client.
	Client(int fd, char* ipAddress);

	/// @brief Copy constructor
	/// @param original The Client object that is to be copied.
	Client(Client const &original);

	/// @brief Default destructor
	~Client();

	/// @brief Erase 'length' characters of the output buffer.
	/// @param length The number of characters to erase.
	void				advanceOutputBuffer(unsigned int length);

	/// @brief Appends 'length' char of string 'str' to the client's input
	/// buffer.
	/// @param str The content we want to append to the client's input buffer.
	/// @param length The number of characters we want to append.
	void				appendInputBuffer(char* str, unsigned int length);

	/// @brief Accessor to the host_ attribute.
	/// @return A constant reference to the std::string containing the host name.
	const std::string&	getHost() const;

	/// @brief Accessor to the ipAddress_ attribute.
	/// @return A constant reference to the std::string containing the IPv4
	/// address.
	const std::string&	getIPAddress() const;

	/// @brief Accessor for the outputBuffer_ attribute.
	/// @return A reference to the output buffer.
	std::string&		getOutputBuffer();

	/// @brief Accessor for the sockFD_ attribute.
	/// @return Returns the value of sockFD_.
	int					getSockFD() const;

	/// @brief Assignment operator overload.
	/// @param original The Client object we want to assign from
	/// @return A reference to a Client object.
	Client				&operator=(Client const &original);

	/// @brief Processes the commands inside the Client's inputBuffer_ attribute.
	void				processInput();

	/// @brief Fills the client's output buffer with 'length' characters of
	/// string 'str'.
	/// @param buffer The data we want to fill the client's output buffer with.
	/// @param maxLength The maximum number of characters we want to put inside
	/// the client's output buffer.
	/// @return Returns the number of bytes written.
	int					setOutputBuffer(char* buffer, unsigned int maxLength);

	/// @brief Setter for the sockFD_ attribute.
	/// @param fd The file descriptor that will be associated with the current
	/// Client object.
	void				setSockFD(int fd);

  private:
	int			sockFD_;		///< Socket file descriptor, -1 if not set.
	UNUSED t_conState	connectionState;	///< Connection state
	UNUSED t_authState	authState;	///< Authentication status
	std::string	nick_;			///< Nickname.
	std::string	name_;			///< Username.
	std::string	host_;			///< Hostname.
	std::string	ipAddress_;		///< IPv4 address of the client.
	std::string	inputBuffer_;	///< Input buffer.
	std::string	outputBuffer_;	///< Output buffer.
	//and current channels. todo! --> ?shared pointer?
	//	- maybe a secondary list for chanels he has mod power into?
};

#undef UNUSED
