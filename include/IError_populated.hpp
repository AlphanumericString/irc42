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
	ERR_NOSUCHNICK();
	virtual ~ERR_NOSUCHNICK(void) throw();
};

// nb:402
// short for:ERR_NOSUCHSERVER
// desc:RFC1459 	<server> :<reason> 	Used to indicate the server name given
// currently doesn't exist
class ERR_NOSUCHSERVER : public IError {
  public:
	ERR_NOSUCHSERVER();
	virtual ~ERR_NOSUCHSERVER(void) throw();
};

// nb:403
// short for:ERR_NOSUCHCHANNEL
// desc:RFC1459 	<channel> :<reason> 	Used to indicate the given channel
// name is invalid, or does not exist
class ERR_NOSUCHCHANNEL : public IError {
  public:
	ERR_NOSUCHCHANNEL();
	virtual ~ERR_NOSUCHCHANNEL(void) throw();
};

// nb:404
// short for:ERR_CANNOTSENDTOCHAN
// desc:RFC1459 	<channel> :<reason> 	Sent to a user who does not have the
// rights to send a message to a channel
class ERR_CANNOTSENDTOCHAN : public IError {
  public:
	ERR_CANNOTSENDTOCHAN();
	virtual ~ERR_CANNOTSENDTOCHAN(void) throw();
};

// nb:405
// short for:ERR_TOOMANYCHANNELS
// desc:RFC1459 	<channel> :<reason> 	Sent to a user when they have joined
// the maximum number of allowed channels and they tried to join another channel
class ERR_TOOMANYCHANNELS : public IError {
  public:
	ERR_TOOMANYCHANNELS();
	virtual ~ERR_TOOMANYCHANNELS(void) throw();
};

// nb:406
// short for:ERR_WASNOSUCHNICK
// desc:RFC1459 	<nick> :<reason> 	Returned by WHOWAS to indicate there was
// no history information for a given nickname
class ERR_WASNOSUCHNICK : public IError {
  public:
	ERR_WASNOSUCHNICK();
	virtual ~ERR_WASNOSUCHNICK(void) throw();
};

// nb:407
// short for:ERR_TOOMANYTARGETS
// desc:RFC1459 	<target> :<reason> 	The given target(s) for a command are
// ambiguous in that they relate to too many targets
class ERR_TOOMANYTARGETS : public IError {
  public:
	ERR_TOOMANYTARGETS();
	virtual ~ERR_TOOMANYTARGETS(void) throw();
};

// nb:408
// short for:ERR_NOSUCHSERVICE
// desc:RFC2812 	<service_name> :<reason> 	Returned to a client which is
// attempting to send an SQUERY (or other message) to a service which does not
// exist
class ERR_NOSUCHSERVICE : public IError {
  public:
	ERR_NOSUCHSERVICE();
	virtual ~ERR_NOSUCHSERVICE(void) throw();
};

// nb:409
// short for:ERR_NOORIGIN
// desc:RFC1459 	:<reason> 	PING or PONG message missing the originator
// parameter which is required since these commands must work without valid
// prefixes
class ERR_NOORIGIN : public IError {
  public:
	ERR_NOORIGIN();
	virtual ~ERR_NOORIGIN(void) throw();
};

// nb:411
// short for:ERR_NORECIPIENT
// desc:RFC1459 	:<reason> 	Returned when no recipient is given with a
// command
class ERR_NORECIPIENT : public IError {
  public:
	ERR_NORECIPIENT();
	virtual ~ERR_NORECIPIENT(void) throw();
};

// nb:412
// short for:ERR_NOTEXTTOSEND
// desc:RFC1459 	:<reason> 	Returned when NOTICE/PRIVMSG is used with no
// message given
class ERR_NOTEXTTOSEND : public IError {
  public:
	ERR_NOTEXTTOSEND();
	virtual ~ERR_NOTEXTTOSEND(void) throw();
};

