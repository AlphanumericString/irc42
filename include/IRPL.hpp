/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRPL.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoulard <bgoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 13:41:54 by bgoulard          #+#    #+#             */
/*   Updated: 2025/08/15 13:41:54 by bgoulard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <sstream>
#include <stdexcept>
#include <string>

#include "Client.hpp"
#include "Server.hpp"

class IRPL {
  public:
	IRPL(int code, std::string desc) : _code(code), string(desc) {
		if (_code < 0 || _code > 999)
			throw std::invalid_argument("IRPL code must be between 0 and 999");
		if (string.empty())
			throw std::invalid_argument("IRPL description cannot be empty");
	}
	IRPL(const IRPL &other) : _code(other._code), string(other.string) {};
	IRPL &operator=(const IRPL &other) {
		if (this != &other) {
			_code = other._code;
			string = other.string;
		}
		return *this;
	}
	virtual ~IRPL() {};
	virtual std::string toString(const Server &s, const Client &c);

  protected:
	int			_code;
	std::string string;
};

class RPL_CUSTOM : public IRPL {
  public:
	RPL_CUSTOM(const std::string &desc) : IRPL(000, desc) {};
	virtual ~RPL_CUSTOM(void) {};
	virtual std::string toString(const Server &s, const Client &c) {
		(void)c;
		std::stringstream ss;

		ss << ":" << s.getServerState().getName() << " ";
		ss << string << "\r\n";
		return ss.str();
	};
};

class RPL_FULLCUSTOM : public IRPL {
  public:
	RPL_FULLCUSTOM(const std::string &str) : IRPL(000, str) {};
	RPL_FULLCUSTOM(const RPL_FULLCUSTOM &other) : IRPL(other) {};
	virtual ~RPL_FULLCUSTOM(void) {};
	virtual std::string toString(const Server &s, const Client &c) {
		(void)c;
		(void)s;
		return IRPL::string;
	};
};


class RPL_JOIN : public IRPL {
  public:
	// nick!user@host JOIN #channel
	// nick -> nickname; user -> username; host -> hostname
	// channel -> channel name
	RPL_JOIN(const std::string &info_client, const std::string &ch_name);
	virtual ~RPL_JOIN(void);
	virtual std::string toString(const Server &s, const Client &c);
};

#include "IRPL_populated.hpp"
