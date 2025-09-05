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

// nb:005
// short for:RPL_BOUNCE
// desc:RFC2812 	:Try server <server_name>, port <port_number> 	Sent by the
// server to a user to suggest an alternative server, sometimes used when the
// connection is refused because the server is already full. Also known as
// RPL_SLINE (AustHex), and RPL_REDIR Also see #010.
class RPL_BOUNCE : public IRPL {
  public:
	RPL_BOUNCE();
	virtual ~RPL_BOUNCE(void);
};

// nb:200
// short for:RPL_TRACELINK
// desc:RFC1459 	Link <version>[.<debug_level>] <destination> <next_server>
// [V<protocol_version> <link_uptime_in_seconds> <backstream_sendq>
// <upstream_sendq>] 	See RFC
class RPL_TRACELINK : public IRPL {
  public:
	RPL_TRACELINK();
	virtual ~RPL_TRACELINK(void);
};

// nb:201
// short for:RPL_TRACECONNECTING
// desc:RFC1459 	Try. <class> <server> 	See RFC
class RPL_TRACECONNECTING : public IRPL {
  public:
	RPL_TRACECONNECTING();
	virtual ~RPL_TRACECONNECTING(void);
};

// nb:202
// short for:RPL_TRACEHANDSHAKE
// desc:RFC1459 	H.S. <class> <server> 	See RFC
class RPL_TRACEHANDSHAKE : public IRPL {
  public:
	RPL_TRACEHANDSHAKE();
	virtual ~RPL_TRACEHANDSHAKE(void);
};

// nb:203
// short for:RPL_TRACEUNKNOWN
// desc:RFC1459 	???? <class> [<connection_address>] 	See RFC
class RPL_TRACEUNKNOWN : public IRPL {
  public:
	RPL_TRACEUNKNOWN();
	virtual ~RPL_TRACEUNKNOWN(void);
};

// nb:204
// short for:RPL_TRACEOPERATOR
// desc:RFC1459 	Oper <class> <nick> 	See RFC
class RPL_TRACEOPERATOR : public IRPL {
  public:
	RPL_TRACEOPERATOR();
	virtual ~RPL_TRACEOPERATOR(void);
};

// nb:205
// short for:RPL_TRACEUSER
// desc:RFC1459 	User <class> <nick> 	See RFC
class RPL_TRACEUSER : public IRPL {
  public:
	RPL_TRACEUSER();
	virtual ~RPL_TRACEUSER(void);
};

// nb:206
// short for:RPL_TRACESERVER
// desc:RFC1459 	Serv <class> <int>S <int>C <server>
// <nick!user|*!*>@<host|server> [V<protocol_version>] 	See RFC
class RPL_TRACESERVER : public IRPL {
  public:
	RPL_TRACESERVER();
	virtual ~RPL_TRACESERVER(void);
};

// nb:207
// short for:RPL_TRACESERVICE
// desc:RFC2812 	Service <class> <name> <type> <active_type> 	See RFC
class RPL_TRACESERVICE : public IRPL {
  public:
	RPL_TRACESERVICE();
	virtual ~RPL_TRACESERVICE(void);
};

// nb:208
// short for:RPL_TRACENEWTYPE
// desc:RFC1459 	<newtype> 0 <client_name> 	See RFC
class RPL_TRACENEWTYPE : public IRPL {
  public:
	RPL_TRACENEWTYPE();
	virtual ~RPL_TRACENEWTYPE(void);
};

// nb:209
// short for:RPL_TRACECLASS
// desc:RFC2812 	Class <class> <count> 	See RFC
class RPL_TRACECLASS : public IRPL {
  public:
	RPL_TRACECLASS();
	virtual ~RPL_TRACECLASS(void);
};

// nb:210
// short for:RPL_TRACERECONNECT
// desc:RFC2812
class RPL_TRACERECONNECT : public IRPL {
  public:
	RPL_TRACERECONNECT();
	virtual ~RPL_TRACERECONNECT(void);
};

// nb:211
// short for:RPL_STATSLINKINFO
// desc:RFC1459 	<linkname> <sendq> <sent_msgs> <sent_bytes> <recvd_msgs>
// <rcvd_bytes> <time_open> 	Reply to STATS (See RFC)
class RPL_STATSLINKINFO : public IRPL {
  public:
	RPL_STATSLINKINFO();
	virtual ~RPL_STATSLINKINFO(void);
};