// nb:413
// short for:ERR_NOTOPLEVEL
// desc:RFC1459 	<mask> :<reason> 	Used when a message is being sent to a
// mask without being limited to a top-level domain (i.e. * instead of *.au)
class ERR_NOTOPLEVEL : public IError {
  public:
	ERR_NOTOPLEVEL();
	virtual ~ERR_NOTOPLEVEL(void) throw();
};

// nb:414
// short for:ERR_WILDTOPLEVEL
// desc:RFC1459 	<mask> :<reason> 	Used when a message is being sent to a
// mask with a wild-card for a top level domain (i.e. *.*)
class ERR_WILDTOPLEVEL : public IError {
  public:
	ERR_WILDTOPLEVEL();
	virtual ~ERR_WILDTOPLEVEL(void) throw();
};

// nb:415
// short for:ERR_BADMASK
// desc:RFC2812 	<mask> :<reason> 	Used when a message is being sent to a
// mask with an invalid syntax
class ERR_BADMASK : public IError {
  public:
	ERR_BADMASK();
	virtual ~ERR_BADMASK(void) throw();
};

// nb:416
// short for:ERR_TOOMANYMATCHES
// desc:IRCnet 	<command> [<mask>] :<info> 	Returned when too many matches have
// been found for a command and the output has been truncated. An example would
// be the WHO command, where by the mask '*' would match everyone on the
// network! Ouch!
class ERR_TOOMANYMATCHES : public IError {
  public:
	ERR_TOOMANYMATCHES();
	virtual ~ERR_TOOMANYMATCHES(void) throw();
};

// nb:421
// short for:ERR_UNKNOWNCOMMAND
// desc:RFC1459 	<command> :<reason> 	Returned when the given command is
// unknown to the server (or hidden because of lack of access rights)
class ERR_UNKNOWNCOMMAND : public IError {
  public:
	ERR_UNKNOWNCOMMAND(const std::string &cmd_predicate);
	virtual ~ERR_UNKNOWNCOMMAND(void) throw();
};

// nb:422
// short for:ERR_NOMOTD
// desc:RFC1459 	:<reason> 	Sent when there is no MOTD to send the client
class ERR_NOMOTD : public IError {
  public:
	ERR_NOMOTD();
	virtual ~ERR_NOMOTD(void) throw();
};

// nb:423
// short for:ERR_NOADMININFO
// desc:RFC1459 	<server> :<reason> 	Returned by a server in response to an
// ADMIN request when no information is available. RFC1459 mentions this in the
// list of numerics. While it's not listed as a valid reply in section 4.3.7
// ('Admin command'), it's confirmed to exist in the real world.
class ERR_NOADMININFO : public IError {
  public:
	ERR_NOADMININFO();
	virtual ~ERR_NOADMININFO(void) throw();
};

// nb:424
// short for:ERR_FILEERROR
// desc:RFC1459 	:<reason> 	Generic error message used to report a failed
// file operation during the processing of a command
class ERR_FILEERROR : public IError {
  public:
	ERR_FILEERROR();
	virtual ~ERR_FILEERROR(void) throw();
};

// nb:431
// short for:ERR_NONICKNAMEGIVEN
// desc:RFC1459 	:<reason> 	Returned when a nickname parameter expected for
// a command isn't found
class ERR_NONICKNAMEGIVEN : public IError {
  public:
	ERR_NONICKNAMEGIVEN();
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
	ERR_ERRONEUSNICKNAME(const std::string &nick);
	virtual ~ERR_ERRONEUSNICKNAME(void) throw();
};

// nb:433
// short for:ERR_NICKNAMEINUSE
// desc:RFC1459 	<nick> :<reason> 	Returned by the NICK command when the
// given nickname is already in use
class ERR_NICKNAMEINUSE : public IError {
  public:
	ERR_NICKNAMEINUSE(const std::string &nick);
	virtual ~ERR_NICKNAMEINUSE(void) throw();
};

