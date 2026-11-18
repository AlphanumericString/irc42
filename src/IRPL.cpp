/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRPL.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoulard <bgoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 13:41:24 by bgoulard          #+#    #+#             */
/*   Updated: 2025/08/15 13:41:24 by bgoulard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRPL.hpp"

#include <iomanip>
#include <list>
#include <sstream>

#include "IError.hpp"
#include "IError_populated.hpp"
#include "IRPL_populated.hpp"
#include "Server.hpp"
#include "generics.hpp"

std::string IRPL::toString(const Server &s, const Client &c) {
	std::stringstream ss;

	ss << ":" << s.getServerState().getName() << " ";
	ss << std::setw(3) << std::setfill('0') << _code;
	ss << " " << c.getNick();
	if (string.find(":") == std::string::npos)
		ss << " :";
	if (string.c_str()[0] != ' ' && ss.str().end()[-1] != ' ')
		ss << " ";
	ss << string << "\r\n";
	return ss.str();
}

// --- customs ---

RPL_JOIN::RPL_JOIN(const std::string &infoclient, const std::string &ch_name)
	: IRPL(000, "...") {
	IRPL::string = ":" + infoclient + " JOIN :" + ch_name;
};

RPL_JOIN::~RPL_JOIN(void) {};

std::string RPL_JOIN::toString(const Server &s, const Client &c) {
	(void)s;
	(void)c;

	return IRPL::string + "\r\n";
}

// --- numeric replies ---

// nb:001
RPL_WELCOME::RPL_WELCOME(const std::string &nick, const std::string &c_hostname)
	: IRPL(001, "Welcome to the Internet Relay Network " + nick + "!" + nick +
					"@" + c_hostname) {};
RPL_WELCOME::~RPL_WELCOME(void) {};

// nb:002
RPL_YOURHOST::RPL_YOURHOST()
	: IRPL(002, "Your host is " SERVER_NAME_DFLT ", running version 1.0") {};
RPL_YOURHOST::~RPL_YOURHOST(void) {};

// nb:003
RPL_CREATED::RPL_CREATED()
	: IRPL(003, "This server was created by " IRC_SERVER_AUTHORS " and is "
				"running on a custom IRC server implementation "
				"(version " IRC_SERVER_VERSION ").") {};
RPL_CREATED::~RPL_CREATED(void) {};

// nb:004
RPL_MYINFO::RPL_MYINFO()
	: IRPL(004, SERVER_NAME_DFLT
		   " " IRC_SERVER_VERSION
		   " " /* available user modes   available chanel modes*/) {}
RPL_MYINFO::~RPL_MYINFO() {};

// nb:311
// short for:RPL_WHOISUSER
// desc:RFC1459        <nick> <user> <host> * :<real_name>     Reply to WHOIS -
// Information about the user
RPL_WHOISUSER::RPL_WHOISUSER(const std::string &nick, const std::string &user,
							 const std::string &host,
							 const std::string &real_name)
	: IRPL(311, "...") {
	IRPL::string = nick + " " + user + " " + host + " * :" + real_name;
};
RPL_WHOISUSER::~RPL_WHOISUSER(void) {};

// nb:312
// short for:RPL_WHOISSERVER
// desc:RFC1459        <nick> <server> :<server_info>  Reply to WHOIS - What
// server they're on
RPL_WHOISSERVER::RPL_WHOISSERVER(const std::string &nick,
								 const std::string &server,
								 const std::string &server_info)
	: IRPL(312, nick + " " + server + " :" + server_info) {};
RPL_WHOISSERVER::~RPL_WHOISSERVER(void) {};

// nb:314
// short for:RPL_WHOWASUSER
// desc:RFC1459        <nick> <user> <host> * :<real_name>     Reply to WHOWAS -
// Information about the user
RPL_WHOWASUSER::RPL_WHOWASUSER(const std::string &nick, const std::string &user,
							   const std::string &host,
							   const std::string &real_name)
	: IRPL(314, nick + " " + user + " " + host + " * :" + real_name) {

	  };