// nb:212
// short for:RPL_STATSCOMMANDS
// desc:RFC1459 	<command> <count> [<byte_count> <remote_count>] 	Reply to
// STATS (See RFC)
class RPL_STATSCOMMANDS : public IRPL {
  public:
	RPL_STATSCOMMANDS();
	virtual ~RPL_STATSCOMMANDS(void);
};

// nb:213
// short for:RPL_STATSCLINE
// desc:RFC1459 	C <host> * <name> <port> <class> 	Reply to STATS (See RFC)
class RPL_STATSCLINE : public IRPL {
  public:
	RPL_STATSCLINE();
	virtual ~RPL_STATSCLINE(void);
};

// nb:214
// short for:RPL_STATSNLINE
// desc:RFC1459 	N <host> * <name> <port> <class> 	Reply to STATS (See
// RFC), Also known as RPL_STATSOLDNLINE (ircu, Unreal)
class RPL_STATSNLINE : public IRPL {
  public:
	RPL_STATSNLINE();
	virtual ~RPL_STATSNLINE(void);
};

// nb:215
// short for:RPL_STATSILINE
// desc:RFC1459 	I <host> * <host> <port> <class> 	Reply to STATS (See RFC)
class RPL_STATSILINE : public IRPL {
  public:
	RPL_STATSILINE();
	virtual ~RPL_STATSILINE(void);
};

// nb:216
// short for:RPL_STATSKLINE
// desc:RFC1459 	K <host> * <username> <port> <class> 	Reply to STATS (See
// RFC)
class RPL_STATSKLINE : public IRPL {
  public:
	RPL_STATSKLINE();
	virtual ~RPL_STATSKLINE(void);
};

// nb:217
// short for:RPL_STATSQLINE
// desc:RFC1459
class RPL_STATSQLINE : public IRPL {
  public:
	RPL_STATSQLINE();
	virtual ~RPL_STATSQLINE(void);
};

// other ref: nb:217 	short for:RPL_STATSPLINE 	desc:ircu

// nb:218
// short for:RPL_STATSYLINE
// desc:RFC1459 	Y <class> <ping_freq> <connect_freq> <max_sendq> 	Reply to
// STATS (See RFC)
class RPL_STATSYLINE : public IRPL {
  public:
	RPL_STATSYLINE();
	virtual ~RPL_STATSYLINE(void);
};

// nb:219
// short for:RPL_ENDOFSTATS
// desc:RFC1459 	<query> :<info> 	End of RPL_STATS* list.
class RPL_ENDOFSTATS : public IRPL {
  public:
	RPL_ENDOFSTATS();
	virtual ~RPL_ENDOFSTATS(void);
};

// nb:221
// short for:RPL_UMODEIS
// desc:RFC1459 	<user_modes> [<user_mode_params>] 	Information about a
// user's own modes. Some daemons have extended the mode command and certain
// modes take parameters (like channel modes).
class RPL_UMODEIS : public IRPL {
  public:
	RPL_UMODEIS(const std::string &modes);
	virtual ~RPL_UMODEIS(void);
};

// Seems to be unused / non-standard
// // nb:231
// // short for:RPL_SERVICEINFO
// // desc:RFC1459
// class RPL_SERVICEINFO : public IRPL {
//   public:
// 	RPL_SERVICEINFO();
// 	virtual ~RPL_SERVICEINFO(void);
// };
// // nb:232
// // short for:RPL_ENDOFSERVICES
// // desc:RFC1459
// class RPL_ENDOFSERVICES : public IRPL {
//   public:
// 	RPL_ENDOFSERVICES();
// 	virtual ~RPL_ENDOFSERVICES(void);
// };
// // nb:233
// // short for:RPL_SERVICE
// // desc:RFC1459
// class RPL_SERVICE : public IRPL {
//   public:
// 	RPL_SERVICE();
// 	virtual ~RPL_SERVICE(void);
// };

// nb:234
// short for:RPL_SERVLIST
// desc:RFC2812 	<name> <server> <mask> <type> <hopcount> <info> 	A
// service entry in the service list
class RPL_SERVLIST : public IRPL {
  public:
	RPL_SERVLIST();
	virtual ~RPL_SERVLIST(void);
};

