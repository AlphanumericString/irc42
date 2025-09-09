/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IError_populated.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoulard <bgoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 12:15:28 by bgoulard          #+#    #+#             */
/*   Updated: 2025/08/20 12:15:28 by bgoulard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "IError.hpp"

// nb:401
// short for:ERR_NOSUCHNICK
// desc:RFC1459 	<nick> :<reason> 	Used to indicate the nickname parameter
// supplied to a command is currently unused
class ERR_NOSUCHNICK : public IError {
  public:
	ERR_NOSUCHNICK(const std::string &nick,
				   const std::string &reason = "No such nick");
	virtual ~ERR_NOSUCHNICK(void) throw();
};

// nb:402
// short for:ERR_NOSUCHSERVER
// desc:RFC1459 	<server> :<reason> 	Used to indicate the server name given
// currently doesn't exist
class ERR_NOSUCHSERVER : public IError {
  public:
	ERR_NOSUCHSERVER(const std::string &server,
					 const std::string &reason = "No such server");
	virtual ~ERR_NOSUCHSERVER(void) throw();
};

// nb:403
// short for:ERR_NOSUCHCHANNEL
// desc:RFC1459 	<channel> :<reason> 	Used to indicate the given channel
// name is invalid, or does not exist
class ERR_NOSUCHCHANNEL : public IError {
  public:
	ERR_NOSUCHCHANNEL(const std::string &channel,
					  const std::string &reason = "No such channel");
	virtual ~ERR_NOSUCHCHANNEL(void) throw();
};

// nb:404
// short for:ERR_CANNOTSENDTOCHAN
// desc:RFC1459 	<channel> :<reason> 	Sent to a user who does not have the
// rights to send a message to a channel
class ERR_CANNOTSENDTOCHAN : public IError {
  public:
	ERR_CANNOTSENDTOCHAN(const std::string &channel,
						 const std::string &reason = "Cannot send to channel");
	virtual ~ERR_CANNOTSENDTOCHAN(void) throw();
};

// nb:406
// short for:ERR_WASNOSUCHNICK
// desc:RFC1459 	<nick> :<reason> 	Returned by WHOWAS to indicate there was
// no history information for a given nickname
class ERR_WASNOSUCHNICK : public IError {
  public:
	ERR_WASNOSUCHNICK(const std::string &nick,
					  const std::string &reason = "There was no such nickname");
	virtual ~ERR_WASNOSUCHNICK(void) throw();
};

// nb:409
// short for:ERR_NOORIGIN
// desc:RFC1459 	:<reason> 	PING or PONG message missing the originator
// parameter which is required since these commands must work without valid
// prefixes
class ERR_NOORIGIN : public IError {
  public:
	ERR_NOORIGIN(const std::string &reason = "No origin specified");
	virtual ~ERR_NOORIGIN(void) throw();
};

// nb:412
// short for:ERR_NOTEXTTOSEND
// desc:RFC1459 	:<reason> 	Returned when NOTICE/PRIVMSG is used with no
// message given
class ERR_NOTEXTTOSEND : public IError {
  public:
	ERR_NOTEXTTOSEND(const std::string &reason = "No text to send");
	virtual ~ERR_NOTEXTTOSEND(void) throw();
};

// nb:414
// short for:ERR_WILDTOPLEVEL
// desc:RFC1459 	<mask> :<reason> 	Used when a message is being sent to a
// mask with a wild-card for a top level domain (i.e. *.*)
class ERR_WILDTOPLEVEL : public IError {
  public:
	ERR_WILDTOPLEVEL(const std::string &mask,
					 const std::string &reason = "Wildcard in toplevel domain");
	virtual ~ERR_WILDTOPLEVEL(void) throw();
};

// nb:421
// short for:ERR_UNKNOWNCOMMAND
// desc:RFC1459 	<command> :<reason> 	Returned when the given command is
// unknown to the server (or hidden because of lack of access rights)
class ERR_UNKNOWNCOMMAND : public IError {
  public:
	ERR_UNKNOWNCOMMAND(const std::string &cmd_predicate,
					   const std::string &reason = "Unknown command");
	virtual ~ERR_UNKNOWNCOMMAND(void) throw();
};

// nb:431
// short for:ERR_NONICKNAMEGIVEN
// desc:RFC1459 	:<reason> 	Returned when a nickname parameter expected for
// a command isn't found
class ERR_NONICKNAMEGIVEN : public IError {
  public:
	ERR_NONICKNAMEGIVEN(const std::string &reason = "No nickname given");
	virtual ~ERR_NONICKNAMEGIVEN(void) throw();
};

// nb:432
// short for:ERR_ERRONEUSNICKNAME
// desc:RFC1459 	<nick> :<reason> 	Returned after receiving a NICK message
// which contains a nickname which is considered invalid, such as it's reserved
// ('anonymous') or contains characters considered invalid for nicknames. This
// numeric is misspelt, but remains with this name for historical reasons :)
class ERR_ERRONEUSNICKNAME : public IError {
  public:
	ERR_ERRONEUSNICKNAME(const std::string &nick,
						 const std::string &reason = "Erroneous nickname");
	virtual ~ERR_ERRONEUSNICKNAME(void) throw();
};

// nb:433
// short for:ERR_NICKNAMEINUSE
// desc:RFC1459 	<nick> :<reason> 	Returned by the NICK command when the
// given nickname is already in use
class ERR_NICKNAMEINUSE : public IError {
  public:
	ERR_NICKNAMEINUSE(const std::string &nick,
					  const std::string &reason = "Nickname is already in use");
	virtual ~ERR_NICKNAMEINUSE(void) throw();
};

// nb:441
// short for:ERR_USERNOTINCHANNEL
// desc:RFC1459 	<nick> <channel> :<reason> 	Returned by the server to
// indicate that the target user of the command is not on the given channel
class ERR_USERNOTINCHANNEL : public IError {
  public:
	ERR_USERNOTINCHANNEL(const std::string &nick, const std::string &channel,
						 const std::string &reason = "is not on that channel");
	virtual ~ERR_USERNOTINCHANNEL(void) throw();
};

// nb:442
// short for:ERR_NOTONCHANNEL
// desc:RFC1459 	<channel> :<reason> 	Returned by the server whenever a
// client tries to perform a channel effecting command for which the client is
// not a member
class ERR_NOTONCHANNEL : public IError {
  public:
	ERR_NOTONCHANNEL(const std::string &channel,
					 const std::string &reason = "You're not on that channel");
	virtual ~ERR_NOTONCHANNEL(void) throw();
};

// nb:443
// short for:ERR_USERONCHANNEL
// desc:RFC1459 	<nick> <channel> [:<reason>] 	Returned when a client tries
// to invite a user to a channel they're already on
class ERR_USERONCHANNEL : public IError {
  public:
	ERR_USERONCHANNEL(const std::string &nick, const std::string &channel,
					  const std::string &reason = "is already on channel");
	virtual ~ERR_USERONCHANNEL(void) throw();
};

// nb:451
// short for:ERR_NOTREGISTERED
// desc:RFC1459 	:<reason> 	Returned by the server to indicate that the
// client must be registered before the server will allow it to be parsed in
// detail
class ERR_NOTREGISTERED : public IError {
  public:
	ERR_NOTREGISTERED(const std::string &reason = "You have not registered");
	virtual ~ERR_NOTREGISTERED(void) throw();
};

// nb:461
// short for:ERR_NEEDMOREPARAMS
// desc:RFC1459 	<command> :<reason> 	Returned by the server by any
// command which requires more parameters than the number of parameters given
class ERR_NEEDMOREPARAMS : public IError {
  public:
	ERR_NEEDMOREPARAMS(const std::string &cmd,
					   const std::string &reason = "Not enough parameters");
	virtual ~ERR_NEEDMOREPARAMS(void) throw();
};

// nb:462
// short for:ERR_ALREADYREGISTERED
// desc:RFC1459 	:<reason> 	Returned by the server to any link which
// attempts to register again
class ERR_ALREADYREGISTERED : public IError {
  public:
	ERR_ALREADYREGISTERED(const std::string &reason = "You may not reregister");
	virtual ~ERR_ALREADYREGISTERED(void) throw();
};

// nb:464
// short for:ERR_PASSWDMISMATCH
// desc:RFC1459 	:<reason> 	Returned by the PASS command to indicate the
// given password was required and was either not given or was incorrect
class ERR_PASSWDMISMATCH : public IError {
  public:
	ERR_PASSWDMISMATCH(const std::string &reason = "Password incorrect");
	virtual ~ERR_PASSWDMISMATCH(void) throw();
};

// nb:471
// short for:ERR_CHANNELISFULL
// desc:RFC1459 	<channel> :<reason> 	Returned when attempting to join a
// channel which is set +l and is already full
class ERR_CHANNELISFULL : public IError {
  public:
	ERR_CHANNELISFULL(const std::string &channel,
					  const std::string &reason = "Channel is full");
	virtual ~ERR_CHANNELISFULL(void) throw();
};

// nb:472
// short for:ERR_UNKNOWNMODE
// desc:RFC1459 	<char> :<reason> 	Returned when a given mode is unknown
class ERR_UNKNOWNMODE : public IError {
  public:
	ERR_UNKNOWNMODE(const std::string &mode_char,
					const std::string &reason =
						"is/contain unknown or unsuported mode char");
	virtual ~ERR_UNKNOWNMODE(void) throw();
};

// nb:473
// short for:ERR_INVITEONLYCHAN
// desc:RFC1459 	<channel> :<reason> 	Returned when attempting to join a
// channel which is invite only without an invitation
class ERR_INVITEONLYCHAN : public IError {
  public:
	ERR_INVITEONLYCHAN(const std::string &channel,
					   const std::string &reason = "Cannot join channel (+i)");
	virtual ~ERR_INVITEONLYCHAN(void) throw();
};

// nb:475
// short for:ERR_BADCHANNELKEY
// desc:RFC1459 	<channel> :<reason> 	Returned when attempting to join a
// key-locked channel either without a key or with the wrong key
class ERR_BADCHANNELKEY : public IError {
  public:
	ERR_BADCHANNELKEY(const std::string &channel,
					  const std::string &reason = "Cannot join channel (+k)");
	virtual ~ERR_BADCHANNELKEY(void) throw();
};

// nb:482
// short for:ERR_CHANOPRIVSNEEDED
// desc:RFC1459 	<channel> :<reason> 	Returned by any command requiring
// special channel privileges (eg. channel operator) to indicate the operation
// was unsuccessful
class ERR_CHANOPRIVSNEEDED : public IError {
  public:
	ERR_CHANOPRIVSNEEDED(
		const std::string &channel,
		const std::string &reason = "You're not channel operator");
	virtual ~ERR_CHANOPRIVSNEEDED(void) throw();
};

// nb:501
// short for:ERR_UMODEUNKNOWNFLAG
// desc:RFC1459 	:<reason> 	Returned by the server to indicate that a MODE
// message was sent with a nickname parameter and that the mode flag sent was
// not recognised
class ERR_UMODEUNKNOWNFLAG : public IError {
  public:
	ERR_UMODEUNKNOWNFLAG(const std::string &reason = "Unknown MODE flag");
	virtual ~ERR_UMODEUNKNOWNFLAG(void) throw();
};