RPL_WHOWASUSER::~RPL_WHOWASUSER(void) {};

// nb:317
// short for:RPL_WHOISIDLE
// desc:RFC1459        <nick> <seconds> :seconds idle
// Reply to WHOIS - Idle information
RPL_WHOISIDLE::RPL_WHOISIDLE(const std::string &nick, unsigned long secs)
	: IRPL(317, nick + " " + to_string(secs) + " : since last activity.") {};
RPL_WHOISIDLE::~RPL_WHOISIDLE(void) {};

// nb:318
// short for:RPL_ENDOFWHOIS
// desc:RFC1459        <nick> :<info>  Reply to WHOIS - End of list
RPL_ENDOFWHOIS::RPL_ENDOFWHOIS(const std::string &nick, const std::string &info)
	: IRPL(318, nick + " :" + info) {};
RPL_ENDOFWHOIS::~RPL_ENDOFWHOIS(void) {};

// nb:319
// short for:RPL_WHOISCHANNELS
// desc:RFC1459        <nick> :*( ( '@' / '+' ) <channel> ' ' )        Reply to
// WHOIS - Channel list for user (See RFC)
RPL_WHOISCHANNELS::RPL_WHOISCHANNELS(const std::string &nick,
									 const std::string &chanstr)
	: IRPL(319, nick + " :" + chanstr) {};
RPL_WHOISCHANNELS::~RPL_WHOISCHANNELS(void) {};

// nb:324
// short for:RPL_CHANNELMODEIS
// desc:RFC1459        <channel> <mode> <mode_params>
RPL_CHANNELMODEIS::RPL_CHANNELMODEIS(std::string const &ch_name,
									 std::string const &modes,
									 std::string const &mode_params)
	: IRPL(324, ch_name + " " + modes +
					(mode_params.empty() ? "" : " " + mode_params)) {};
RPL_CHANNELMODEIS::~RPL_CHANNELMODEIS(void) {};
std::string RPL_CHANNELMODEIS::toString(const Server &s, const Client &c) {
	std::stringstream ss;

	ss << ":" << s.getServerState().getName() << " ";
	ss << std::setw(3) << std::setfill('0') << _code;
	ss << " " << c.getNick();
	ss << " " << string << "\r\n";
	return ss.str();
};

// nb:331
// short for:RPL_NOTOPIC
// desc:RFC1459        <channel> :<info>       Response to TOPIC when no topic
// is set
RPL_NOTOPIC::RPL_NOTOPIC(const std::string &ch_name)
	: IRPL(331, ch_name + " :" + "No topic set for channel " + ch_name + ".") {
	  };
RPL_NOTOPIC::~RPL_NOTOPIC(void) {};
std::string RPL_NOTOPIC::toString(const Server &s, const Client &c) {
	(void)s;
	std::stringstream ss;

	ss << ":" << s.getServerState().getName() << " ";
	ss << std::setw(3) << std::setfill('0') << _code;
	ss << " " << c.getNick();
	ss << " " << string << "\r\n";
	return ss.str();
};

// nb:332
// short for:RPL_TOPIC
// desc:RFC1459        <channel> :<topic>      Response to TOPIC with the set
// topic
RPL_TOPIC::RPL_TOPIC(const std::string &ch_name, const std::string &topic)
	: IRPL(332, ch_name + " :" + topic) {};
RPL_TOPIC::~RPL_TOPIC(void) {};
std::string RPL_TOPIC::toString(const Server &s, const Client &c) {
	std::stringstream ss;

	ss << ":" << s.getServerState().getName() << " ";
	ss << std::setw(3) << std::setfill('0') << _code;
	ss << " " << c.getNick();
	ss << " " << string << "\r\n";
	return ss.str();
};