// nb:235
// short for:RPL_SERVLISTEND
// desc:RFC2812 	<mask> <type> :<info> 	Termination of an RPL_SERVLIST list
class RPL_SERVLISTEND : public IRPL {
  public:
	RPL_SERVLISTEND();
	virtual ~RPL_SERVLISTEND(void);
};

// nb:240
// short for:RPL_STATSVLINE
// desc:RFC2812
class RPL_STATSVLINE : public IRPL {
  public:
	RPL_STATSVLINE();
	virtual ~RPL_STATSVLINE(void);
};

// nb:241
// short for:RPL_STATSLLINE
// desc:RFC1459 	L <hostmask> * <servername> <maxdepth> 	Reply to STATS (See
// RFC)
class RPL_STATSLLINE : public IRPL {
  public:
	RPL_STATSLLINE();
	virtual ~RPL_STATSLLINE(void);
};

// nb:242
// short for:RPL_STATSUPTIME
// desc:RFC1459 	:Server Up <days> days <hours>:<minutes>:<seconds> 	Reply to
// STATS (See RFC)
class RPL_STATSUPTIME : public IRPL {
  public:
	RPL_STATSUPTIME();
	virtual ~RPL_STATSUPTIME(void);
};

// nb:243
// short for:RPL_STATSOLINE
// desc:RFC1459 	O <hostmask> * <nick> [:<info>] 	Reply to STATS (See
// RFC); The info field is an extension found in some IRC daemons, which returns
// info such as an e-mail address or the name/job of an operator
class RPL_STATSOLINE : public IRPL {
  public:
	RPL_STATSOLINE();
	virtual ~RPL_STATSOLINE(void);
};

// nb:244
// short for:RPL_STATSHLINE
// desc:RFC1459 	H <hostmask> * <servername> 	Reply to STATS (See RFC)
class RPL_STATSHLINE : public IRPL {
  public:
	RPL_STATSHLINE();
	virtual ~RPL_STATSHLINE(void);
};

// nb:246
// short for:RPL_STATSPING
// desc:RFC2812
class RPL_STATSPING : public IRPL {
  public:
	RPL_STATSPING();
	virtual ~RPL_STATSPING(void);
};

// nb:247
// short for:RPL_STATSBLINE
// desc:RFC2812
class RPL_STATSBLINE : public IRPL {
  public:
	RPL_STATSBLINE();
	virtual ~RPL_STATSBLINE(void);
};

// nb:249
// short for:RPL_STATSULINE
// desc:Extension to RFC1459?
class RPL_STATSULINE : public IRPL {
  public:
	RPL_STATSULINE();
	virtual ~RPL_STATSULINE(void);
};

// nb:250
// short for:RPL_STATSDLINE
// desc:RFC2812
class RPL_STATSDLINE : public IRPL {
  public:
	RPL_STATSDLINE();
	virtual ~RPL_STATSDLINE(void);
};

// nb:251
// short for:RPL_LUSERCLIENT
// desc:RFC1459 	:There are <int> users and <int> invisible on <int> servers
// Reply to LUSERS command, other versions exist (eg. RFC2812); Text may vary.
class RPL_LUSERCLIENT : public IRPL {
  public:
	RPL_LUSERCLIENT(int nb_users, int nb_invisible, int nb_servers);
	virtual ~RPL_LUSERCLIENT(void);
};

// nb:252
// short for:RPL_LUSEROP
// desc:RFC1459 	<int> :<info> 	Reply to LUSERS command - Number of IRC
// operators online
class RPL_LUSEROP : public IRPL {
  public:
	RPL_LUSEROP(int nb_ops);
	virtual ~RPL_LUSEROP(void);
};

// nb:253
// short for:RPL_LUSERUNKNOWN
// desc:RFC1459 	<int> :<info> 	Reply to LUSERS command - Number of
// unknown/unregistered connections
class RPL_LUSERUNKNOWN : public IRPL {
  public:
	RPL_LUSERUNKNOWN(int nb_user_unk);
	virtual ~RPL_LUSERUNKNOWN(void);
};

// nb:254
// short for:RPL_LUSERCHANNELS
// desc:RFC1459 	<int> :<info> 	Reply to LUSERS command - Number of channels
// formed
class RPL_LUSERCHANNELS : public IRPL {
  public:
	RPL_LUSERCHANNELS(int nb_chan);
	virtual ~RPL_LUSERCHANNELS(void);
};