// nb:436
// short for:ERR_NICKCOLLISION
// desc:RFC1459 	<nick> :<reason> 	Returned by a server to a client when it
// detects a nickname collision
class ERR_NICKCOLLISION : public IError {
  public:
	ERR_NICKCOLLISION();
	virtual ~ERR_NICKCOLLISION(void) throw();
};

// nb:437
// short for:ERR_UNAVAILRESOURCE
// desc:RFC2812 	<nick/channel/service> :<reason> 	Return when the target
// is unable to be reached temporarily, eg. a delay mechanism in play, or a
// service being offline
class ERR_UNAVAILRESOURCE : public IError {
  public:
	ERR_UNAVAILRESOURCE();
	virtual ~ERR_UNAVAILRESOURCE(void) throw();
};

// nb:441
// short for:ERR_USERNOTINCHANNEL
// desc:RFC1459 	<nick> <channel> :<reason> 	Returned by the server to
// indicate that the target user of the command is not on the given channel
class ERR_USERNOTINCHANNEL : public IError {
  public:
	ERR_USERNOTINCHANNEL();
	virtual ~ERR_USERNOTINCHANNEL(void) throw();
};

// nb:442
// short for:ERR_NOTONCHANNEL
// desc:RFC1459 	<channel> :<reason> 	Returned by the server whenever a
// client tries to perform a channel effecting command for which the client is
// not a member
class ERR_NOTONCHANNEL : public IError {
  public:
	ERR_NOTONCHANNEL();
	virtual ~ERR_NOTONCHANNEL(void) throw();
};

// nb:443
// short for:ERR_USERONCHANNEL
// desc:RFC1459 	<nick> <channel> [:<reason>] 	Returned when a client tries
// to invite a user to a channel they're already on
class ERR_USERONCHANNEL : public IError {
  public:
	ERR_USERONCHANNEL();
	virtual ~ERR_USERONCHANNEL(void) throw();
};

// nb:444
// short for:ERR_NOLOGIN
// desc:RFC1459 	<user> :<reason> 	Returned by the SUMMON command if a
// given user was not logged in and could not be summoned
class ERR_NOLOGIN : public IError {
  public:
	ERR_NOLOGIN();
	virtual ~ERR_NOLOGIN(void) throw();
};

// nb:445
// short for:ERR_SUMMONDISABLED
// desc:RFC1459 	:<reason> 	Returned by SUMMON when it has been disabled or
// not implemented
class ERR_SUMMONDISABLED : public IError {
  public:
	ERR_SUMMONDISABLED();
	virtual ~ERR_SUMMONDISABLED(void) throw();
};

// nb:446
// short for:ERR_USERSDISABLED
// desc:RFC1459 	:<reason> 	Returned by USERS when it has been disabled or
// not implemented
class ERR_USERSDISABLED : public IError {
  public:
	ERR_USERSDISABLED();
	virtual ~ERR_USERSDISABLED(void) throw();
};

// nb:451
// short for:ERR_NOTREGISTERED
// desc:RFC1459 	:<reason> 	Returned by the server to indicate that the
// client must be registered before the server will allow it to be parsed in
// detail
class ERR_NOTREGISTERED : public IError {
  public:
	ERR_NOTREGISTERED();
	virtual ~ERR_NOTREGISTERED(void) throw();
};

// nb:461
// short for:ERR_NEEDMOREPARAMS
// desc:RFC1459 	<command> :<reason> 	Returned by the server by any
// command which requires more parameters than the number of parameters given
class ERR_NEEDMOREPARAMS : public IError {
  public:
	ERR_NEEDMOREPARAMS(const std::string &);
	virtual ~ERR_NEEDMOREPARAMS(void) throw();
};

// nb:462
// short for:ERR_ALREADYREGISTERED
// desc:RFC1459 	:<reason> 	Returned by the server to any link which
// attempts to register again
class ERR_ALREADYREGISTERED : public IError {
  public:
	ERR_ALREADYREGISTERED();
	virtual ~ERR_ALREADYREGISTERED(void) throw();
};