// nb:341
// short for:RPL_INVITING
// desc:RFC1459        <nick>: <channel>       Returned by the server to
// indicate that the attempted INVITE message was successful and is being passed
// onto the end client. Note that RFC1459 documents the parameters in the
// reverse order. The format given here is the format used on production
// servers, and should be considered the standard reply above that given by
// RFC1459.
RPL_INVITING::RPL_INVITING(const std::string &nick, const std::string &ch_name)
	: IRPL(341, nick + " :" + ch_name) {};
RPL_INVITING::~RPL_INVITING(void) {};

// nb:351
// short for:RPL_VERSION
// desc:RFC1459        <version>[.<debuglevel>] <server> :<comments>   Reply by
// the server showing its version details, however this format is not often
// adhered to
RPL_VERSION::RPL_VERSION(const std::string &version,
						 const std::string &serverName,
						 const std::string &comments)
	: IRPL(351, version + " " + serverName + " :" + comments) {}
RPL_VERSION::RPL_VERSION(const std::string &version,
						 const std::string &debuglevel,
						 const std::string &serverName,
						 const std::string &comments)
	: IRPL(351,
		   version + "." + debuglevel + " " + serverName + " :" + comments) {}
RPL_VERSION::~RPL_VERSION(void) {};

// nb:353
// short for:RPL_NAMREPLY
// desc:RFC1459        ( '=' / '*' / '@' ) <channel> ' ' : [ '@' / '+' ] <nick>
// *( ' ' [ '@' / '+' ] <nick> )  Reply to NAMES (See RFC)
// '=' = public channel, '*' = private channel, '@' = secret channel
// chan with +ki modes shows as '@' too
// chan with +i mode shows as '*'
// '@' = chan op, ' ' = normal user
//
RPL_NAMREPLY::RPL_NAMREPLY(const std::string		 &ch_name,
						   const std::list< Client > &cl_list,
						   const std::list< Client > &ops, const ChanMod cm)
	: IRPL(353, "...") {

	IRPL::string = "";
	if (cm & MODE_I && cm & MODE_K)
		IRPL::string += "@ ";
	else if (cm & MODE_I)
		IRPL::string += "* ";
	else
		IRPL::string += "= ";

	IRPL::string += ch_name + " :";

	for (std::list< Client >::const_iterator ci = cl_list.begin();
		 ci != cl_list.end();) {
		if (containsInList< Client >(ops, *ci))
			IRPL::string += "@";
		IRPL::string += ci->getNick();
		if (++ci != cl_list.end())
			IRPL::string += " ";
	}
};
RPL_NAMREPLY::~RPL_NAMREPLY(void) {};

std::string RPL_NAMREPLY::toString(const Server &s, const Client &c) {
	(void)s;
	std::stringstream ss;

	ss << ":" << s.getServerState().getName() << " ";
	ss << std::setw(3) << std::setfill('0') << _code;
	ss << " " << c.getNick();
	ss << " " << string << "\r\n";
	return ss.str();
};

// nb:366
// short for:RPL_ENDOFNAMES
// desc:RFC1459        <channel> :<info>       Termination of an RPL_NAMREPLY
// list
RPL_ENDOFNAMES::RPL_ENDOFNAMES(const std::string &channel,
							   const std::string &info)
	: IRPL(366, channel + " :" + info) {};
RPL_ENDOFNAMES::~RPL_ENDOFNAMES(void) {};
std::string RPL_ENDOFNAMES::toString(const Server &s, const Client &c) {
	(void)s;
	std::stringstream ss;

	ss << ":" << s.getServerState().getName() << " ";
	ss << std::setw(3) << std::setfill('0') << _code;
	ss << " " << c.getNick();
	ss << " " << string << "\r\n";
	return ss.str();
};

// nb:369
// short for:RPL_ENDOFWHOWAS
// desc:RFC1459        <nick> :<info>  Reply to WHOWAS - End of list
RPL_ENDOFWHOWAS::RPL_ENDOFWHOWAS(const std::string &nick,
								 const std::string &info)
	: IRPL(369, nick + " :" + info) {};