// nb:255
// short for:RPL_LUSERME
// desc:RFC1459 	:I have <int> clients and <int> servers 	Reply to LUSERS
// command - Information about local connections; Text may vary.
class RPL_LUSERME : public IRPL {
  public:
	RPL_LUSERME(int nb_clients, int nb_server);
	virtual ~RPL_LUSERME(void);
};

// nb:256
// short for:RPL_ADMINME
// desc:RFC1459 	<server> :<info> 	Start of an RPL_ADMIN* reply. In
// practise, the server parameter is often never given, and instead the info
// field contains the text 'Administrative info about <server>'. Newer daemons
// seem to follow the RFC and output the server's hostname in the 'server'
// parameter, but also output the server name in the text as per traditional
// daemons.
class RPL_ADMINME : public IRPL {
  public:
	RPL_ADMINME();
	virtual ~RPL_ADMINME(void);
};

// nb:257
// short for:RPL_ADMINLOC1
// desc:RFC1459 	:<admin_location> 	Reply to ADMIN command (Location, first
// line)
class RPL_ADMINLOC : public IRPL {
  public:
	RPL_ADMINLOC();
	virtual ~RPL_ADMINLOC(void);
};

// nb:258
// short for:RPL_ADMINLOC2
// desc:RFC1459 	:<admin_location> 	Reply to ADMIN command (Location, second
// line)
class RPL_ADMINLOC2 : public IRPL {
  public:
	RPL_ADMINLOC2();
	virtual ~RPL_ADMINLOC2(void);
};

// nb:259
// short for:RPL_ADMINEMAIL
// desc:RFC1459 	:<email_address> 	Reply to ADMIN command (E-mail address
// of administrator)
class RPL_ADMINEMAIL : public IRPL {
  public:
	RPL_ADMINEMAIL();
	virtual ~RPL_ADMINEMAIL(void);
};

// nb:260 - not in RFC

// nb:261
// short for:RPL_TRACELOG
// desc:RFC1459 	File <logfile> <debug_level> 	See RFC
class RPL_TRACELOG : public IRPL {
  public:
	RPL_TRACELOG();
	virtual ~RPL_TRACELOG(void);
};

// nb:262
// short for:RPL_TRACEPING
// desc:Extension to RFC1459?
class RPL_TRACEPING : public IRPL {
  public:
	RPL_TRACEPING();
	virtual ~RPL_TRACEPING(void);
};

// nb:262
// short for:RPL_TRACEEND
// desc:RFC2812 	<server_name> <version>[.<debug_level>] :<info> 	Used to
// terminate a list of RPL_TRACE* replies
class RPL_TRACEEND : public IRPL {
  public:
	RPL_TRACEEND();
	virtual ~RPL_TRACEEND(void);
};

// nb:263
// short for:RPL_TRYAGAIN
// desc:RFC2812 	<command> :<info> 	When a server drops a command without
// processing it, it MUST use this reply. Also known as RPL_LOAD_THROTTLED and
// RPL_LOAD2HI, I'm presuming they do the same thing.
class RPL_TRYAGAIN : public IRPL {
  public:
	RPL_TRYAGAIN(const std::string &command, const std::string &info);
	virtual ~RPL_TRYAGAIN(void);
};

// nb:300
// short for:RPL_NONE
// desc:RFC1459 		Dummy reply, supposedly only used for debugging/testing
// new features, however has appeared in production daemons.
class RPL_NONE : public IRPL {
  public:
	RPL_NONE();
	virtual ~RPL_NONE(void);
};

// nb:301
// short for:RPL_AWAY
// desc:RFC1459 	<nick> :<message> 	Used in reply to a command directed at a
// user who is marked as away
class RPL_AWAY : public IRPL {
  public:
	RPL_AWAY(const std::string &nick, const std::string &away_msg);
	virtual ~RPL_AWAY(void);
};

// nb:302
// short for:RPL_USERHOST
// desc:RFC1459 	:*1<reply> *( ' ' <reply> ) 	Reply used by USERHOST (see
// RFC)
class RPL_USERHOST : public IRPL {
  public:
	RPL_USERHOST();
	virtual ~RPL_USERHOST(void);
};

// nb:303
// short for:RPL_ISON
// desc:RFC1459 	:*1<nick> *( ' ' <nick> ) 	Reply to the ISON command (see
// RFC)
class RPL_ISON : public IRPL {
  public:
	RPL_ISON();
	virtual ~RPL_ISON(void);
};

