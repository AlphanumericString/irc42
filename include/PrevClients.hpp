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
#include <string>

#include "Client.hpp"

class PrevClients {
  public:
	PrevClients(Client const &c)
		: _nick(c.getNick()), _username(c.getUserName()),
		  _hostname(c.getHost()), _realname(c.getRealName()),
		  _disconnectionTime(std::time(NULL)) {}

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
	bool operator!=(const PrevClients &other) const {
		return (this->_nick != other._nick);
	}
	bool operator==(const std::string &nick) const {
		return (this->_nick == nick);
	}
	bool operator!=(const std::string &nick) const {
		return (this->_nick == nick);
	}
	PrevClients &operator=(PrevClients const &original) {
		if (this != &original) {
			this->_nick = original._nick;
			this->_username = original._username;
			this->_hostname = original._hostname;
			this->_realname = original._realname;
			this->_disconnectionTime = original._disconnectionTime;
		}
		return (*this);
	}

	// flemme de faire des getters pour des truc consts
	std::string _nick;
	std::string _username;
	std::string _hostname;
	std::string _realname;
	std::time_t	_disconnectionTime;
};
