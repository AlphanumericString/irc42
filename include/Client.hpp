/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoulard <bgoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 12:58:32 by bgoulard          #+#    #+#             */
/*   Updated: 2025/08/06 12:36:24 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include "AuthState.hpp"
#include "ConectionState.hpp"

#define UNUSED __attribute__((unused))

/// @class Client
/// @brief Class representing a single client.
class Client {
  public:
	/// @brief
	Client();

	/// @brief
	/// @param fd The file descriptor associated to the client.
	Client(int fd);

	/// @brief
	/// @param original
	Client(Client const &original); // when are we gonna use this ?!

	/// @brief
	~Client();

	/// @brief
	/// @param original
	/// @return
	Client &operator=(Client const &original);

	/// @brief Erase 'length' characters of the output buffer.
	/// @param length The number of characters to erase.
	void	advanceOutputBuffer(unsigned int length);

	/// @brief Appends 'length' char of string 'str' to the client's input
	/// buffer.
	/// @param str The content we want to append to the clien't input buffer.
	/// @length The number of characters we want to append.
	void	appendInputBuffer(char* str, int length);

	/// @brief
	/// @return A reference to the output buffer.
	std::string& getOutputBuffer();

	/// @brief Accessor for the sockFD_ attribute.
	/// @return Returns the value of sockFD_.
	int		getSockFD();

	/// @brief
	void	processInput();

	/// @brief Fills the client's output buffer with 'length' characters of
	/// string 'str'.
	/// @str The data we want to fill the client's output buffer with.
	/// @length The maximum number of characters we want to put inside the
	/// client's output buffer.
	/// @return Returns the number of bytes written.
	int	setOutputBuffer(char* str, int length);

	/// @brief
	/// @param fd
	void	setSockFD(int fd);

  private:
	int			sockFD_;		///< Socket file descriptor, -1 if not set.
	UNUSED t_conState	connectionState;	///< Connection state
	UNUSED t_authState	authState;	///< Authentication status
	std::string	nick_;			///< Nickname.
	std::string	name_;			///< Username.
	std::string	host_;			///< Hostname.
	std::string	inputBuffer_;	///< Input buffer.
	std::string	outputBuffer_;	///< Output buffer.
	//and current channels. todo! --> ?shared pointer?
	//	- maybe a secondary list for chanels he has mod power into?
};

#undef UNUSED