// 304 : seems to be absent from RFC

// nb:305
// short for:RPL_UNAWAY
// desc:RFC1459 	:<info> 	Reply from AWAY when no longer marked as away
class RPL_UNAWAY : public IRPL {
  public:
	RPL_UNAWAY();
	virtual ~RPL_UNAWAY(void);
};

// nb:306
// short for:RPL_NOWAWAY
// desc:RFC1459 	:<info> 	Reply from AWAY when marked away
class RPL_NOWAWAY : public IRPL {
  public:
	RPL_NOWAWAY();
	virtual ~RPL_NOWAWAY(void);
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

// nb:313
// short for:RPL_WHOISOPERATOR
// desc:RFC1459 	<nick> :<privileges> 	Reply to WHOIS - User has IRC
// Operator privileges
class RPL_WHOISOPERATOR : public IRPL {
  public:
	RPL_WHOISOPERATOR(const std::string &nick, const std::string &privilege);
	virtual ~RPL_WHOISOPERATOR(void);
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

// nb:315
// short for:RPL_ENDOFWHO
// desc:RFC1459 	<name> :<info> 	Used to terminate a list of RPL_WHOREPLY
// replies
class RPL_ENDOFWHO : public IRPL {
  public:
	RPL_ENDOFWHO(const std::string &name, const std::string &info);
	virtual ~RPL_ENDOFWHO(void);
};

// nb:316
// short for:RPL_WHOISCHANOP
// desc:RFC1459
class RPL_WHOISCHANOP : public IRPL {
  public:
	RPL_WHOISCHANOP();
	virtual ~RPL_WHOISCHANOP(void);
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
	RPL_ENDOFWHOIS(const std::string &nick, const std::string &info = "End of /WHOIS list");
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

// nb:321
// short for:RPL_LISTSTART
// desc:RFC1459 	Channels :Users Name 	Channel list - Header
class RPL_LISTSTART : public IRPL {
  public:
	RPL_LISTSTART();
	virtual ~RPL_LISTSTART(void);
};

// nb:322
// short for:RPL_LIST
// desc:RFC1459 	<channel> <#_visible> :<topic> 	Channel list - A channel
class RPL_LIST : public IRPL {
  public:
	RPL_LIST();
	virtual ~RPL_LIST(void);
};

// nb:323
// short for:RPL_LISTEND
// desc:RFC1459 	:<info> 	Channel list - End of list
class RPL_LISTEND : public IRPL {
  public:
	RPL_LISTEND();
	virtual ~RPL_LISTEND(void);
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

// nb:325
// short for:RPL_UNIQOPIS
// desc:RFC2812 	<channel> <nickname>
class RPL_UNIQOPIS : public IRPL {
  public:
	RPL_UNIQOPIS();
	virtual ~RPL_UNIQOPIS(void);
};

// nb:329
// short for:RPL_CREATIONTIME
// desc:RFC2812		<channel> <timestamp>
// Indicates the time the channel was created. The timestamp is in
// seconds since the epoch (1970)

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
	RPL_INVITING(const std::string &nick, const std::string &ch_name);
	virtual ~RPL_INVITING(void);
};

// nb:342
// short for:RPL_SUMMONING
// desc:RFC1459 	<user> :<info> 	Returned by a server answering a SUMMON
// message to indicate that it is summoning that user
class RPL_SUMMONING : public IRPL {
  public:
	RPL_SUMMONING(const std::string &u, const std::string &info);
	virtual ~RPL_SUMMONING(void);
};

// // nb:345
// // short for:RPL_INVITED
// // desc:GameSurge 	<channel> <user being invited> <user issuing invite>
// :<user
// // being invited> has been invited by <user issuing invite> 	Sent to users on
// // a channel when an INVITE command has been issued
// class RPL_INVITED : public IRPL {
//   public:
// 	RPL_INVITED();
// 	virtual ~RPL_INVITED(void);
// };

// // nb:346
// // short for:RPL_INVITELIST
// // desc:RFC2812 	<channel> <invitemask> 	An invite mask for the invite mask
// // list
// class RPL_INVITELIST : public IRPL {
//   public:
// 	RPL_INVITELIST();
// 	virtual ~RPL_INVITELIST(void);
// };

// // nb:347
// // short for:RPL_ENDOFINVITELIST
// // desc:RFC2812 	<channel> :<info> 	Termination of an RPL_INVITELIST list
// class RPL_ENDOFINVITELIST : public IRPL {
//   public:
// 	RPL_ENDOFINVITELIST();
// 	virtual ~RPL_ENDOFINVITELIST(void);
// };

// nb:348
// short for:RPL_EXCEPTLIST
// desc:RFC2812 	<channel> <exceptionmask> 	An exception mask for the
// exception mask list. Also known as RPL_EXLIST (Unreal, Ultimate)
class RPL_EXCEPTLIST : public IRPL {
  public:
	RPL_EXCEPTLIST(const std::string &chn, const std::string &emsk);
	virtual ~RPL_EXCEPTLIST(void);
};

// nb:349
// short for:RPL_ENDOFEXCEPTLIST
// desc:RFC2812 	<channel> :<info> 	Termination of an RPL_EXCEPTLIST list.
// Also known as RPL_ENDOFEXLIST (Unreal, Ultimate)
class RPL_ENDOFEXCEPTLIST : public IRPL {
  public:
	RPL_ENDOFEXCEPTLIST(const std::string &ch, const std::string &info);
	virtual ~RPL_ENDOFEXCEPTLIST(void);
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

// nb:352
// short for:RPL_WHOREPLY
// desc:RFC1459 	<channel> <user> <host> <server> <nick> <H|G>[*][@|+]
// :<hopcount> <real_name> 	Reply to vanilla WHO (See RFC). This format can be
// very different if the 'WHOX' version of the command is used (see ircu).
class RPL_WHOREPLY : public IRPL {
  public:
	RPL_WHOREPLY();
	virtual ~RPL_WHOREPLY(void);
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

// nb:361
// short for:RPL_KILLDONE
// desc:RFC1459
class RPL_KILLDONE : public IRPL {
  public:
	RPL_KILLDONE();
	virtual ~RPL_KILLDONE(void);
};

// nb:362
// short for:RPL_CLOSING
// desc:RFC1459
class RPL_CLOSING : public IRPL {
  public:
	RPL_CLOSING();
	virtual ~RPL_CLOSING(void);
};

// nb:363
// short for:RPL_CLOSEEND
// desc:RFC1459
class RPL_CLOSEEND : public IRPL {
  public:
	RPL_CLOSEEND();
	virtual ~RPL_CLOSEEND(void);
};

// nb:364
// short for:RPL_LINKS
// desc:RFC1459 	<mask> <server> :<hopcount> <server_info> 	Reply to the
// LINKS command
class RPL_LINKS : public IRPL {
  public:
	RPL_LINKS();
	virtual ~RPL_LINKS(void);
};

// nb:365
// short for:RPL_ENDOFLINKS
// desc:RFC1459 	<mask> :<info> 	Termination of an RPL_LINKS list
class RPL_ENDOFLINKS : public IRPL {
  public:
	RPL_ENDOFLINKS(const std::string &msk, const std::string &info);
	virtual ~RPL_ENDOFLINKS(void);
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

// nb:367
// short for:RPL_BANLIST
// desc:RFC1459 	<channel> <banid> [<time_left> :<reason>] 	A ban-list item
// (See RFC); <time left> and <reason> are additions used by KineIRCd
class RPL_BANLIST : public IRPL {
  public:
	RPL_BANLIST();
	virtual ~RPL_BANLIST(void);
};

// nb:368
// short for:RPL_ENDOFBANLIST
// desc:RFC1459 	<channel> :<info> 	Termination of an RPL_BANLIST list
class RPL_ENDOFBANLIST : public IRPL {
  public:
	RPL_ENDOFBANLIST(const std::string &channel, const std::string &info);
	virtual ~RPL_ENDOFBANLIST(void);
};

// nb:369
// short for:RPL_ENDOFWHOWAS
// desc:RFC1459 	<nick> :<info> 	Reply to WHOWAS - End of list
class RPL_ENDOFWHOWAS : public IRPL {
  public:
	RPL_ENDOFWHOWAS(const std::string &nick, const std::string &info = "End of /WHOWAS");
	virtual ~RPL_ENDOFWHOWAS(void);
};

// nb:371
// short for:RPL_INFO
// desc:RFC1459 	:<string> 	Reply to INFO
class RPL_INFO : public IRPL {
  public:
	RPL_INFO(const std::string &string);
	virtual ~RPL_INFO(void);
};

// nb:372
// short for:RPL_MOTD
// desc:RFC1459 	:- <string> 	Reply to MOTD
class RPL_MOTD : public IRPL {
  public:
	RPL_MOTD(const std::string &dword);
	virtual ~RPL_MOTD(void);
};

// nb:373
// short for:RPL_INFOSTART
// desc:RFC1459
class RPL_INFOSTART : public IRPL {
  public:
	RPL_INFOSTART();
	virtual ~RPL_INFOSTART(void);
};

// nb:374
// short for:RPL_ENDOFINFO
// desc:RFC1459 	:<info> 	Termination of an RPL_INFO list
class RPL_ENDOFINFO : public IRPL {
  public:
	RPL_ENDOFINFO(const std::string &info);
	virtual ~RPL_ENDOFINFO(void);
};

// nb:375
// short for:RPL_MOTDSTART
// desc:RFC1459 	:- <server> Message of the day - 	Start of an RPL_MOTD
// list
class RPL_MOTDSTART : public IRPL {
  public:
	RPL_MOTDSTART();
	virtual ~RPL_MOTDSTART(void);
};

// nb:376
// short for:RPL_ENDOFMOTD
// desc:RFC1459 	:<info> 	Termination of an RPL_MOTD list
class RPL_ENDOFMOTD : public IRPL {
  public:
	RPL_ENDOFMOTD();
	virtual ~RPL_ENDOFMOTD(void);
};

// nb:381
// short for:RPL_YOUREOPER
// desc:RFC1459 	:<info> 	Successful reply from OPER
class RPL_YOUREOPER : public IRPL {
  public:
	RPL_YOUREOPER();
	virtual ~RPL_YOUREOPER(void);
};

// nb:382
// short for:RPL_REHASHING
// desc:RFC1459 	<config_file> :<info> 	Successful reply from REHASH
class RPL_REHASHING : public IRPL {
  public:
	RPL_REHASHING(const std::string &cfile, const std::string &info);
	virtual ~RPL_REHASHING(void);
};

// nb:383
// short for:RPL_YOURESERVICE
// desc:RFC2812 	:You are service <service_name> 	Sent upon successful
// registration of a service
class RPL_YOURESERVICE : public IRPL {
  public:
	RPL_YOURESERVICE(const std::string sername);
	virtual ~RPL_YOURESERVICE(void);
};

// // nb:384
// // short for:RPL_MYPORTIS
// // desc:RFC1459
// class RPL_MYPORTIS : public IRPL {
//   public:
// 	RPL_MYPORTIS();
// 	virtual ~RPL_MYPORTIS(void);
// };

// nb:391
// short for:RPL_TIME
// desc:RFC1459 	<server> :<time string> 	Response to the TIME command.
// The string format may vary greatly. Also see #679.
class RPL_TIME : public IRPL {
  public:
	RPL_TIME(const std::string &sname, const std::string &time);
	virtual ~RPL_TIME(void);
};

// nb:392
// short for:RPL_USERSSTART
// desc:RFC1459 	:UserID Terminal Host 	Start of an RPL_USERS list
class RPL_USERSSTART : public IRPL {
  public:
	RPL_USERSSTART(const std::string &uid, const std::string &th);
	virtual ~RPL_USERSSTART(void);
};

// nb:393
// short for:RPL_USERS
// desc:RFC1459 	:<username> <ttyline> <hostname> 	Response to the USERS
// command (See RFC)
class RPL_USERS : public IRPL {
  public:
	RPL_USERS(const std::string &usr_name, const std::string &ttyline,
			  const std::string &hname);
	virtual ~RPL_USERS(void);
};

// nb:394
// short for:RPL_ENDOFUSERS
// desc:RFC1459 	:<info> 	Termination of an RPL_USERS list
class RPL_ENDOFUSERS : public IRPL {
  public:
	RPL_ENDOFUSERS(const std::string &inf);
	RPL_ENDOFUSERS();
	virtual ~RPL_ENDOFUSERS(void);
};

// nb:395
// short for:RPL_NOUSERS
// desc:RFC1459 	:<info> 	Reply to USERS when nobody is logged in
class RPL_NOUSERS : public IRPL {
  public:
	RPL_NOUSERS(const std::string &inf);
	virtual ~RPL_NOUSERS(void);
};
