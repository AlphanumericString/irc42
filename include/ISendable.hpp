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

#include <exception>
#include <iomanip>
#include <string>
#include <vector>

#include "Client.hpp"
#include "ConnectionState.hpp"
#include "Server.hpp"
#include "generics.hpp"

#pragma once

class ISendable {
  public:
	ISendable(void) {};
	virtual ~ISendable() {};
	virtual std::string toString(const Server &s, const Client &c) = 0;
};

class IError : public ISendable, public std::exception {
  public:
	IError(int e_code, const std::string &s) : ISendable(), std::exception() {
		_s = s;
		_c = e_code;
	};
	virtual ~IError() throw() {};

	virtual const char *what(void) const throw() {
		return _s.c_str();
	}
	virtual std::string toString(const Server &s, const Client &c) {
		char		buff[4] = {0};
		std::string ret;

		buff[0] = '0' + (_c / 100);
		buff[1] = '0' + (_c % 100) / 10;
		buff[2] = '0' + (_c % 10);

		ret =
			":" + s.getServerState().getName() + " " + buff + " " + c.getNick();
		if (_s.find(':') !=
			std::string::npos) // if you had no argument pushed after err code
			ret += " :";
		ret += _s + "\n";
		return (ret);
	}

  protected:
	std::string _s;
	int			_c;
};

class ERR_NEEDMOREPARAM : public IError {
  public:
	ERR_NEEDMOREPARAM(const std::string &cmd)
		: IError(461, "Not enough parameters") {
		_s = cmd + " :" + _s;
	};
	virtual ~ERR_NEEDMOREPARAM(void) throw() {};
};

class ERR_ALREADYREGISTRED : public IError {
  public:
	ERR_ALREADYREGISTRED() : IError(462, "You may not reregister") {};
	virtual ~ERR_ALREADYREGISTRED(void) throw() {};
};

class ERR_PASSWDMISMATCH : public IError {
  public:
	ERR_PASSWDMISMATCH() : IError(464, "Password incorect") {};
	virtual ~ERR_PASSWDMISMATCH(void) throw() {};
};

class ERR_NONICKNAMEGIVEN : public IError {
  public:
	ERR_NONICKNAMEGIVEN() : IError(431, "No nickname given") {};
	virtual ~ERR_NONICKNAMEGIVEN(void) throw() {};
};

class ERR_ERRONEUSNICKNAME : public IError {
  public:
	ERR_ERRONEUSNICKNAME(const std::string &nick)
		: IError(432, "Erroneus nickname") {
		_s = nick + " :" + _s;
	};
	virtual ~ERR_ERRONEUSNICKNAME() throw() {};
};

class ERR_NICKNAMEINUSE : public IError {
  public:
	ERR_NICKNAMEINUSE(const std::string &nick)
		: IError(432, "Nickname is already in use") {
		_s = nick + " :" + _s;
	};
	virtual ~ERR_NICKNAMEINUSE() throw() {};
};

class ERR_UNKNOWNCOMMAND : public IError {
  public:
	ERR_UNKNOWNCOMMAND(const std::string &cmd)
		: IError(421, "Unknown command") {
		_s = cmd + " :" + _s;
	};
	virtual ~ERR_UNKNOWNCOMMAND() throw() {};
};

class ICommand : public ISendable {
  public:
	ICommand(const std::string &raw) : ISendable() {
		_raw = raw;
		_args = split(_raw, " ");
	};

	virtual ~ICommand(void) {};
	virtual std::string toString(const Server &s, const Client &c) {
		(void)s;
		(void)c;
		return _response;
	}

	virtual void execute(Server &s,
						 Client &clien_requesting) throw(IError *) = 0;

  protected:
	std::string				   _response;
	std::vector< std::string > _args;
	std::string				   _raw;
};

class CMD_PASS : public ICommand {
  private:
	static const int minArg = 2;

  public:
	CMD_PASS(const std::string &s) : ICommand(s) {}
	virtual void execute(Server &s, Client &clien_requesting) throw(IError *) {
		if (_args.size() < CMD_PASS::minArg)
			throw(new ERR_NEEDMOREPARAM(_args[0]));
		else if (clien_requesting.getConState() != REGISTERING)
			throw(new ERR_ALREADYREGISTRED());
		else if (s.getServerState().getPassword().compare(_args[1]) != 0)
			throw(new ERR_PASSWDMISMATCH());
		return;
	}
	static const std::string predicate() {
		return std::string("PASS");
	}
};

class CMD_NICK : public ICommand {
  private:
	static const int minArg = 2;

  public:
	CMD_NICK(const std::string &s) : ICommand(s) {}
	virtual void execute(Server &s, Client &clien_requesting) throw(IError *) {
		if (_args.size() < CMD_NICK::minArg)
			throw(new ERR_NONICKNAMEGIVEN());
		if (_args[1].length() > 200 ||
			_args[1].find_first_not_of(ALNUM) != std::string::npos ||
			_args[1].length() < 9)
			throw(new ERR_ERRONEUSNICKNAME(_args[1]));
		for (std::list< Client >::const_iterator it =
				 s.getServerState().getClients().begin();
			 it != s.getServerState().getClients().end(); it++)
			if (it->getNick().compare(_args[1]) != 0)
				throw(new ERR_NICKNAMEINUSE(_args[1]));
		try {
			clien_requesting.setNickname(_args[1]);
		} catch (...) {
			throw(new ERR_ERRONEUSNICKNAME(_args[1]));
		}
		// @TODO:
		//  multi-server setup require to transmit nick to followupservers
		//  and call ERR_NICKCOLISION if nick is already present in other server
		//  theres somthing abou a command kill bu i didnt get it @ 3am lol
	};
	static const std::string predicate() {
		return std::string("NICK");
	}
};

class CMD_USER : public ICommand {
  private:
	static const int minArgs = 5;

  public:
	CMD_USER(const std::string &s) : ICommand(s) {}
	virtual void execute(Server &s, Client &clien_requesting) throw(IError *) {
		std::string _real_name;
		if (clien_requesting.getConState() != REGISTERING)
			throw(new ERR_ALREADYREGISTRED());
		if (_raw.find_last_of(":") == std::string::npos ||
			_args.size() < CMD_USER::minArgs)
			throw(new ERR_NEEDMOREPARAM(_args[0]));
		_real_name = _raw.substr(_raw.find_last_of(":"));
		clien_requesting.setName(_args[1]);
		clien_requesting.setHost(_args[2]);
		clien_requesting.setRealname(_real_name);

		(void)s;
		// _response = ":Welcome to the Internet Relay Network " +
		// 			clien_requesting.getNick() + "!" +
		// 			clien_requesting.getUserName() + "@" +
		// 			clien_requesting.getHost() + "\r\n";
		// _response += ":Your host is "
	}
	static const std::string predicate() {
		return std::string("USER");
	}
};