// nb:463
// short for:ERR_NOPERMFORHOST
// desc:RFC1459 	:<reason> 	Returned to a client which attempts to register
// with a server which has been configured to refuse connections from the
// client's host
class ERR_NOPERMFORHOST : public IError {
  public:
	ERR_NOPERMFORHOST();
	virtual ~ERR_NOPERMFORHOST(void) throw();
};

// nb:464
// short for:ERR_PASSWDMISMATCH
// desc:RFC1459 	:<reason> 	Returned by the PASS command to indicate the
// given password was required and was either not given or was incorrect
class ERR_PASSWDMISMATCH : public IError {
  public:
	ERR_PASSWDMISMATCH();
	virtual ~ERR_PASSWDMISMATCH(void) throw();
};

// nb:465
// short for:ERR_YOUREBANNEDCREEP
// desc:RFC1459 	:<reason> 	Returned to a client after an attempt to
// register on a server configured to ban connections from that client
class ERR_YOUREBANNEDCREEP : public IError {
  public:
	ERR_YOUREBANNEDCREEP();
	virtual ~ERR_YOUREBANNEDCREEP(void) throw();
};

// nb:466
// short for:ERR_YOUWILLBEBANNED
// desc:RFC1459 		Sent by a server to a user to inform that access to the
// server will soon be denied
class ERR_YOUWILLBEBANNED : public IError {
  public:
	ERR_YOUWILLBEBANNED();
	virtual ~ERR_YOUWILLBEBANNED(void) throw();
};

// nb:467
// short for:ERR_KEYSET
// desc:RFC1459 	<channel> :<reason> 	Returned when the channel key for a
// channel has already been set
class ERR_KEYSET : public IError {
  public:
	ERR_KEYSET();
	virtual ~ERR_KEYSET(void) throw();
};

// nb:471
// short for:ERR_CHANNELISFULL
// desc:RFC1459 	<channel> :<reason> 	Returned when attempting to join a
// channel which is set +l and is already full
class ERR_CHANNELISFULL : public IError {
  public:
	ERR_CHANNELISFULL();
	virtual ~ERR_CHANNELISFULL(void) throw();
};

// nb:472
// short for:ERR_UNKNOWNMODE
// desc:RFC1459 	<char> :<reason> 	Returned when a given mode is unknown
class ERR_UNKNOWNMODE : public IError {
  public:
	ERR_UNKNOWNMODE();
	virtual ~ERR_UNKNOWNMODE(void) throw();
};

// nb:473
// short for:ERR_INVITEONLYCHAN
// desc:RFC1459 	<channel> :<reason> 	Returned when attempting to join a
// channel which is invite only without an invitation
class ERR_INVITEONLYCHAN : public IError {
  public:
	ERR_INVITEONLYCHAN();
	virtual ~ERR_INVITEONLYCHAN(void) throw();
};

// nb:474
// short for:ERR_BANNEDFROMCHAN
// desc:RFC1459 	<channel> :<reason> 	Returned when attempting to join a
// channel a user is banned from
class ERR_BANNEDFROMCHAN : public IError {
  public:
	ERR_BANNEDFROMCHAN();
	virtual ~ERR_BANNEDFROMCHAN(void) throw();
};

// nb:475
// short for:ERR_BADCHANNELKEY
// desc:RFC1459 	<channel> :<reason> 	Returned when attempting to join a
// key-locked channel either without a key or with the wrong key
class ERR_BADCHANNELKEY : public IError {
  public:
	ERR_BADCHANNELKEY();
	virtual ~ERR_BADCHANNELKEY(void) throw();
};

// nb:476
// short for:ERR_BADCHANMASK
// desc:RFC2812 	<channel> :<reason> 	The given channel mask was invalid
class ERR_BADCHANMASK : public IError {
  public:
	ERR_BADCHANMASK();
	virtual ~ERR_BADCHANMASK(void) throw();
};

// nb:477
// short for:ERR_NOCHANMODES
// desc:RFC2812 	<channel> :<reason> 	Returned when attempting to set a
// mode on a channel which does not support channel modes, or channel mode
// changes. Also known as ERR_MODELESS
class ERR_NOCHANMODES : public IError {
  public:
	ERR_NOCHANMODES();
	virtual ~ERR_NOCHANMODES(void) throw();
};

