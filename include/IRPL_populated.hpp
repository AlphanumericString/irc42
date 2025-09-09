/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRPL_populated.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoulard <bgoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 11:35:23 by bgoulard          #+#    #+#             */
/*   Updated: 2025/08/20 11:35:23 by bgoulard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Channel.hpp"
#include "IRPL.hpp"

// nb:001
// short for:RPL_WELCOME
// desc:RFC2812 	:Welcome to the Internet Relay Network <nick>!<user>@<host>
// The first message sent after client registration. The text used varies widely
class RPL_WELCOME : public IRPL {
  public:
	RPL_WELCOME(const std::string &nick, const std::string &c_host);
	virtual ~RPL_WELCOME(void);
};

// nb:002
// short for:RPL_YOURHOST
// desc:RFC2812 	:Your host is <servername>, running version <version> 	Part
// of the post-registration greeting. Text varies widely
class RPL_YOURHOST : public IRPL {
  public:
	RPL_YOURHOST();
	virtual ~RPL_YOURHOST(void);
};

// nb:003
// short for:RPL_CREATED
// desc:RFC2812 	:This server was created <date> 	Part of the
// post-registration greeting. Text varies widely
class RPL_CREATED : public IRPL {
  public:
	RPL_CREATED();
	virtual ~RPL_CREATED(void);
};

// nb:004
// short for:RPL_MYINFO
// desc:RFC2812 	<server_name> <version> <user_modes> <chan_modes> 	Part of
// the post-registration greeting
class RPL_MYINFO : public IRPL {
  public:
	RPL_MYINFO();
	virtual ~RPL_MYINFO(void);
};

// nb:311
// short for:RPL_WHOISUSER
// desc:RFC1459 	<nick> <user> <host> * :<real_name> 	Reply to WHOIS -
// Information about the user
class RPL_WHOISUSER : public IRPL {
  public:
	RPL_WHOISUSER(const std::string &nick, const std::string &user,
				  const std::string &host, const std::string &real_name);
	virtual ~RPL_WHOISUSER(void);
};

// nb:312
// short for:RPL_WHOISSERVER
// desc:RFC1459 	<nick> <server> :<server_info> 	Reply to WHOIS - What server
// they're on
class RPL_WHOISSERVER : public IRPL {
  public:
	RPL_WHOISSERVER(const std::string &nick, const std::string &server_name,
					const std::string &server_info);
	virtual ~RPL_WHOISSERVER(void);
};

// nb:314
// short for:RPL_WHOWASUSER
// desc:RFC1459 	<nick> <user> <host> * :<real_name> 	Reply to WHOWAS -
// Information about the user
class RPL_WHOWASUSER : public IRPL {
  public:
	RPL_WHOWASUSER(const std::string &nick, const std::string &user,
				   const std::string &host, const std::string &real_name);
	virtual ~RPL_WHOWASUSER(void);
};

// nb:317
// short for:RPL_WHOISIDLE
// desc:RFC1459 	<nick> <seconds> :seconds idle 	Reply to WHOIS - Idle
// information
class RPL_WHOISIDLE : public IRPL {
  public:
	RPL_WHOISIDLE(const std::string &nick, unsigned long secs);
	virtual ~RPL_WHOISIDLE(void);
};

// nb:318
// short for:RPL_ENDOFWHOIS
// desc:RFC1459 	<nick> :<info> 	Reply to WHOIS - End of list
class RPL_ENDOFWHOIS : public IRPL {
  public:
	RPL_ENDOFWHOIS(const std::string &nick,
				   const std::string &info = "End of /WHOIS list");
	virtual ~RPL_ENDOFWHOIS(void);
};

// nb:319
// short for:RPL_WHOISCHANNELS
// desc:RFC1459 	<nick> :*( ( '@' / '+' ) <channel> ' ' ) 	Reply to WHOIS -
// Channel list for user (See RFC)
class RPL_WHOISCHANNELS : public IRPL {
  public:
	RPL_WHOISCHANNELS(const std::string &nick, const std::string &chan_list);
	virtual ~RPL_WHOISCHANNELS(void);
};

// nb:324
// short for:RPL_CHANNELMODEIS
// desc:RFC1459 	<channel> <mode> <mode_params>
class RPL_CHANNELMODEIS : public IRPL {
  public:
	RPL_CHANNELMODEIS(const std::string &ch_name, const std::string &modes,
					  const std::string &mode_params = "");
	virtual ~RPL_CHANNELMODEIS(void);
};

// nb:331
// short for:RPL_NOTOPIC
// desc:RFC1459 	<channel> :<info> 	Response to TOPIC when no topic is set
class RPL_NOTOPIC : public IRPL {
  public:
	RPL_NOTOPIC(const std::string &ch_name);
	virtual ~RPL_NOTOPIC(void);
	virtual std::string toString(const Server &s, const Client &c);
};

// nb:332
// short for:RPL_TOPIC
// desc:RFC1459 	<channel> :<topic> 	Response to TOPIC with the set topic
class RPL_TOPIC : public IRPL {
  public:
	RPL_TOPIC(const std::string &ch_name, const std::string &topic);
	virtual ~RPL_TOPIC(void);
	virtual std::string toString(const Server &s, const Client &c);
};

// nb:341
// short for:RPL_INVITING
// desc:RFC1459 	<nick> <channel> 	Returned by the server to indicate that
// the attempted INVITE message was successful and is being passed onto the end
// client. Note that RFC1459 documents the parameters in the reverse order. The
// format given here is the format used on production servers, and should be
// considered the standard reply above that given by RFC1459.
class RPL_INVITING : public IRPL {
  public:
	RPL_INVITING(const std::string &nick_invitee, const std::string &ch_name);
	virtual ~RPL_INVITING(void);
};

// nb:351
// short for:RPL_VERSION
// desc:RFC1459 	<version>[.<debuglevel>] <server> :<comments> 	Reply by the
// server showing its version details, however this format is not often adhered
// to
class RPL_VERSION : public IRPL {
  public:
	RPL_VERSION(const std::string &version, const std::string &server,
				const std::string &comments = "");
	RPL_VERSION(const std::string &version, const std::string &debuglevel,
				const std::string &server, const std::string &comments);
	virtual ~RPL_VERSION(void);
};

// nb:353
// short for:RPL_NAMREPLY
// desc:RFC1459 	( '=' / '*' / '@' ) <channel> ' ' : [ '@' / '+' ] <nick> *(
// ' ' [ '@' / '+' ] <nick> ) 	Reply to NAMES (See RFC)
// '=' = public channel, '*' = private channel, '@' = secret channel
//  -> if none of these are used, it is a public channel by default
// '@' = channel operator, '+' = voiced user
//  -> if none of these are used, the user is a normal user
// note: we dont support secret channels, so no need to implement '@' case
// note: we dont support private channels, so no need to implement '*' case
// note: we dont support voiced users, so no need to implement '+' case
// note: tldr; we only need to implement '@' for channel clients
class RPL_NAMREPLY : public IRPL {
  public:
	RPL_NAMREPLY(const std::string		   &ch_name,
				 const std::list< Client > &ch_clients,
				 const std::list< Client > &ops, const ChanMod mode);
	virtual ~RPL_NAMREPLY(void);
	virtual std::string toString(const Server &s, const Client &c);
};

// nb:366
// short for:RPL_ENDOFNAMES
// desc:RFC1459 	<channel> :<info> 	Termination of an RPL_NAMREPLY list
class RPL_ENDOFNAMES : public IRPL {
  public:
	RPL_ENDOFNAMES(const std::string &channel,
				   const std::string &info = "end of /NAMES list.");
	virtual ~RPL_ENDOFNAMES(void);
	virtual std::string toString(const Server &s, const Client &c);
};

// nb:369
// short for:RPL_ENDOFWHOWAS
// desc:RFC1459 	<nick> :<info> 	Reply to WHOWAS - End of list
class RPL_ENDOFWHOWAS : public IRPL {
  public:
	RPL_ENDOFWHOWAS(const std::string &nick,
					const std::string &info = "End of /WHOWAS");
	virtual ~RPL_ENDOFWHOWAS(void);
};
