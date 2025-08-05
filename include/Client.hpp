/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoulard <bgoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 12:58:32 by bgoulard          #+#    #+#             */
/*   Updated: 2025/08/05 17:23:05 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include "AuthState.hpp"
#include "ConectionState.hpp"

#define UNUSED __attribute__((unused))

/// @class Client
/// @brief
class Client {
  public:
	/// @brief
	Client();
	Client(Client const &original); // when are we gonna use this ?!
	~Client();
	Client &operator=(Client const &original);

	/// @brief Erase length characters of the output buffer.
	/// @param length The number of characters to erase.
	void	advanceOutputBuffer(int length);

	/// @brief
	/// @param buffer
	/// @length
	void	appendInputBuffer(char* buffer, int length);

	/// @brief
	/// @return A reference to the output buffer.
	std::string& getOutputBuffer();

	/// @brief
	/// @return
	int		getSockFD();

	void	processInput();

	/// @brief
	/// @param str
	/// @return
	int	setOutputBuffer(char* str);

	/// @brief
	/// @str
	/// @length
	/// @return
	int	setOutputBuffer(char* str, int length);

	/// @brief
	/// @param fd
	void	setSockFD(int fd);

  private:
	int			sockFD_;	///< Socket file descriptor, -1 if not set.
	UNUSED t_conState	connectionState;	///< Connection state
	UNUSED t_authState	authState;	///< Authentication status
	UNUSED std::string	nick;	///< Nickname
	UNUSED std::string	name;	///< Username
	UNUSED std::string	host;	///< Hostname
	std::string	inputBuffer_;
	std::string	outputBuffer_;
	//and current channels. todo! --> ?shared pointer?
	//	- maybe a secondary list for chanels he has mod power into?
};

#undef UNUSED
