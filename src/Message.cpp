/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoulard <bgoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 10:55:03 by bgoulard          #+#    #+#             */
/*   Updated: 2025/07/09 10:55:03 by bgoulard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Message.hpp"

#include <cstddef>
#include <sstream>
#include <string>

#include "Server.hpp"
#include "generics.hpp"

#define UNUSED __attribute__((unused))
const std::pair< Message::t_command, Message::t_handler > Message::table[] = {
	std::make_pair(Message::UNKNOWN, unknown_handl), // keep last
};
const std::pair< Message::t_command, std::string > Message::table_str[] = {
	std::make_pair(Message::CAP, std::string("CAP")),
	std::make_pair(Message::QUIT, std::string("QUIT")),
	std::make_pair(Message::USER, std::string("USER")),
	std::make_pair(Message::NICK, std::string("NICK")),
	std::make_pair(Message::JOIN, std::string("JOIN")),
	std::make_pair(Message::PART, std::string("PART")),
	std::make_pair(Message::PRIVMSG, std::string("PRIVMSG")),
	std::make_pair(Message::PING, std::string("PING")),
	std::make_pair(Message::PONG, std::string("PONG")),
	std::make_pair(Message::WHO, std::string("WHO")),
	std::make_pair(Message::NAMES, std::string("NAMES")),
	std::make_pair(Message::LIST, std::string("LIST")),
	std::make_pair(Message::VERSION, std::string("VERSION")),
	std::make_pair(Message::KICK, std::string("KICK")),
	std::make_pair(Message::INVITE, std::string("INVITE")),
	std::make_pair(Message::MODE, std::string("MODE")),
	std::make_pair(Message::TOPIC, std::string("TOPIC")),
	std::make_pair(Message::UNKNOWN, std::string("UNKNOWN")),
};

int Message::unknown_handl(Server &s) {
	(void)s;
	return (0);
}

Message::t_handler Message::getHandler() const {
	return _handler;
};
Message::t_command Message::getCommand() const {
	return _command;
};
const std::string &Message::getRaw() const {
	return _raw;
};

Message::t_handler Message::strToHandler(const std::string &s) {
	std::stringstream  ss(s);
	std::size_t		   i;
	Message::t_command cmd;

	cmd = strToCommand(s);
	if (cmd == Message::UNKNOWN)
		return ((Message::t_handler)&Message::unknown_handl);
	for (i = 0; i < CTAB_SIZE(table); i++)
		if (table[i].first == cmd)
			return (table[i].second);
	return ((Message::t_handler)&Message::unknown_handl);
}

Message::t_command Message::strToCommand(const std::string &s) {
	std::string		  cmd;
	std::stringstream ss(s);
	std::size_t		  i;

	if (!std::getline(ss, cmd, ' '))
		return (Message::UNKNOWN);
	for (i = 0; i < CTAB_SIZE(table_str); i++)
		if (table_str[i].second.compare(cmd) == 0)
			return (table_str[i].first);
	return (Message::UNKNOWN);
}

Message::Message(std::string &str) {
	size_t i;
	_command = strToCommand(str);
	for (i = 0; i < CTAB_SIZE(table); i++)
		if (table[i].first == Message::UNKNOWN || table[i].first == _command)
			break;
	_handler = table[i].second;
	_raw = str;
}

Message::Message(const Message &other) {
	_handler = other.getHandler();
	_command = other.getCommand();
	_raw = other.getRaw();
}

Message &Message::operator=(UNUSED const Message &other) {
	// kinda cool right ?
	// since you can override the '&'
	// you can call addressof to be sure to get an address
	if (this != std::__addressof(other))
		*this = other;
	return (*this);
};

Message::~Message() {}
