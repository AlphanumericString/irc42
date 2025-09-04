/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IError.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoulard <bgoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 13:43:13 by bgoulard          #+#    #+#             */
/*   Updated: 2025/08/15 13:43:13 by bgoulard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <exception>
#include <string>

#include "IRPL.hpp"

class IError : public IRPL, public std::exception {
  public:
	IError(int e_code, const std::string &s)
		: IRPL(e_code, s), std::exception() {
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
		if (_s.find(":") == std::string::npos)
			_s = " :" + _s;
		else if (_s[0] != ' ')
			ret += " ";
		ret += _s + "\n";
		return (ret);
	}

  protected:
	std::string _s;
	int			_c;
};
#include "IError_populated.hpp"

// class ERR_NEEDMOREPARAMS : public IError {
//   public:
// 	ERR_NEEDMOREPARAMS(const std::string &cmd)
// 		: IError(461, "Not enough parameters") {
// 		_s = cmd + " :" + _s;
// 	};
// 	virtual ~ERR_NEEDMOREPARAMS(void) throw() {};
// };
//
// class ERR_ALREADYREGISTERED : {
//   public:
// 	ERR_ALREADYREGISTRED() : IError(462, "You may not reregister") {};
// 	virtual ~ERR_ALREADYREGISTRED(void) throw() {};
// };
//
// class ERR_PASSWDMISMATCH : public IError {
//   public:
// 	ERR_PASSWDMISMATCH() : IError(464, "Password incorect") {};
// 	virtual ~ERR_PASSWDMISMATCH(void) throw() {};
// };
//
// class ERR_NONICKNAMEGIVEN : public IError {
//   public:
// 	ERR_NONICKNAMEGIVEN() : IError(431, "No nickname given") {};
// 	virtual ~ERR_NONICKNAMEGIVEN(void) throw() {};
// };
//
// class ERR_ERRONEUSNICKNAME : public IError {
//   public:
// 	ERR_ERRONEUSNICKNAME(const std::string &nick)
// 		: IError(432, "Erroneus nickname") {
// 		_s = nick + " :" + _s;
// 	};
// 	virtual ~ERR_ERRONEUSNICKNAME() throw() {};
// };
//
// class ERR_NICKNAMEINUSE : public IError {
//   public:
// 	ERR_NICKNAMEINUSE(const std::string &nick)
// 		: IError(432, "Nickname is already in use") {
// 		_s = nick + " :" + _s;
// 	};
// 	virtual ~ERR_NICKNAMEINUSE() throw() {};
// };
//
// class ERR_UNKNOWNCOMMAND : public IError {
//   public:
// 	ERR_UNKNOWNCOMMAND(const std::string &cmd)
// 		: IError(421, "Unknown command") {
// 		_s = " * " + cmd + " :" + _s;
// 	};
// 	virtual ~ERR_UNKNOWNCOMMAND() throw() {};
// };

