/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoulard <bgoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 12:58:32 by bgoulard          #+#    #+#             */
/*   Updated: 2025/07/07 12:58:32 by bgoulard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include "AuthState.hpp"
#include "ConectionState.hpp"

#define UNUSED __attribute__((unused))

class Client {
  private:
	UNUSED int sock_fd;	//socket file descriptor,
	UNUSED t_conState connectionState;	//connection state,
	UNUSED t_authState authState;	//authentication status,
	UNUSED std::string	nick;	//nickname,
	UNUSED std::string name;	//username,
	UNUSED std::string	host;	//hostname,
	//and current channels. todo! --> ?shared pointer?
	//	- maybe a secondary list for chanels he has mod power into?

  public:
	// Constructors
	Client();
	Client(Client const &original); // when are we gonna use this ?!
	// Destructors
	~Client();
	// Operator overloads
	Client &operator=(Client const &original);
	// Getters
	// Setters
	// Member functions
	// Exceptions
};

#undef UNUSED