RPL_ENDOFWHOWAS::~RPL_ENDOFWHOWAS(void) {};

// ------------ ERRORS ------------

// nb:401
// short for:ERR_NOSUCHNICK
// desc:RFC1459        <nick> :<reason>        Used to indicate the nickname
// parameter supplied to a command is currently unused
ERR_NOSUCHNICK::ERR_NOSUCHNICK(const std::string &nick,
							   const std::string &reason)
	: IError(401, nick + " :" + reason) {};
ERR_NOSUCHNICK::~ERR_NOSUCHNICK(void) throw() {};

// nb:402
// short for:ERR_NOSUCHSERVER
// desc:RFC1459        <server> :<reason>      Used to indicate the server name
// given currently doesn't exist
ERR_NOSUCHSERVER::ERR_NOSUCHSERVER(const std::string &server,
								   const std::string &reason)
	: IError(402, server + " :" + reason) {};
ERR_NOSUCHSERVER::~ERR_NOSUCHSERVER(void) throw() {};

// nb:403
// short for:ERR_NOSUCHCHANNEL
// desc:RFC1459        <channel> :<reason>     Used to indicate the given
// channel name is invalid, or does not exist
ERR_NOSUCHCHANNEL::ERR_NOSUCHCHANNEL(const std::string &ch_name,
									 const std::string &reason)
	: IError(403, ch_name + " :" + reason) {};
ERR_NOSUCHCHANNEL::~ERR_NOSUCHCHANNEL(void) throw() {};

// nb:404
// short for:ERR_CANNOTSENDTOCHAN
// desc:RFC1459        <channel> :<reason>     Sent to a user who does not have
// the rights to send a message to a channel
ERR_CANNOTSENDTOCHAN::ERR_CANNOTSENDTOCHAN(const std::string &ch_name,
										   const std::string &reason)
	: IError(404, ch_name + " :" + reason) {};
ERR_CANNOTSENDTOCHAN::~ERR_CANNOTSENDTOCHAN(void) throw() {};

// nb:406
// short for:ERR_WASNOSUCHNICK
// desc:RFC1459        <nick> :<reason>        Returned by WHOWAS to indicate
// there was no history information for a given nickname
ERR_WASNOSUCHNICK::ERR_WASNOSUCHNICK(const std::string &nick,
									 const std::string &reason)
	: IError(406, nick + " :" + reason) {};
ERR_WASNOSUCHNICK::~ERR_WASNOSUCHNICK(void) throw() {};

// nb:409
// short for:ERR_NOORIGIN
// desc:RFC1459        :<reason>       PING or PONG message missing the
// originator parameter which is required since these commands must work without
// valid prefixes
ERR_NOORIGIN::ERR_NOORIGIN(const std::string &reason) : IError(409, reason) {};
ERR_NOORIGIN::~ERR_NOORIGIN(void) throw() {};

// nb:412
// short for:ERR_NOTEXTTOSEND
// desc:RFC1459        :<reason>       Returned when NOTICE/PRIVMSG is used with
// no message given
ERR_NOTEXTTOSEND::ERR_NOTEXTTOSEND(const std::string &reason)
	: IError(412, reason) {};
ERR_NOTEXTTOSEND::~ERR_NOTEXTTOSEND(void) throw() {};

// nb:414
// short for:ERR_WILDTOPLEVEL
// desc:RFC1459        <mask> :<reason>        Used when a message is being sent
// to a mask with a wild-card for a top level domain (i.e. *.*)
ERR_WILDTOPLEVEL::ERR_WILDTOPLEVEL(const std::string &mask,
								   const std::string &reason)
	: IError(414, mask + " :" + reason) {};
ERR_WILDTOPLEVEL::~ERR_WILDTOPLEVEL(void) throw() {};

// nb:421
// short for:ERR_UNKNOWNCOMMAND
// desc:RFC1459        <command> :<reason>     Returned when the given command
// is unknown to the server (or hidden because of lack of access rights)
ERR_UNKNOWNCOMMAND::ERR_UNKNOWNCOMMAND(const std::string &cmd_predicate,
									   const std::string &reason)
	: IError(421, cmd_predicate + " :" + reason) {};
