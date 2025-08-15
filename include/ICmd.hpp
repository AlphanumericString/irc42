/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ISendable.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoulard <bgoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 01:35:46 by bgoulard          #+#    #+#             */
/*   Updated: 2025/08/14 01:35:46 by bgoulard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <vector>

#include "Client.hpp"
#include "IRPL.hpp"
#include "Server.hpp"
#include "generics.hpp"

class ICmd {
  public:
	ICmd(const std::string &raw) {
		_raw = raw;
		_args = split(_raw, " ");
		_response.clear();
	};
	virtual ~ICmd(void) {};

	virtual std::vector< IRPL > execute(Server &s, Client &c) = 0;

  protected:
	std::string				   _response;
	std::vector< std::string > _args;
	std::string				   _raw;
};

class CMD_PASS : public ICmd {
  private:
	static const int minArg = 2;

  public:
	CMD_PASS(const std::string &s) : ICmd(s) {}
	virtual std::vector< IRPL > execute(Server &s, Client &clien_requesting);
	static const std::string	predicate() {
		   return std::string("PASS");
	}
};

class CMD_NICK : public ICmd {
  private:
	static const int minArg = 2;

  public:
	CMD_NICK(const std::string &s) : ICmd(s) {}
	virtual std::vector< IRPL > execute(Server &s, Client &clien_requesting);
	static const std::string	predicate() {
		   return std::string("NICK");
	}
};

class CMD_USER : public ICmd {
  private:
	static const int minArgs = 5;

  public:
	CMD_USER(const std::string &s) : ICmd(s) {}
	virtual std::vector< IRPL > execute(Server &s, Client &clien_requesting);
	static const std::string	predicate() {
		   return std::string("USER");
	}
};
