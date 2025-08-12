/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoulard <bgoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:49:12 by bgoulard          #+#    #+#             */
/*   Updated: 2025/08/11 16:57:53 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
/// @file Message.hpp
/// @brief
// there are no 'normal' message any message sent in chat rooms are technically
// PRIVMSG to #chat
// this class will be a tokenizer to TMessage (Tokenized Message)

#include <string>

#include "Server.hpp"
#include "smart_ptr.hpp"

class Message {
  private:
	typedef int (*t_handler)(Server &);

  public:
	typedef enum {
		// connection de-connections
		CAP, // maybe sub cmd CAP LS, CAP REQ, CAP LIST, CAP END ?
		QUIT,

		// user centered
		USER,
		NICK,

		// chanel co-deco
		JOIN,
		PART,

		// talks
		PRIVMSG,

		// inquiries
		PING,
		PONG,
		WHO,
		NAMES,
		LIST,
		VERSION,

		// operator only
		KICK,
		INVITE,
		MODE,
		TOPIC,

		UNKNOWN // error
	} t_command;

	Message(std::string &str);
	Message(const Message &);
	Message &operator=(const Message &);
	~Message();

	// returns function pointer to handler
	// int	(Message::*getHandler())(Server &) const;
	t_handler		   getHandler() const;
	const std::string &getRaw() const;
	t_command		   getCommand() const;

	static t_handler strToHandler(const std::string &s);
	static t_command strToCommand(const std::string &s);

  private:
	static int unknown_handl(Server &s);

	static const std::pair< t_command, t_handler >	 table[];
	static const std::pair< t_command, std::string > table_str[];
	// yes im too lazy to struct it
	// and 2 - it'll only be used in this class
	// the other table might be exported or the type might be made public
	// with strToHandle being public and strToCommand being public
	// might be typedef-ed

	t_command	_command;
	t_handler	_handler;
	std::string _raw;
	// dogshit language. cnat init here. Need to be done @ the impl file...
	// tldr of table:
	//  std::make_pair(JOIN, join_handl);
	//  ...
	//	std::make_pair(UNKNOWN, unknown_handl);
};