ERR_UNKNOWNCOMMAND::~ERR_UNKNOWNCOMMAND(void) throw() {}

// nb:431
// short for:ERR_NONICKNAMEGIVEN
// desc:RFC1459        :<reason>       Returned when a nickname parameter
// expected for a command isn't found
ERR_NONICKNAMEGIVEN::ERR_NONICKNAMEGIVEN(const std::string &reason)
	: IError(431, reason) {};
ERR_NONICKNAMEGIVEN::~ERR_NONICKNAMEGIVEN() throw() {}

// nb:432
// short for:ERR_ERRONEUSNICKNAME
// desc:RFC1459        <nick> :<reason>        Returned after receiving a NICK
// message which contains a nickname which is considered invalid, such as it's
// reserved
// ('anonymous') or contains characters considered invalid for nicknames. This
// numeric is misspelt, but remains with this name for historical reasons :)
ERR_ERRONEUSNICKNAME::ERR_ERRONEUSNICKNAME(const std::string &nick,
										   const std::string &reason)
	: IError(432, nick + " :" + reason) {}
ERR_ERRONEUSNICKNAME::~ERR_ERRONEUSNICKNAME(void) throw() {}

// nb:433
// short for:ERR_NICKNAMEINUSE
// desc:RFC1459        <nick> :<reason>        Returned by the NICK command when
// the given nickname is already in use
ERR_NICKNAMEINUSE::ERR_NICKNAMEINUSE(const std::string &nick,
									 const std::string &reason)
	: IError(433, nick + " :" + reason) {}
ERR_NICKNAMEINUSE::~ERR_NICKNAMEINUSE(void) throw() {}

// nb:441
// short for:ERR_USERNOTINCHANNEL
// desc:RFC1459        <nick> <channel> :<reason>      Returned by the server to
// indicate that the target user of the command is not on the given channel
ERR_USERNOTINCHANNEL::ERR_USERNOTINCHANNEL(const std::string &nick,
										   const std::string &ch_name,
										   const std::string &reason)
	: IError(441, nick + " " + ch_name + " :" + reason) {}
ERR_USERNOTINCHANNEL::~ERR_USERNOTINCHANNEL(void) throw() {};

// nb:442
// short for:ERR_NOTONCHANNEL
// desc:RFC1459        <channel> :<reason>     Returned by the server whenever a
// client tries to perform a channel effecting command for which the client is
// not a member
ERR_NOTONCHANNEL::ERR_NOTONCHANNEL(const std::string &chan,
								   const std::string &reason)
	: IError(442, chan + " :" + reason) {}
ERR_NOTONCHANNEL::~ERR_NOTONCHANNEL(void) throw() {}

// nb:443
// short for:ERR_USERONCHANNEL
// desc:RFC1459        <nick> <channel> [:<reason>]    Returned when a client
// tries to invite a user to a channel they're already on
ERR_USERONCHANNEL::ERR_USERONCHANNEL(const std::string &nick,
									 const std::string &chan,
									 const std::string &reason)
	: IError(443, nick + " " + chan) {
	if (reason.empty() == false)
		IError::_s += " :" + reason;
}
ERR_USERONCHANNEL::~ERR_USERONCHANNEL(void) throw() {}

// nb:451
// short for:ERR_NOTREGISTERED
// desc:RFC1459        :<reason>       Returned by the server to indicate that
// the client must be registered before the server will allow it to be parsed in
// detail
ERR_NOTREGISTERED::ERR_NOTREGISTERED(const std::string &reason)
	: IError(452, reason) {};
ERR_NOTREGISTERED::~ERR_NOTREGISTERED(void) throw() {};