// nb:478
// short for:ERR_BANLISTFULL
// desc:RFC2812 	<channel> <char> :<reason> 	Returned when a channel access
// list (i.e. ban list etc) is full and cannot be added to
class ERR_BANLISTFULL : public IError {
  public:
	ERR_BANLISTFULL();
	virtual ~ERR_BANLISTFULL(void) throw();
};

// nb:481
// short for:ERR_NOPRIVILEGES
// desc:RFC1459 	:<reason> 	Returned by any command requiring special
// privileges (eg. IRC operator) to indicate the operation was unsuccessful
class ERR_NOPRIVILEGES : public IError {
  public:
	ERR_NOPRIVILEGES();
	virtual ~ERR_NOPRIVILEGES(void) throw();
};

// nb:482
// short for:ERR_CHANOPRIVSNEEDED
// desc:RFC1459 	<channel> :<reason> 	Returned by any command requiring
// special channel privileges (eg. channel operator) to indicate the operation
// was unsuccessful
class ERR_CHANOPRIVSNEEDED : public IError {
  public:
	ERR_CHANOPRIVSNEEDED();
	virtual ~ERR_CHANOPRIVSNEEDED(void) throw();
};

// nb:483
// short for:ERR_CANTKILLSERVER
// desc:RFC1459 	:<reason> 	Returned by KILL to anyone who tries to kill a
// server
class ERR_CANTKILLSERVER : public IError {
  public:
	ERR_CANTKILLSERVER();
	virtual ~ERR_CANTKILLSERVER(void) throw();
};

// nb:484
// short for:ERR_RESTRICTED
// desc:RFC2812 	:<reason> 	Sent by the server to a user upon connection to
// indicate the restricted nature of the connection (i.e. usermode +r)
class ERR_RESTRICTED : public IError {
  public:
	ERR_RESTRICTED();
	virtual ~ERR_RESTRICTED(void) throw();
};

// nb:485
// short for:ERR_UNIQOPRIVSNEEDED
// desc:RFC2812 	:<reason> 	Any mode requiring 'channel creator' privileges
// returns this error if the client is attempting to use it while not a channel
// creator on the given channel
class ERR_UNIQOPRIVSNEEDED : public IError {
  public:
	ERR_UNIQOPRIVSNEEDED();
	virtual ~ERR_UNIQOPRIVSNEEDED(void) throw();
};

// nb:491
// short for:ERR_NOOPERHOST
// desc:RFC1459 	:<reason> 	Returned by OPER to a client who cannot become
// an IRC operator because the server has been configured to disallow the
// client's host
class ERR_NOOPERHOST : public IError {
  public:
	ERR_NOOPERHOST();
	virtual ~ERR_NOOPERHOST(void) throw();
};

// nb:492
// short for:ERR_NOSERVICEHOST
// desc:RFC1459
class ERR_NOSERVICEHOST : public IError {
  public:
	ERR_NOSERVICEHOST();
	virtual ~ERR_NOSERVICEHOST(void) throw();
};

// nb:501
// short for:ERR_UMODEUNKNOWNFLAG
// desc:RFC1459 	:<reason> 	Returned by the server to indicate that a MODE
// message was sent with a nickname parameter and that the mode flag sent was
// not recognised
class ERR_UMODEUNKNOWNFLAG : public IError {
  public:
	ERR_UMODEUNKNOWNFLAG();
	virtual ~ERR_UMODEUNKNOWNFLAG(void) throw();
};

// nb:502
// short for:ERR_USERSDONTMATCH
// desc:RFC1459 	:<reason> 	Error sent to any user trying to view or change
class ERR_USERSDONTMATCH : public IError {
  public:
	ERR_USERSDONTMATCH();
	virtual ~ERR_USERSDONTMATCH(void) throw();
};
// the user mode for a user other than themselves
