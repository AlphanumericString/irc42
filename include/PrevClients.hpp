/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrevClients.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoulard <bgoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 20:42:04 by bgoulard          #+#    #+#             */
/*   Updated: 2025/09/04 20:42:04 by bgoulard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <ctime>
#include <iostream>
#include <string>

#include "Client.hpp"

class PrevClients {
  public:
	PrevClients(Client const &c)
		: _nick(c.getNick()), _username(c.getUserName()),
		  _hostname(c.getHost()), _realname(c.getRealName()),
		  _disconnectionTime(clock()) {}

	PrevClients(const std::string &nick, const std::string &username,
				const std::string &hostname, const std::string &realname)
		: _nick(nick), _username(username), _hostname(hostname),
		  _realname(realname), _disconnectionTime(clock()) {}
	PrevClients(PrevClients const &original)
		: _nick(original._nick), _username(original._username),
		  _hostname(original._hostname), _realname(original._realname),
		  _disconnectionTime(original._disconnectionTime) {}
	~PrevClients() {};

	bool operator==(const PrevClients &other) const {
		return (this->_nick == other._nick);
	}
	bool operator==(const std::string &nick) const {
		return (this->_nick == nick);
	}

	// flemme de faire des getters pour des truc consts
	const std::string _nick;
	const std::string _username;
	const std::string _hostname;
	const std::string _realname;
	const clock_t	  _disconnectionTime;
};
