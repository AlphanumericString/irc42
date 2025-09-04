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
#include "IError_populated.hpp"
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

	virtual std::vector< IRPL * > execute(Server &s, Client &c) = 0;

  protected:
	std::string				   _response;
	std::vector< std::string > _args;
	std::string				   _raw;
};

// Connection core : [PASS, USER, CAP, QUIT, NICK]
// nick grouped in here as req for registration, howerver last bc can be used
// outside of it.

class CMD_PASS : public ICmd {
  private:
	static const int minArg = 2;

  public:
	CMD_PASS(const std::string &s) : ICmd(s) {}
	virtual std::vector< IRPL * > execute(Server &s, Client &client_requesting);
	static const std::string	  predicate() {
		 return std::string("PASS");
	}
};

class CMD_USER : public ICmd {
  private:
	static const int minArgs = 5;

  public:
	CMD_USER(const std::string &s) : ICmd(s) {}
	virtual std::vector< IRPL * > execute(Server &s, Client &client_requesting);
	static const std::string	  predicate() {
		 return std::string("USER");
	}
};

class CMD_CAP : public ICmd {
  private:
	static const int minArg = 2;

  public:
	CMD_CAP(const std::string &s) : ICmd(s) {}
	virtual std::vector< IRPL * > execute(Server &s, Client &client_requesting);
	static const std::string	  predicate() {
		 return std::string("CAP");
	}
};

class CMD_QUIT : public ICmd {
  public:
	CMD_QUIT(const std::string &s) : ICmd(s) {}
	virtual std::vector< IRPL * > execute(Server &s, Client &client_requesting);
	static const std::string	  predicate() {
		 return std::string("QUIT");
	}
};

// [ NICK ]
class CMD_NICK : public ICmd {
  private:
	static const int minArg = 2;

  public:
	CMD_NICK(const std::string &s) : ICmd(s) {}
	virtual std::vector< IRPL * > execute(Server &s, Client &client_requesting);
	static const std::string	  predicate() {
		 return std::string("NICK");
	}
};

// msg core : [JOIN, PART, PRIVMSG]
// TODO: [NOTICE, AWAY]

class CMD_JOIN : public ICmd {
  private:
	static const int minArg = 2;

  public:
	// FIX:
	// JOIN [add-checks]-> invite only, key, limit
	CMD_JOIN(const std::string &s) : ICmd(s) {}
	virtual std::vector< IRPL * > execute(Server &s, Client &client_requesting);
	static const std::string	  predicate() {
		 return std::string("JOIN");
	}
};

class CMD_PRIVMSG : public ICmd {
  private:
	static const int minArg = 3;

  public:
	CMD_PRIVMSG(const std::string &s) : ICmd(s) {}
	virtual std::vector< IRPL * > execute(Server &s, Client &client_requesting);
	static const std::string	  predicate() {
		 return std::string("PRIVMSG");
	}
};

class CMD_PART : public ICmd {
  private:
	static const int minArg = 2;

  public:
	CMD_PART(const std::string &s) : ICmd(s) {}
	virtual std::vector< IRPL * > execute(Server &s, Client &client_requesting);
	static const std::string	  predicate() {
		 return std::string("PART");
	}
};

// ------------
// INFO core : [whois, whowas, ping, version]
// -----------

// no 'WHO' command. Im NOT manually implementing regexes

// FIX:
// fix whois - some replies missing +
//	mixup on some stuff atm.
//  1 - seems like it replies server info even if target matches a client nick
//		i think its supposed to be exclusive, like check if it matches a client,
//		check if it matches a channel, etc ... but at the moment it seems to
//		reply everything that matches for every category.
//	2 - Also idle time seems broken, always 2 hours and some change.
//	3 - Away status missing, if we do it we need to go all the way.
class CMD_WHOIS : public ICmd {
  private:
	static const int minArg = 2;

  public:
	CMD_WHOIS(const std::string &s) : ICmd(s) {}
	virtual std::vector< IRPL * > execute(Server &s, Client &client_requesting);
	static const std::string	  predicate() {
		 return std::string("WHOIS");
	}
};

class CMD_WHOWAS : public ICmd {
  private:
	static const int minArg = 2;

  public:
	CMD_WHOWAS(const std::string &s) : ICmd(s) {}
	virtual std::vector< IRPL * > execute(Server &s, Client &client_requesting);
	static const std::string	  predicate() {
		 return std::string("WHOWAS");
	}
};

class CMD_PING : public ICmd {
  public:
	CMD_PING(const std::string &s) : ICmd(s) {};
	virtual std::vector< IRPL * > execute(Server &s, Client &client_requesting);
	static const std::string	  predicate() {
		 return std::string("PING");
	}
};

class CMD_VERSION : public ICmd {
  public:
	CMD_VERSION(const std::string &s) : ICmd(s) {};
	virtual std::vector< IRPL * > execute(Server &s, Client &client_requesting);
	static const std::string predicate() {
		return std::string("version");
	}
};

// ------------
// OPERATOR core : [KICK, INVITE, TOPIC, MODE]
// ------------
// [KICK] - remove user from channel
class CMD_KICK : public ICmd {
  private:
	static const int minArg = 3;

  public:
	CMD_KICK(const std::string &s) : ICmd(s) {}
	virtual std::vector< IRPL * > execute(Server &s, Client &client_requesting);
	static const std::string	  predicate() {
		 return std::string("KICK");
	}
};

// [INVITE] - invite user to channel
// [TOPIC] - set or view topic of channel
// [MODE] not implemented {i, t, k, o, l}
// i-> invite only
// t-> topic set by ops only
// k-> key (password)
// o-> give/take channel operator privilege
// l-> user limit