// nb:461
// short for:ERR_NEEDMOREPARAMS
// desc:RFC1459        <command> :<reason>     Returned by the server by any
// command which requires more parameters than the number of parameters given
ERR_NEEDMOREPARAMS::ERR_NEEDMOREPARAMS(const std::string &cmd,
									   const std::string &reason)
	: IError(461, cmd + " :" + reason) {}
ERR_NEEDMOREPARAMS::~ERR_NEEDMOREPARAMS(void) throw() {}

// nb:462
// short for:ERR_ALREADYREGISTERED
// desc:RFC1459        :<reason>       Returned by the server to any link which
// attempts to register again
ERR_ALREADYREGISTERED::ERR_ALREADYREGISTERED(const std::string &reason)
	: IError(462, reason) {};
ERR_ALREADYREGISTERED::~ERR_ALREADYREGISTERED(void) throw() {}

// nb:464
// short for:ERR_PASSWDMISMATCH
// desc:RFC1459        :<reason>       Returned by the PASS command to indicate
// the given password was required and was either not given or was incorrect
ERR_PASSWDMISMATCH::ERR_PASSWDMISMATCH(const std::string &r)
	: IError(464, r) {};
ERR_PASSWDMISMATCH::~ERR_PASSWDMISMATCH(void) throw() {}

// nb:471
// short for:ERR_CHANNELISFULL
// desc:RFC1459        <channel> :<reason>     Returned when attempting to join
// a channel which is set +l and is already full
ERR_CHANNELISFULL::ERR_CHANNELISFULL(const std::string &chan,
									 const std::string &r)
	: IError(471, chan + " :" + r) {};
ERR_CHANNELISFULL::~ERR_CHANNELISFULL(void) throw() {};

// nb:472
// short for:ERR_UNKNOWNMODE
// desc:RFC1459        <char> :<reason>        Returned when a given mode is
// unknow
ERR_UNKNOWNMODE::ERR_UNKNOWNMODE(const std::string &char_m,
								 const std::string &r)
	: IError(472, char_m + " :" + r) {};
ERR_UNKNOWNMODE::~ERR_UNKNOWNMODE(void) throw() {};

// nb:473
// short for:ERR_INVITEONLYCHAN
// desc:RFC1459        <channel> :<reason>     Returned when attempting to join
// a channel which is invite only without an invitation
ERR_INVITEONLYCHAN::ERR_INVITEONLYCHAN(const std::string &chan,
									   const std::string &r)
	: IError(473, chan + " :" + r) {};
ERR_INVITEONLYCHAN::~ERR_INVITEONLYCHAN(void) throw() {};

// nb:475
// short for:ERR_BADCHANNELKEY
// desc:RFC1459        <channel> :<reason>     Returned when attempting to join
// a key-locked channel either without a key or with the wrong key
ERR_BADCHANNELKEY::ERR_BADCHANNELKEY(const std::string &chan,
									 const std::string &r)
	: IError(475, chan + " :" + r) {};
ERR_BADCHANNELKEY::~ERR_BADCHANNELKEY(void) throw() {};

// nb:482
// short for:ERR_CHANOPRIVSNEEDED
// desc:RFC1459        <channel> :<reason>     Returned by any command requiring
// special channel privileges (eg. channel operator) to indicate the operation
// was unsuccessful
ERR_CHANOPRIVSNEEDED::ERR_CHANOPRIVSNEEDED(const std::string &chan,
										   const std::string &r)
	: IError(482, chan + " :" + r) {};
ERR_CHANOPRIVSNEEDED::~ERR_CHANOPRIVSNEEDED(void) throw() {};

// nb:501
// short for:ERR_UMODEUNKNOWNFLAG
// desc:RFC1459        :<reason>       Returned by the server to indicate that a
// MODE message was sent with a nickname parameter and that the mode flag sent
// was not recognised
ERR_UMODEUNKNOWNFLAG::ERR_UMODEUNKNOWNFLAG(const std::string &r)
	: IError(501, r) {}
ERR_UMODEUNKNOWNFLAG::~ERR_UMODEUNKNOWNFLAG(void) throw() {};
