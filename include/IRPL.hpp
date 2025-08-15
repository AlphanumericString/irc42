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

class RPL_WELCOME : public IRPL {
  public:
	RPL_WELCOME(const std::string &nick, const std::string &c_hostname);
	virtual ~RPL_WELCOME(void);
};

class RPL_YOURHOST : public IRPL {
  public:
	RPL_YOURHOST();
	virtual ~RPL_YOURHOST(void);
};

class RPL_CREATED : public IRPL {
  public:
	RPL_CREATED();
	virtual ~RPL_CREATED(void);
};
