/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoulard <bgoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 12:58:52 by bgoulard          #+#    #+#             */
/*   Updated: 2025/08/12 15:20:33 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/// @file Channel.hpp
/// @brief
///
/// A channel is a named group of one or more clients which will all receive
/// messages addressed to that channel. The channel is created implicitly when
/// the first client joins it, and the channel ceases to exist when the last
/// client leaves it. While channel exists, any client can reference the channel
/// using the name of the channel.
///
/// Channels are created when a user uses the `JOIN` command on a not-already
/// existing channel.

#pragma once

#include <exception>
#include <list>
#include <ostream>
#include <string>

class Client;
class Server;

#define MAX_CHAN_NAME_LEN 200
#define PREFIX_CHARS	  "#&"
#define DEFAULT_PREFIX	  PREFIX_CHARS[0]
#define UNUSED			  __attribute__((unused))

typedef enum {		  // need to read doc, make these more explicit
	MODE_UNKNOWN = 0, ///< Unknown mode (default).
	MODE_L = 1 << 0,  ///< User limit for the channel.
	MODE_T = 1 << 1,  ///< Channel topic.
	MODE_I = 1 << 2,  ///< Invite-only channel.
	MODE_K = 1 << 4,  ///< Password-protected channel.
	MODE_O = 1 << 5,  ///< Channel operator status.
	MODE_DEFAULT = MODE_UNKNOWN,
	MODE_NUMBER = 6
} ChanMod;

void	operator|=(ChanMod &a, ChanMod b);
ChanMod operator|(const ChanMod a, const ChanMod b);
ChanMod operator&(const ChanMod a, const ChanMod b);

std::ostream &operator<<(std::ostream &os, ChanMod m);

class Channel {
  public:
	Channel(std::string const &name, Client &creator);
	Channel(Channel const &original);
	~Channel();
	Channel &operator=(Channel const &original);

	// broadcast message to all members except the origin
	void broadcast_full(const std::string &s, Server &ser);
	void broadcast(const std::string &s, const Client &c, Server &ser);
	void updateNick(const Client &c, const std::string &newNick, Server &ser);

	// [checks]
	bool isFull() const;
	bool isEmpty() const;
	bool operator==(Channel const &other) const;
	bool operator==(std::string const &name) const;

	// [members] {has, add, remove, get}
	bool					   hasMember(const Client &client) const;
	void					   addMember(Client &client);
	void					   removeMember(const Client &client);
	std::list< Client >		  &getMembers();
	const std::list< Client > &getMembers() const;
	const Client			  &getMember(const std::string &nick) const;
	Client					  &getMember(const std::string &nick);
	const Client			  &getMember(const Client &c) const;
	Client					  &getMember(const Client &c);

	// [operators] {is, add, remove, get}
	bool					   isOperator(const Client &client) const;
	void					   addOperator(Client &client);
	void					   removeOperator(const Client &client);
	std::list< Client >		  &getOperators();
	const std::list< Client > &getOperators() const;
	Client					  &getOperator(const std::string &nick);
	const Client			  &getOperator(const std::string &nick) const;

	// [invites] {is, add, remove, get}
	bool					   isInvited(const Client &client) const;
	void					   addInvite(const Client &client);
	void					   removeInvite(const Client &client);
	std::list< Client >		  &getInvited();
	const std::list< Client > &getInvited() const;
	Client					  &getInvited(const std::string &nick);
	const Client			  &getInvited(const std::string &nick) const;

	// get/set
	// [name]
	void			   setName(const std::string &t);
	std::string const &getName() const;

	// [topic]
	void			   setTopic(const std::string &t);
	std::string const &getTopic() const;

	// [mode-stuff] {user limit, mode, key}
	//
	std::string getModeStrFormat(std::string *mode_params) const;
	int			getUserLimit() const;
	void		setUserLimit(int limit);

	ChanMod getMode() const;
	void	setMode(ChanMod m);
	void	unsetMode(const ChanMod m);

	const std::string &getKey() const;
	void			   setKey(const std::string &k);

  private:
	Channel();

	std::list< Client > operators_;
	std::list< Client > invited_;
	std::list< Client > members_;

	std::string name_;
	std::string topic_;
	std::string key_;

	int userLimit_;

	ChanMod mode_;
};

#undef UNUSED
