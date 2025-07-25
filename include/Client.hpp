/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoulard <bgoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 12:58:32 by bgoulard          #+#    #+#             */
/*   Updated: 2025/07/25 21:25:03 by bgoulard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include "AuthState.hpp"
#include "ConectionState.hpp"

#define UNUSED __attribute__((unused))

class Client {
  public:
	Client();
	Client(Client const &original); // when are we gonna use this ?!
	~Client();
	Client &operator=(Client const &original);

	/// @brief
	/// @return
	int		getSockFD();

	/// @brief
	/// @param
	void	setSockFD(int fd);

  private:
	int			sockFD_;	///< Socket file descriptor
	UNUSED t_conState	connectionState;	///< Connection state
	UNUSED t_authState	authState;	///< Authentication status
	UNUSED std::string	nick;	///< Nickname
	UNUSED std::string	name;	///< Username
	UNUSED std::string	host;	///< Hostname
	//and current channels. todo! --> ?shared pointer?
	//	- maybe a secondary list for chanels he has mod power into?
};

#undef UNUSED
