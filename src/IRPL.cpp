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

RPL_WELCOME::RPL_WELCOME(const std::string &nick, const std::string &c_hostname)
	: IRPL(001, "Welcome to the Internet Relay Network " + nick + "!" + nick +
					"@" + c_hostname) {};
RPL_WELCOME::~RPL_WELCOME(void) {};

RPL_YOURHOST::RPL_YOURHOST()
	: IRPL(002, "Your host is " SERVER_NAME_DFLT ", running version 1.0") {};
RPL_YOURHOST::~RPL_YOURHOST(void) {};

RPL_CREATED::RPL_CREATED()
	: IRPL(003, "This server was created by " IRC_SERVER_AUTHORS " and is "
				"running on a custom IRC server implementation "
				"(version " IRC_SERVER_VERSION ").") {};
RPL_CREATED::~RPL_CREATED(void) {};

RPL_MYINFO::RPL_MYINFO()
	: IRPL(004, SERVER_NAME_DFLT
		   " " IRC_SERVER_VERSION
		   " " /* available user modes   available chanel modes*/) {}
RPL_MYINFO::~RPL_MYINFO() {};

RPL_BOUNCE::RPL_BOUNCE()
	: IRPL(005, "...") {
		  // TODO:
		  // implement when server is multi-server capable
		  //	- pick a server not full in list of connected server,
		  //	- set _s to "Try server <server_name>, port <port_number>"
		  //	end.
	  };
RPL_BOUNCE::~RPL_BOUNCE() {};

RPL_TRACELINK::RPL_TRACELINK() : IRPL(200, "...") {
	// TODO:
	// server stuff.
	// didnt really get it.
}
RPL_TRACELINK::~RPL_TRACELINK() {};

RPL_TRACECONNECTING::RPL_TRACECONNECTING() : IRPL(201, "...") {
	// TODO:
	// server stuff.
	// didnt really get it.
}
RPL_TRACECONNECTING::~RPL_TRACECONNECTING(void) {}

// nb:202
// short for:RPL_TRACEHANDSHAKE
// desc:RFC1459 	H.S. <class> <server> 	See RFC
RPL_TRACEHANDSHAKE::RPL_TRACEHANDSHAKE() : IRPL(202, "...") {
	// TODO:
	// server stuff.
	// didnt really get it.
}
RPL_TRACEHANDSHAKE::~RPL_TRACEHANDSHAKE(void) {};

// nb:203
// short for:RPL_TRACEUNKNOWN
// desc:RFC1459 	???? <class> [<connection_address>] 	See RFC
RPL_TRACEUNKNOWN::RPL_TRACEUNKNOWN() : IRPL(203, "...") {
	// TODO:
	// server stuff.
	// didnt really get it.
}
RPL_TRACEUNKNOWN::~RPL_TRACEUNKNOWN(void) {};

// nb:204
// short for:RPL_TRACEOPERATOR
// desc:RFC1459 	Oper <class> <nick> 	See RFC
RPL_TRACEOPERATOR::RPL_TRACEOPERATOR() : IRPL(204, "...") {
	// TODO:
	// server stuff.
	// didnt really get it.
}
RPL_TRACEOPERATOR::~RPL_TRACEOPERATOR(void) {};

// nb:205
// short for:RPL_TRACEUSER
// desc:RFC1459 	User <class> <nick> 	See RFC
RPL_TRACEUSER::RPL_TRACEUSER() : IRPL(205, "...") {
	// TODO:
	// server stuff.
	// didnt really get it.
}
RPL_TRACEUSER::~RPL_TRACEUSER(void) {};

// nb:206
// short for:RPL_TRACESERVER
// desc:RFC1459 	Serv <class> <int>S <int>C <server>
// <nick!user|*!*>@<host|server> [V<protocol_version>] 	See RFC
RPL_TRACESERVER::RPL_TRACESERVER() : IRPL(206, "...") {
	// TODO:
	// server stuff.
	// didnt really get it.
}
RPL_TRACESERVER::~RPL_TRACESERVER(void) {};

// nb:207
// short for:RPL_TRACESERVICE
// desc:RFC2812 	Service <class> <name> <type> <active_type> 	See RFC
RPL_TRACESERVICE::RPL_TRACESERVICE() : IRPL(207, "...") {
	// TODO:
	// server stuff.
	// didnt really get it.
}
RPL_TRACESERVICE::~RPL_TRACESERVICE(void) {};

// nb:208
// short for:RPL_TRACENEWTYPE
// desc:RFC1459 	<newtype> 0 <client_name> 	See RFC
RPL_TRACENEWTYPE::RPL_TRACENEWTYPE() : IRPL(208, "...") {
	// TODO:
	// server stuff.
	// didnt really get it.
}
RPL_TRACENEWTYPE::~RPL_TRACENEWTYPE(void) {};

// nb:209
// short for:RPL_TRACECLASS
// desc:RFC2812 	Class <class> <count> 	See RFC
RPL_TRACECLASS::RPL_TRACECLASS() : IRPL(209, "...") {
	// TODO:
	// server stuff.
	// didnt really get it.
}
RPL_TRACECLASS::~RPL_TRACECLASS(void) {};

// nb:210
// short for:RPL_TRACERECONNECT
// desc:RFC2812
RPL_TRACERECONNECT::RPL_TRACERECONNECT() : IRPL(210, "...") {
	// TODO:
	// server stuff.
	// didnt really get it.
}
RPL_TRACERECONNECT::~RPL_TRACERECONNECT(void) {};

// nb:211
// short for:RPL_STATSLINKINFO
// desc:RFC1459 	<linkname> <sendq> <sent_msgs> <sent_bytes> <recvd_msgs>
// <rcvd_bytes> <time_open> 	Reply to STATS (See RFC)
RPL_STATSLINKINFO::RPL_STATSLINKINFO() : IRPL(212, "...") {
	// TODO:
	// server stuff.
	// didnt really get it.
}
RPL_STATSLINKINFO::~RPL_STATSLINKINFO(void) {};

// nb:212
// short for:RPL_STATSCOMMANDS
// desc:RFC1459 	<command> <count> [<byte_count> <remote_count>] 	Reply to
// STATS (See RFC)
RPL_STATSCOMMANDS::RPL_STATSCOMMANDS() : IRPL(212, "...") {
	// TODO:
	// server stuff.
	// didnt really get it.
}
RPL_STATSCOMMANDS::~RPL_STATSCOMMANDS(void) {};

// nb:213
// short for:RPL_STATSCLINE
// desc:RFC1459 	C <host> * <name> <port> <class> 	Reply to STATS (See RFC)
RPL_STATSCLINE::RPL_STATSCLINE() : IRPL(213, "...") {
	// TODO:
	// server stuff.
	// didnt really get it.
}
RPL_STATSCLINE::~RPL_STATSCLINE(void) {};

// nb:214
// short for:RPL_STATSNLINE
// desc:RFC1459 	N <host> * <name> <port> <class> 	Reply to STATS (See
// RFC), Also known as RPL_STATSOLDNLINE (ircu, Unreal)
RPL_STATSNLINE::RPL_STATSNLINE() : IRPL(214, "...") {
	// TODO:
	// server stuff.
	// didnt really get it.
}
RPL_STATSNLINE::~RPL_STATSNLINE(void) {};

// nb:215
// short for:RPL_STATSILINE
// desc:RFC1459 	I <host> * <host> <port> <class> 	Reply to STATS (See RFC)
RPL_STATSILINE::RPL_STATSILINE() : IRPL(215, "...") {
	// TODO:
	// server stuff.
	// didnt really get it.
}
RPL_STATSILINE::~RPL_STATSILINE(void) {};

// nb:216
// short for:RPL_STATSKLINE
// desc:RFC1459 	K <host> * <username> <port> <class> 	Reply to STATS (See
// RFC)
RPL_STATSKLINE::RPL_STATSKLINE() : IRPL(216, "...") {
	// TODO:
	// server stuff.
	// didnt really get it.
}
RPL_STATSKLINE::~RPL_STATSKLINE(void) {};

// nb:217
// short for:RPL_STATSQLINE
// desc:RFC1459
RPL_STATSQLINE::RPL_STATSQLINE() : IRPL(217, "...") {
	// TODO:
	// server stuff.
	// didnt really get it.
}
RPL_STATSQLINE::~RPL_STATSQLINE(void) {};

// other ref: nb:217 	short for:RPL_STATSPLINE 	desc:ircu

// nb:218
// short for:RPL_STATSYLINE
// desc:RFC1459 	Y <class> <ping_freq> <connect_freq> <max_sendq> 	Reply to
// STATS (See RFC)
RPL_STATSYLINE::RPL_STATSYLINE() : IRPL(218, "...") {
	// TODO:
	// server stuff.
	// didnt really get it.
}
RPL_STATSYLINE::~RPL_STATSYLINE(void) {};

// nb:219
// short for:RPL_ENDOFSTATS
// desc:RFC1459 	<query> :<info> 	End of RPL_STATS* list.
RPL_ENDOFSTATS::RPL_ENDOFSTATS() : IRPL(219, "...") {
	// TODO:
	// server stuff.
	// didnt really get it.
}
RPL_ENDOFSTATS::~RPL_ENDOFSTATS(void) {};

RPL_UMODEIS::RPL_UMODEIS(const std::string &modes) : IRPL(221, modes) {}
RPL_UMODEIS::~RPL_UMODEIS(void) {};

// might be useless - no server to server communications are needed for irc
RPL_SERVLIST::RPL_SERVLIST() : IRPL(234, "...") {};
RPL_SERVLIST::~RPL_SERVLIST() {};

RPL_SERVLISTEND::RPL_SERVLISTEND(void) : IRPL(235, "End of service listing") {};
RPL_SERVLISTEND::~RPL_SERVLISTEND(void) {};

// nb:240
// short for:RPL_STATSVLINE
// desc:RFC2812
RPL_STATSVLINE::RPL_STATSVLINE() : IRPL(240, "...") {};
RPL_STATSVLINE::~RPL_STATSVLINE(void) {};

// nb:241
// short for:RPL_STATSLLINE::RPL_STATSLLINE
// desc:RFC1459 	L <hostmask> * <servername> <maxdepth> 	Reply to STATS (See
// RFC)
RPL_STATSLLINE::RPL_STATSLLINE() : IRPL(241, "...") {};
RPL_STATSLLINE::~RPL_STATSLLINE(void) {};

// nb:242
// short for:RPL_STATSUPTIME::RPL_STATSUPTIME
// desc:RFC1459 	:Server Up <days> days <hours>:<minutes>:<seconds> 	Reply to
// STATS (See RFC)
RPL_STATSUPTIME::RPL_STATSUPTIME() : IRPL(242, "...") {};
RPL_STATSUPTIME::~RPL_STATSUPTIME(void) {};

// nb:243
// short for:RPL_STATSOLINE::RPL_STATSOLINE
// desc:RFC1459 	O <hostmask> * <nick> [:<info>] 	Reply to STATS (See
// RFC); The info field is an extension found in some IRC daemons, which returns
// info such as an e-mail address or the name/job of an operator
RPL_STATSOLINE::RPL_STATSOLINE() : IRPL(243, "...") {};
RPL_STATSOLINE::~RPL_STATSOLINE(void) {};

// nb:244
// short for:RPL_STATSHLINE::RPL_STATSHLINE
// desc:RFC1459 	H <hostmask> * <servername> 	Reply to STATS (See RFC)
RPL_STATSHLINE::RPL_STATSHLINE() : IRPL(244, "...") {};
RPL_STATSHLINE::~RPL_STATSHLINE(void) {};

// nb:246
// short for:RPL_STATSPING::RPL_STATSPING
// desc:RFC2812
RPL_STATSPING::RPL_STATSPING() : IRPL(246, "...") {};
RPL_STATSPING::~RPL_STATSPING(void) {};

// nb:247
// short for:RPL_STATSBLINE::RPL_STATSBLINE
// desc:RFC2812
RPL_STATSBLINE::RPL_STATSBLINE() : IRPL(247, "...") {};
RPL_STATSBLINE::~RPL_STATSBLINE(void) {};

// nb:249
// short for:RPL_STATSULINE::RPL_STATSULINE
// desc:Extension to RFC1459?
RPL_STATSULINE::RPL_STATSULINE() : IRPL(249, "...") {};
RPL_STATSULINE::~RPL_STATSULINE(void) {};

// nb:250
// short for:RPL_STATSDLINE::RPL_STATSDLINE
// desc:RFC2812
RPL_STATSDLINE::RPL_STATSDLINE() : IRPL(250, "...") {};
RPL_STATSDLINE::~RPL_STATSDLINE(void) {};

// nb:251
// short for:RPL_LUSERCLIENT
// desc:RFC1459 	:There are <int> users and <int> invisible on <int> servers
// Reply to LUSERS command, other versions exist (eg. RFC2812); Text may vary.
RPL_LUSERCLIENT::RPL_LUSERCLIENT(int nb_users, int nb_invisible, int nb_servers)
	: IRPL(251, "There are <int> users and <int> invisible on <int> servers") {
	IRPL::string = "There are " + to_string(nb_users) + " users and " +
				   to_string(nb_invisible) + " invisible on " +
				   to_string(nb_servers) + " servers";
};
RPL_LUSERCLIENT::~RPL_LUSERCLIENT(void) {};

// nb:252
// short for:RPL_LUSEROP
// desc:RFC1459 	<int> :<info> 	Reply to LUSERS command - Number of IRC
// operators online
RPL_LUSEROP::RPL_LUSEROP(int nb_ops) : IRPL(252, "...") {
	IRPL::string = to_string(nb_ops) + " :There are " + to_string(nb_ops) +
				   " IRC operators online";
};
RPL_LUSEROP::~RPL_LUSEROP(void) {};

// nb:253
// short for:RPL_LUSERUNKNOWN
// desc:RFC1459 	<int> :<info> 	Reply to LUSERS command - Number of
// unknown/unregistered connections
RPL_LUSERUNKNOWN::RPL_LUSERUNKNOWN(int nb_user_unk) : IRPL(253, "...") {
	IRPL::string = to_string(nb_user_unk) + " :There are " +
				   to_string(nb_user_unk) + " unknown/unregistered connections";
};
RPL_LUSERUNKNOWN::~RPL_LUSERUNKNOWN(void) {};

// nb:254
// short for:RPL_LUSERCHANNELS
// desc:RFC1459 	<int> :<info> 	Reply to LUSERS command - Number of channels
// formed
RPL_LUSERCHANNELS::RPL_LUSERCHANNELS(int nb_chan) : IRPL(254, "...") {
	IRPL::string = to_string(nb_chan) + " :There are " + to_string(nb_chan) +
				   " channels formed";
};
RPL_LUSERCHANNELS::~RPL_LUSERCHANNELS(void) {};

// nb:255
// short for:RPL_LUSERME
// desc:RFC1459 	:I have <int> clients and <int> servers 	Reply to LUSERS
// command - Information about local connections; Text may vary.
RPL_LUSERME::RPL_LUSERME(int nb_clients, int nb_server) : IRPL(255, "...") {
	IRPL::string = "I have " + to_string(nb_clients) + " clients and " +
				   to_string(nb_server) + " servers";
};
RPL_LUSERME::~RPL_LUSERME(void) {};

// nb:256
// short for:RPL_ADMINME
// desc:RFC1459 	<server> :<info> 	Start of an RPL_ADMIN* reply. In
// practise, the server parameter is often never given, and instead the info
// field contains the text 'Administrative info about <server>'. Newer daemons
// seem to follow the RFC and output the server's hostname in the 'server'
// parameter, but also output the server name in the text as per traditional
// daemons.
RPL_ADMINME::RPL_ADMINME()
	: IRPL(256, "...") {
		  // TODO: implement
	  };
RPL_ADMINME::~RPL_ADMINME(void) {};

// nb:257
// short for:RPL_ADMINLOC1
// desc:RFC1459 	:<admin_location> 	Reply to ADMIN command (Location, first
// line)
RPL_ADMINLOC::RPL_ADMINLOC()
	: IRPL(257, "...") {
		  // TODO: implement
	  };
RPL_ADMINLOC::~RPL_ADMINLOC(void) {};

// nb:258
// short for:RPL_ADMINLOC2
// desc:RFC1459 	:<admin_location> 	Reply to ADMIN command (Location, second
// line)
RPL_ADMINLOC2::RPL_ADMINLOC2()
	: IRPL(258, "...") {
		  // TODO: implement
	  };
RPL_ADMINLOC2::~RPL_ADMINLOC2(void) {};

// nb:259
// short for:RPL_ADMINEMAIL
// desc:RFC1459 	:<email_address> 	Reply to ADMIN command (E-mail address
// of administrator)
RPL_ADMINEMAIL::RPL_ADMINEMAIL() : IRPL(259, ADMIN_EMAIL_DFLT) {};
RPL_ADMINEMAIL::~RPL_ADMINEMAIL(void) {};

// nb:261
// short for:RPL_TRACELOG
// desc:RFC1459 	File <logfile> <debug_level> 	See RFC
RPL_TRACELOG::RPL_TRACELOG()
	: IRPL(261, "...") {
		  // TODO: implement
	  };
RPL_TRACELOG::~RPL_TRACELOG(void) {};

// nb:262
// short for:RPL_TRACEPING
// desc:Extension to RFC1459?
RPL_TRACEPING::RPL_TRACEPING()
	: IRPL(262, "...") {
		  // TODO: implement - ping related?
	  };
RPL_TRACEPING::~RPL_TRACEPING(void) {};

// nb:262
// short for:RPL_TRACEEND
// desc:RFC2812 	<server_name> <version>[.<debug_level>] :<info> 	Used to
// terminate a list of RPL_TRACE* replies
//   code is the same as RPL_TRACEPING? might be a bug in what I read
RPL_TRACEEND::RPL_TRACEEND()
	: IRPL(262, "...") {
		  // TODO: implement
	  };
RPL_TRACEEND::~RPL_TRACEEND(void) {};

// nb:263
// short for:RPL_TRYAGAIN
// desc:RFC2812 	<command> :<info> 	When a server drops a command without
// processing it, it MUST use this reply. Also known as RPL_LOAD_THROTTLED and
// RPL_LOAD2HI, I'm presuming they do the same thing.
RPL_TRYAGAIN::RPL_TRYAGAIN(const std::string &cmd, const std::string &info)
	: IRPL(263, cmd + " :" + info) {};
RPL_TRYAGAIN::~RPL_TRYAGAIN(void) {};

// nb:300
// short for:RPL_NONE
// desc:RFC1459 		Dummy reply, supposedly only used for debugging/testing
// new features, however has appeared in production daemons.
RPL_NONE::RPL_NONE() : IRPL(300, "...") {}; // empty string
RPL_NONE::~RPL_NONE(void) {};

// nb:301
// short for:RPL_AWAY
// desc:RFC1459 	<nick> :<message> 	Used in reply to a command directed at a
// user who is marked as away
RPL_AWAY::RPL_AWAY(const std::string &nick, const std::string &away_msg)
	: IRPL(301, nick + " : " + away_msg) {};
RPL_AWAY::~RPL_AWAY(void) {};

// nb:302
// short for:RPL_USERHOST
// desc:RFC1459 	:*1<reply> *( ' ' <reply> ) 	Reply used by USERHOST (see
// RFC)
RPL_USERHOST::RPL_USERHOST()
	: IRPL(302, "...") {
		  // TODO: implement
	  };
RPL_USERHOST::~RPL_USERHOST(void) {};

// nb:303
// short for:RPL_ISON
// desc:RFC1459 	:*1<nick> *( ' ' <nick> ) 	Reply to the ISON command (see
// RFC)
RPL_ISON::RPL_ISON()
	: IRPL(303, "...") {
		  // TODO: implement
	  };
RPL_ISON::~RPL_ISON(void) {};

// nb:305
// short for:RPL_UNAWAY
// desc:RFC1459 	:<info> 	Reply from AWAY when no longer marked as away
RPL_UNAWAY::RPL_UNAWAY()
	: IRPL(305, "You are no longer marked as being away") {};
RPL_UNAWAY::~RPL_UNAWAY(void) {};

// nb:306
// short for:RPL_NOWAWAY
// desc:RFC1459 	:<info> 	Reply from AWAY when marked away
RPL_NOWAWAY::RPL_NOWAWAY() : IRPL(306, "You have been marked as being away") {};
RPL_NOWAWAY::~RPL_NOWAWAY(void) {};

// nb:311
// short for:RPL_WHOISUSER
// desc:RFC1459 	<nick> <user> <host> * :<real_name> 	Reply to WHOIS -
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
// desc:RFC1459 	<nick> <server> :<server_info> 	Reply to WHOIS - What server
// they're on
RPL_WHOISSERVER::RPL_WHOISSERVER(const std::string &nick,
								 const std::string &server,
								 const std::string &server_info)
	: IRPL(312, nick + " " + server + " :" + server_info) {};
RPL_WHOISSERVER::~RPL_WHOISSERVER(void) {};

// nb:313
// short for:RPL_WHOISOPERATOR
// desc:RFC1459 	<nick> :<privileges> 	Reply to WHOIS - User has IRC
// Operator privileges
RPL_WHOISOPERATOR::RPL_WHOISOPERATOR(const std::string &nick,
									 const std::string &privlege)
	: IRPL(313, nick + " :" + privlege) {};
RPL_WHOISOPERATOR::~RPL_WHOISOPERATOR(void) {};

// nb:314
// short for:RPL_WHOWASUSER
// desc:RFC1459 	<nick> <user> <host> * :<real_name> 	Reply to WHOWAS -
// Information about the user
RPL_WHOWASUSER::RPL_WHOWASUSER(const std::string &nick, const std::string &user,
							   const std::string &host,
							   const std::string &real_name)
	: IRPL(314, nick + " " + user + " " + host + " * :" + real_name) {

	  };
RPL_WHOWASUSER::~RPL_WHOWASUSER(void) {};

// nb:315
// short for:RPL_ENDOFWHO
// desc:RFC1459 	<name> :<info> 	Used to terminate a list of RPL_WHOREPLY
// replies
RPL_ENDOFWHO::RPL_ENDOFWHO(const std::string &name, const std::string &info)
	: IRPL(315, name + " :" + info) {};
RPL_ENDOFWHO::~RPL_ENDOFWHO(void) {};

// nb:317
// short for:RPL_WHOISIDLE
// desc:RFC1459 	<nick> <seconds> :seconds idle
// Reply to WHOIS - Idle information
RPL_WHOISIDLE::RPL_WHOISIDLE(const std::string &nick, unsigned long secs)
	: IRPL(317, nick + " " + to_string(secs) + " : since last activity.") {};
RPL_WHOISIDLE::~RPL_WHOISIDLE(void) {};

// nb:318
// short for:RPL_ENDOFWHOIS
// desc:RFC1459 	<nick> :<info> 	Reply to WHOIS - End of list
RPL_ENDOFWHOIS::RPL_ENDOFWHOIS(const std::string &nick, const std::string &info)
	: IRPL(318, nick + " :" + info) {};
RPL_ENDOFWHOIS::~RPL_ENDOFWHOIS(void) {};

// nb:319
// short for:RPL_WHOISCHANNELS
// desc:RFC1459 	<nick> :*( ( '@' / '+' ) <channel> ' ' ) 	Reply to WHOIS -
// Channel list for user (See RFC)
RPL_WHOISCHANNELS::RPL_WHOISCHANNELS(const std::string &nick,
									 const std::string &chanstr)
	: IRPL(319, nick + " :" + chanstr) {};
RPL_WHOISCHANNELS::~RPL_WHOISCHANNELS(void) {};

// nb:321
// short for:RPL_LISTSTART
// desc:RFC1459 	Channels :Users Name 	Channel list - Header
RPL_LISTSTART::RPL_LISTSTART() : IRPL(321, "Channels: Users Name") {};
RPL_LISTSTART::~RPL_LISTSTART(void) {};

// nb:322
// short for:RPL_LIST
// desc:RFC1459 	<channel> <#_visible> :<topic> 	Channel list - A channel
RPL_LIST::RPL_LIST(/* (Channel *) or ChannelState? */) : IRPL(322, "...") {
	IRPL::string = "";
};
RPL_LIST::~RPL_LIST(void) {};

// nb:323
// short for:RPL_LISTEND
// desc:RFC1459 	:<info> 	Channel list - End of list
RPL_LISTEND::RPL_LISTEND() : IRPL(323, "End of /LIST") {};
RPL_LISTEND::~RPL_LISTEND(void) {};

// nb:324
// short for:RPL_CHANNELMODEIS
// desc:RFC1459 	<channel> <mode> <mode_params>
RPL_CHANNELMODEIS::RPL_CHANNELMODEIS(std::string const &ch_name,
									 std::string const &modes,
									 std::string const &mode_params)
	: IRPL(324, ch_name + " " + modes + " " + mode_params) {};
RPL_CHANNELMODEIS::~RPL_CHANNELMODEIS(void) {};

// nb:325
// short for:RPL_UNIQOPIS
// desc:RFC2812 	<channel> <nickname>
RPL_UNIQOPIS::RPL_UNIQOPIS()
	: IRPL(325, "...") {
		  // TODO: implement.
	  };
RPL_UNIQOPIS::~RPL_UNIQOPIS(void) {};

// nb:331
// short for:RPL_NOTOPIC
// desc:RFC1459 	<channel> :<info> 	Response to TOPIC when no topic is set
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
// desc:RFC1459 	<channel> :<topic> 	Response to TOPIC with the set topic
RPL_TOPIC::RPL_TOPIC(const std::string &ch_name, const std::string &topic)
	: IRPL(332, ch_name + " :" + topic) {};
RPL_TOPIC::~RPL_TOPIC(void) {};

// nb:341
// short for:RPL_INVITING
// desc:RFC1459 	<nick> <channel> 	Returned by the server to indicate that
// the attempted INVITE message was successful and is being passed onto the end
// client. Note that RFC1459 documents the parameters in the reverse order. The
// format given here is the format used on production servers, and should be
// considered the standard reply above that given by RFC1459.
RPL_INVITING::RPL_INVITING(const std::string &nick, const std::string &ch_name)
	: IRPL(341, nick + " " + ch_name) {};
RPL_INVITING::~RPL_INVITING(void) {};

// nb:342
// short for:RPL_SUMMONING
// desc:RFC1459 	<user> :<info> 	Returned by a server answering a SUMMON
// message to indicate that it is summoning that user
RPL_SUMMONING::RPL_SUMMONING(const std::string &u, const std::string &info)
	: IRPL(342, u + " :" + info) {};
RPL_SUMMONING::~RPL_SUMMONING(void) {};

// // nb:345
// // short for:RPL_INVITED
// // desc:GameSurge 	<channel> <user being invited> <user issuing invite>
// :<user
// // being invited> has been invited by <user issuing invite> 	Sent to users on
// // a channel when an INVITE command has been issued
// RPL_INVITED::RPL_INVITED() : IRPL(000, "...") {};
// RPL_INVITED::~RPL_INVITED(void) {};

// // nb:346
// // short for:RPL_INVITELIST
// // desc:RFC2812 	<channel> <invitemask> 	An invite mask for the invite mask
// // list
// RPL_INVITELIST::RPL_INVITELIST() : IRPL(000, "...") {};
// RPL_INVITELIST::~RPL_INVITELIST(void) {};

// // nb:347
// // short for:RPL_ENDOFINVITELIST
// // desc:RFC2812 	<channel> :<info> 	Termination of an RPL_INVITELIST list
// RPL_ENDOFINVITELIST::RPL_ENDOFINVITELIST() : IRPL(000, "...") {};
// RPL_ENDOFINVITELIST::~RPL_ENDOFINVITELIST(void) {};

// nb:348
// short for:RPL_EXCEPTLIST
// desc:RFC2812 	<channel> <exceptionmask> 	An exception mask for the
// exception mask list. Also known as RPL_EXLIST (Unreal, Ultimate)
RPL_EXCEPTLIST::RPL_EXCEPTLIST(const std::string &chn, const std::string &emsk)
	: IRPL(348, chn + " " + emsk) {};
RPL_EXCEPTLIST::~RPL_EXCEPTLIST(void) {};

// nb:349
// short for:RPL_ENDOFEXCEPTLIST
// desc:RFC2812 	<channel> :<info> 	Termination of an RPL_EXCEPTLIST list.
// Also known as RPL_ENDOFEXLIST (Unreal, Ultimate)
RPL_ENDOFEXCEPTLIST::RPL_ENDOFEXCEPTLIST(const std::string &ch,
										 const std::string &info)
	: IRPL(349, ch + " :" + info) {};
RPL_ENDOFEXCEPTLIST::~RPL_ENDOFEXCEPTLIST(void) {};

// nb:351
// short for:RPL_VERSION
// desc:RFC1459 	<version>[.<debuglevel>] <server> :<comments> 	Reply by the
// server showing its version details, however this format is not often adhered
// to
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

// nb:352
// short for:RPL_WHOREPLY
// desc:RFC1459 	<channel> <user> <host> <server> <nick> <H|G>[*][@|+]
// :<hopcount> <real_name> 	Reply to vanilla WHO (See RFC). This format can be
// very different if the 'WHOX' version of the command is used (see ircu).
RPL_WHOREPLY::RPL_WHOREPLY() : IRPL(000, "...") {};
RPL_WHOREPLY::~RPL_WHOREPLY(void) {};

// nb:353
// short for:RPL_NAMREPLY
// desc:RFC1459 	( '=' / '*' / '@' ) <channel> ' ' : [ '@' / '+' ] <nick> *(
// ' ' [ '@' / '+' ] <nick> ) 	Reply to NAMES (See RFC)
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

// nb:361
// short for:RPL_KILLDONE
// desc:RFC1459
RPL_KILLDONE::RPL_KILLDONE() : IRPL(361, "...") {};
RPL_KILLDONE::~RPL_KILLDONE(void) {};

// nb:362
// short for:RPL_CLOSING
// desc:RFC1459
RPL_CLOSING::RPL_CLOSING() : IRPL(362, "...") {};
RPL_CLOSING::~RPL_CLOSING(void) {};

// nb:363
// short for:RPL_CLOSEEND
// desc:RFC1459
RPL_CLOSEEND::RPL_CLOSEEND() : IRPL(363, "...") {};
RPL_CLOSEEND::~RPL_CLOSEEND(void) {};

// nb:364
// short for:RPL_LINKS
// desc:RFC1459 	<mask> <server> :<hopcount> <server_info> 	Reply to the
// LINKS command
RPL_LINKS::RPL_LINKS() : IRPL(000, "...") {};
RPL_LINKS::~RPL_LINKS(void) {};

// nb:365
// short for:RPL_ENDOFLINKS
// desc:RFC1459 	<mask> :<info> 	Termination of an RPL_LINKS list
RPL_ENDOFLINKS::RPL_ENDOFLINKS(const std::string &msk, const std::string &info)
	: IRPL(365, msk + " :" + info) {};
RPL_ENDOFLINKS::~RPL_ENDOFLINKS(void) {};

// nb:366
// short for:RPL_ENDOFNAMES
// desc:RFC1459 	<channel> :<info> 	Termination of an RPL_NAMREPLY list
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

// nb:367
// short for:RPL_BANLIST
// desc:RFC1459 	<channel> <banid> [<time_left> :<reason>] 	A ban-list item
// (See RFC); <time left> and <reason> are additions used by KineIRCd
RPL_BANLIST::RPL_BANLIST() : IRPL(000, "...") {};
RPL_BANLIST::~RPL_BANLIST(void) {};

// nb:368
// short for:RPL_ENDOFBANLIST
// desc:RFC1459 	<channel> :<info> 	Termination of an RPL_BANLIST list
RPL_ENDOFBANLIST::RPL_ENDOFBANLIST(const std::string &channel,
								   const std::string &info)
	: IRPL(368, channel + " :" + info) {};
RPL_ENDOFBANLIST::~RPL_ENDOFBANLIST(void) {};

// nb:369
// short for:RPL_ENDOFWHOWAS
// desc:RFC1459 	<nick> :<info> 	Reply to WHOWAS - End of list
RPL_ENDOFWHOWAS::RPL_ENDOFWHOWAS(const std::string &nick,
								 const std::string &info)
	: IRPL(369, nick + " :" + info) {};
RPL_ENDOFWHOWAS::~RPL_ENDOFWHOWAS(void) {};

// nb:371
// short for:RPL_INFO
// desc:RFC1459 	:<string> 	Reply to INFO
RPL_INFO::RPL_INFO(const std::string &string) : IRPL(371, string) {};
RPL_INFO::~RPL_INFO(void) {};

// nb:372
// short for:RPL_MOTD
// desc:RFC1459 	:- <string> 	Reply to MOTD
RPL_MOTD::RPL_MOTD(const std::string &dword) : IRPL(372, "- " + dword) {};
RPL_MOTD::~RPL_MOTD(void) {};

// nb:373
// short for:RPL_INFOSTART
// desc:RFC1459
RPL_INFOSTART::RPL_INFOSTART() : IRPL(373, "...") {};
RPL_INFOSTART::~RPL_INFOSTART(void) {};

// nb:374
// short for:RPL_ENDOFINFO
// desc:RFC1459 	:<info> 	Termination of an RPL_INFO list
RPL_ENDOFINFO::RPL_ENDOFINFO(const std::string &info) : IRPL(374, info) {};
RPL_ENDOFINFO::~RPL_ENDOFINFO(void) {};

// nb:375
// short for:RPL_MOTDSTART
// desc:RFC1459 	:- <server> Message of the day - 	Start of an RPL_MOTD
// list
RPL_MOTDSTART::RPL_MOTDSTART()
	: IRPL(375, ":- <server> Message of the day - ") {};
RPL_MOTDSTART::~RPL_MOTDSTART(void) {};

// nb:376
// short for:RPL_ENDOFMOTD
// desc:RFC1459 	:<info> 	Termination of an RPL_MOTD list
RPL_ENDOFMOTD::RPL_ENDOFMOTD() : IRPL(376, ":End of MOTD command") {};
RPL_ENDOFMOTD::~RPL_ENDOFMOTD(void) {};

// nb:381
// short for:RPL_YOUREOPER
// desc:RFC1459 	:<info> 	Successful reply from OPER
RPL_YOUREOPER::RPL_YOUREOPER() : IRPL(381, "You are now an IRC operator") {};
RPL_YOUREOPER::~RPL_YOUREOPER(void) {};

// nb:382
// short for:RPL_REHASHING
// desc:RFC1459 	<config_file> :<info> 	Successful reply from REHASH
RPL_REHASHING::RPL_REHASHING(const std::string &cfile, const std::string &info)
	: IRPL(382, cfile + " :" + info) {};
RPL_REHASHING::~RPL_REHASHING(void) {};

// nb:383
// short for:RPL_YOURESERVICE
// desc:RFC2812 	:You are service <service_name> 	Sent upon successful
// registration of a service
RPL_YOURESERVICE::RPL_YOURESERVICE(const std::string sername)
	: IRPL(383, "You are service " + sername) {};
RPL_YOURESERVICE::~RPL_YOURESERVICE(void) {};

// // nb:384
// // short for:RPL_MYPORTIS
// // desc:RFC1459
// RPL_MYPORTIS::RPL_MYPORTIS(const std::string &port) : IRPL(384, port) {};
// RPL_MYPORTIS::~RPL_MYPORTIS(void) {};

// nb:391
// short for:RPL_TIME
// desc:RFC1459 	<server> :<time string> 	Response to the TIME command.
// The string format may vary greatly. Also see #679.
RPL_TIME::RPL_TIME(const std::string &sname, const std::string &time)
	: IRPL(391, sname + " " + time) {};
RPL_TIME::~RPL_TIME(void) {};

// nb:392
// short for:RPL_USERSSTART
// desc:RFC1459 	:UserID Terminal Host 	Start of an RPL_USERS list
RPL_USERSSTART::RPL_USERSSTART(const std::string &uid, const std::string &th)
	: IRPL(392, uid + " " + th) {};
RPL_USERSSTART::~RPL_USERSSTART(void) {};

// nb:393
// short for:RPL_USERS
// desc:RFC1459 	:<username> <ttyline> <hostname> 	Response to the USERS
// command (See RFC)
RPL_USERS::RPL_USERS(const std::string &usr_name, const std::string &ttyline,
					 const std::string &hname)
	: IRPL(393, usr_name + " " + ttyline + " " + hname) {};
RPL_USERS::~RPL_USERS(void) {};

// nb:394
// short for:RPL_ENDOFUSERS
// desc:RFC1459 	:<info> 	Termination of an RPL_USERS list
RPL_ENDOFUSERS::RPL_ENDOFUSERS(const std::string &inf) : IRPL(394, inf) {};
RPL_ENDOFUSERS::~RPL_ENDOFUSERS(void) {};

// nb:395
// short for:RPL_NOUSERS
// desc:RFC1459 	:<info> 	Reply to USERS when nobody is logged in
RPL_NOUSERS::RPL_NOUSERS(const std::string &inf) : IRPL(395, inf) {};
RPL_NOUSERS::~RPL_NOUSERS(void) {};

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

////////////////////////////////////////////////////////////////////////////////
//									 ------									  //
//									 errors									  //
//									 ------									  //
////////////////////////////////////////////////////////////////////////////////

// nb:401
// short for:ERR_NOSUCHNICK
// desc:RFC1459 	<nick> :<reason> 	Used to indicate the nickname parameter
// supplied to a command is currently unused
ERR_NOSUCHNICK::ERR_NOSUCHNICK(const std::string &nick,
							   const std::string &reason)
	: IError(401, nick + " :" + reason) {};
ERR_NOSUCHNICK::~ERR_NOSUCHNICK(void) throw() {};

// nb:402
// short for:ERR_NOSUCHSERVER
// desc:RFC1459 	<server> :<reason> 	Used to indicate the server name given
// currently doesn't exist
ERR_NOSUCHSERVER::ERR_NOSUCHSERVER(const std::string &server,
								   const std::string &reason)
	: IError(402, server + " :" + reason) {};
ERR_NOSUCHSERVER::~ERR_NOSUCHSERVER(void) throw() {};

// nb:403
// short for:ERR_NOSUCHCHANNEL
// desc:RFC1459 	<channel> :<reason> 	Used to indicate the given channel
// name is invalid, or does not exist
ERR_NOSUCHCHANNEL::ERR_NOSUCHCHANNEL(const std::string &ch_name,
									 const std::string &reason)
	: IError(403, ch_name + " :" + reason) {};
ERR_NOSUCHCHANNEL::~ERR_NOSUCHCHANNEL(void) throw() {};

// nb:404
// short for:ERR_CANNOTSENDTOCHAN
// desc:RFC1459 	<channel> :<reason> 	Sent to a user who does not have the
// rights to send a message to a channel
ERR_CANNOTSENDTOCHAN::ERR_CANNOTSENDTOCHAN(const std::string &ch_name,
										   const std::string &reason)
	: IError(404, ch_name + " :" + reason) {};
ERR_CANNOTSENDTOCHAN::~ERR_CANNOTSENDTOCHAN(void) throw() {};

// nb:405
// short for:ERR_TOOMANYCHANNELS
// desc:RFC1459 	<channel> :<reason> 	Sent to a user when they have joined
// the maximum number of allowed channels and they tried to join another channel
ERR_TOOMANYCHANNELS::ERR_TOOMANYCHANNELS(const std::string &ch_name,
										 const std::string &reason)
	: IError(405, ch_name + " :" + reason) {};
ERR_TOOMANYCHANNELS::~ERR_TOOMANYCHANNELS(void) throw() {};

// nb:406
// short for:ERR_WASNOSUCHNICK
// desc:RFC1459 	<nick> :<reason> 	Returned by WHOWAS to indicate there was
// no history information for a given nickname
ERR_WASNOSUCHNICK::ERR_WASNOSUCHNICK(const std::string &nick,
									 const std::string &reason)
	: IError(406, nick + " :" + reason) {};
ERR_WASNOSUCHNICK::~ERR_WASNOSUCHNICK(void) throw() {};

// nb:407
// short for:ERR_TOOMANYTARGETS
// desc:RFC1459 	<target> :<reason> 	The given target(s) for a command are
// ambiguous in that they relate to too many targets
ERR_TOOMANYTARGETS::ERR_TOOMANYTARGETS(const std::string &target,
									   const std::string &reason)
	: IError(407, target + " :" + reason) {};
ERR_TOOMANYTARGETS::~ERR_TOOMANYTARGETS(void) throw() {};

// nb:408
// short for:ERR_NOSUCHSERVICE
// desc:RFC2812 	<service_name> :<reason> 	Returned to a client which is
// attempting to send an SQUERY (or other message) to a service which does not
// exist
ERR_NOSUCHSERVICE::ERR_NOSUCHSERVICE(const std::string &serv_name,
									 const std::string &reason)
	: IError(408, serv_name + " :" + reason) {};
ERR_NOSUCHSERVICE::~ERR_NOSUCHSERVICE(void) throw() {};

// nb:409
// short for:ERR_NOORIGIN
// desc:RFC1459 	:<reason> 	PING or PONG message missing the originator
// parameter which is required since these commands must work without valid
// prefixes
ERR_NOORIGIN::ERR_NOORIGIN(const std::string &reason) : IError(409, reason) {};
ERR_NOORIGIN::~ERR_NOORIGIN(void) throw() {};

// nb:411
// short for:ERR_NORECIPIENT
// desc:RFC1459 	:<reason> 	Returned when no recipient is given with a
// command
ERR_NORECIPIENT::ERR_NORECIPIENT(const std::string &reason)
	: IError(411, reason) {};
ERR_NORECIPIENT::~ERR_NORECIPIENT(void) throw() {};

// nb:412
// short for:ERR_NOTEXTTOSEND
// desc:RFC1459 	:<reason> 	Returned when NOTICE/PRIVMSG is used with no
// message given
ERR_NOTEXTTOSEND::ERR_NOTEXTTOSEND(const std::string &reason)
	: IError(412, reason) {};
ERR_NOTEXTTOSEND::~ERR_NOTEXTTOSEND(void) throw() {};

// nb:413
// short for:ERR_NOTOPLEVEL
// desc:RFC1459 	<mask> :<reason> 	Used when a message is being sent to a
// mask without being limited to a top-level domain (i.e. * instead of *.au)
ERR_NOTOPLEVEL::ERR_NOTOPLEVEL(const std::string &mask,
							   const std::string &reason)
	: IError(413, mask + " :" + reason) {};
ERR_NOTOPLEVEL::~ERR_NOTOPLEVEL(void) throw() {};

// nb:414
// short for:ERR_WILDTOPLEVEL
// desc:RFC1459 	<mask> :<reason> 	Used when a message is being sent to a
// mask with a wild-card for a top level domain (i.e. *.*)
ERR_WILDTOPLEVEL::ERR_WILDTOPLEVEL(const std::string &mask,
								   const std::string &reason)
	: IError(414, mask + " :" + reason) {};
ERR_WILDTOPLEVEL::~ERR_WILDTOPLEVEL(void) throw() {};

// nb:415
// short for:ERR_BADMASK
// desc:RFC2812 	<mask> :<reason> 	Used when a message is being sent to a
// mask with an invalid syntax
ERR_BADMASK::ERR_BADMASK(const std::string &mask, const std::string &reason)
	: IError(415, mask + " :" + reason) {};
ERR_BADMASK::~ERR_BADMASK(void) throw() {};

// nb:416
// short for:ERR_TOOMANYMATCHES
// desc:IRCnet 	<command> [<mask>] :<info> 	Returned when too many matches have
// been found for a command and the output has been truncated. An example would
// be the WHO command, where by the mask '*' would match everyone on the
// network! Ouch!
ERR_TOOMANYMATCHES::ERR_TOOMANYMATCHES(const std::string &cmd,
									   const std::string &mask,
									   const std::string &info)
	: IError(416, cmd + " " + mask + " :" + info) {};
ERR_TOOMANYMATCHES::~ERR_TOOMANYMATCHES(void) throw() {};

// nb:421
// short for:ERR_UNKNOWNCOMMAND
// desc:RFC1459 	<command> :<reason> 	Returned when the given command is
// unknown to the server (or hidden because of lack of access rights)
ERR_UNKNOWNCOMMAND::ERR_UNKNOWNCOMMAND(const std::string &cmd_predicate,
									   const std::string &reason)
	: IError(421, cmd_predicate + " :" + reason) {};
ERR_UNKNOWNCOMMAND::~ERR_UNKNOWNCOMMAND(void) throw() {}

// nb:422
// short for:ERR_NOMOTD
// desc:RFC1459 	:<reason> 	Sent when there is no MOTD to send the client
ERR_NOMOTD::ERR_NOMOTD(const std::string &reason) : IError(422, reason) {};
ERR_NOMOTD::~ERR_NOMOTD(void) throw() {};

// nb:423
// short for:ERR_NOADMININFO
// desc:RFC1459 	<server> :<reason> 	Returned by a server in response to an
// ADMIN request when no information is available. RFC1459 mentions this in the
// list of numerics. While it's not listed as a valid reply in section 4.3.7
// ('Admin command'), it's confirmed to exist in the real world.
ERR_NOADMININFO::ERR_NOADMININFO(const std::string &server,
								 const std::string &reason)
	: IError(423, server + " :" + reason) {};
ERR_NOADMININFO::~ERR_NOADMININFO(void) throw() {};

// nb:424
// short for:ERR_FILEERROR
// desc:RFC1459 	:<reason> 	Generic error message used to report a failed
// file operation during the processing of a command
ERR_FILEERROR::ERR_FILEERROR(const std::string &reason)
	: IError(424, reason) {};
ERR_FILEERROR::~ERR_FILEERROR(void) throw() {};

// nb:431
// short for:ERR_NONICKNAMEGIVEN
// desc:RFC1459 	:<reason> 	Returned when a nickname parameter expected for
// a command isn't found
ERR_NONICKNAMEGIVEN::ERR_NONICKNAMEGIVEN(const std::string &reason)
	: IError(431, reason) {};
ERR_NONICKNAMEGIVEN::~ERR_NONICKNAMEGIVEN() throw() {}

// nb:432
// short for:ERR_ERRONEUSNICKNAME
// desc:RFC1459 	<nick> :<reason> 	Returned after receiving a NICK message
// which contains a nickname which is considered invalid, such as it's reserved
// ('anonymous') or contains characters considered invalid for nicknames. This
// numeric is misspelt, but remains with this name for historical reasons :)
ERR_ERRONEUSNICKNAME::ERR_ERRONEUSNICKNAME(const std::string &nick,
										   const std::string &reason)
	: IError(432, nick + " :" + reason) {}
ERR_ERRONEUSNICKNAME::~ERR_ERRONEUSNICKNAME(void) throw() {}

// nb:433
// short for:ERR_NICKNAMEINUSE
// desc:RFC1459 	<nick> :<reason> 	Returned by the NICK command when the
// given nickname is already in use
ERR_NICKNAMEINUSE::ERR_NICKNAMEINUSE(const std::string &nick,
									 const std::string &reason)
	: IError(433, nick + " :" + reason) {}
ERR_NICKNAMEINUSE::~ERR_NICKNAMEINUSE(void) throw() {}

// nb:436
// short for:ERR_NICKCOLLISION
// desc:RFC1459 	<nick> :<reason> 	Returned by a server to a client when it
// detects a nickname collision
ERR_NICKCOLLISION::ERR_NICKCOLLISION(const std::string &nick,
									 const std::string &reason)
	: IError(436, nick + " :" + reason) {}
ERR_NICKCOLLISION::~ERR_NICKCOLLISION(void) throw() {};

// nb:437
// short for:ERR_UNAVAILRESOURCE
// desc:RFC2812 	<nick/channel/service> :<reason> 	Return when the target
// is unable to be reached temporarily, eg. a delay mechanism in play, or a
// service being offline
ERR_UNAVAILRESOURCE::ERR_UNAVAILRESOURCE(const std::string &target,
										 const std::string &reason)
	: IError(437, target + " :" + reason) {}
ERR_UNAVAILRESOURCE::~ERR_UNAVAILRESOURCE(void) throw() {};

// nb:441
// short for:ERR_USERNOTINCHANNEL
// desc:RFC1459 	<nick> <channel> :<reason> 	Returned by the server to
// indicate that the target user of the command is not on the given channel
ERR_USERNOTINCHANNEL::ERR_USERNOTINCHANNEL(const std::string &nick,
										   const std::string &ch_name,
										   const std::string &reason)
	: IError(441, nick + " " + ch_name + " :" + reason) {}
ERR_USERNOTINCHANNEL::~ERR_USERNOTINCHANNEL(void) throw() {};

// nb:442
// short for:ERR_NOTONCHANNEL
// desc:RFC1459 	<channel> :<reason> 	Returned by the server whenever a
// client tries to perform a channel effecting command for which the client is
// not a member
ERR_NOTONCHANNEL::ERR_NOTONCHANNEL(const std::string &chan,
								   const std::string &reason)
	: IError(442, chan + " :" + reason) {}
ERR_NOTONCHANNEL::~ERR_NOTONCHANNEL(void) throw() {}

// nb:443
// short for:ERR_USERONCHANNEL
// desc:RFC1459 	<nick> <channel> [:<reason>] 	Returned when a client tries
// to invite a user to a channel they're already on
ERR_USERONCHANNEL::ERR_USERONCHANNEL(const std::string &nick,
									 const std::string &chan,
									 const std::string &reason)
	: IError(443, nick + " " + chan) {
	if (reason.empty() == false)
		IError::_s += " :" + reason;
}
ERR_USERONCHANNEL::~ERR_USERONCHANNEL(void) throw() {}

// nb:444
// short for:ERR_NOLOGIN
// desc:RFC1459 	<user> :<reason> 	Returned by the SUMMON command if a
// given user was not logged in and could not be summoned
ERR_NOLOGIN::ERR_NOLOGIN(const std::string &usr, const std::string &r)
	: IError(444, usr + " :" + r) {};
ERR_NOLOGIN::~ERR_NOLOGIN(void) throw() {}

// nb:445
// short for:ERR_SUMMONDISABLED
// desc:RFC1459 	:<reason> 	Returned by SUMMON when it has been disabled or
// not implemented
ERR_SUMMONDISABLED::ERR_SUMMONDISABLED(const std::string &reason)
	: IError(445, reason) {};
ERR_SUMMONDISABLED::~ERR_SUMMONDISABLED(void) throw() {}

// nb:446
// short for:ERR_USERSDISABLED
// desc:RFC1459 	:<reason> 	Returned by USERS when it has been disabled or
// not implemented
ERR_USERSDISABLED::ERR_USERSDISABLED(const std::string &reason)
	: IError(446, reason) {};
ERR_USERSDISABLED::~ERR_USERSDISABLED(void) throw() {};

// nb:451
// short for:ERR_NOTREGISTERED
// desc:RFC1459 	:<reason> 	Returned by the server to indicate that the
// client must be registered before the server will allow it to be parsed in
// detail
ERR_NOTREGISTERED::ERR_NOTREGISTERED(const std::string &reason)
	: IError(452, reason) {};
ERR_NOTREGISTERED::~ERR_NOTREGISTERED(void) throw() {};

// nb:461
// short for:ERR_NEEDMOREPARAMS
// desc:RFC1459 	<command> :<reason> 	Returned by the server by any
// command which requires more parameters than the number of parameters given
ERR_NEEDMOREPARAMS::ERR_NEEDMOREPARAMS(const std::string &cmd,
									   const std::string &reason)
	: IError(461, cmd + " :" + reason) {}
ERR_NEEDMOREPARAMS::~ERR_NEEDMOREPARAMS(void) throw() {}

// nb:462
// short for:ERR_ALREADYREGISTERED
// desc:RFC1459 	:<reason> 	Returned by the server to any link which
// attempts to register again
ERR_ALREADYREGISTERED::ERR_ALREADYREGISTERED(const std::string &reason)
	: IError(462, reason) {};
ERR_ALREADYREGISTERED::~ERR_ALREADYREGISTERED(void) throw() {}

// nb:463
// short for:ERR_NOPERMFORHOST
// desc:RFC1459 	:<reason> 	Returned to a client which attempts to register
// with a server which has been configured to refuse connections from the
// client's host
ERR_NOPERMFORHOST::ERR_NOPERMFORHOST(const std::string &reason)
	: IError(463, reason) {};
ERR_NOPERMFORHOST::~ERR_NOPERMFORHOST(void) throw() {}

// nb:464
// short for:ERR_PASSWDMISMATCH
// desc:RFC1459 	:<reason> 	Returned by the PASS command to indicate the
// given password was required and was either not given or was incorrect
ERR_PASSWDMISMATCH::ERR_PASSWDMISMATCH(const std::string &r)
	: IError(464, r) {};
ERR_PASSWDMISMATCH::~ERR_PASSWDMISMATCH(void) throw() {}

// nb:465
// short for:ERR_YOUREBANNEDCREEP
// desc:RFC1459 	:<reason> 	Returned to a client after an attempt to
// register on a server configured to ban connections from that client
ERR_YOUREBANNEDCREEP::ERR_YOUREBANNEDCREEP(const std::string &reason)
	: IError(462, reason) {};
ERR_YOUREBANNEDCREEP::~ERR_YOUREBANNEDCREEP(void) throw() {}

// nb:466
// short for:ERR_YOUWILLBEBANNED
// desc:RFC1459 		Sent by a server to a user to inform that access to the
// server will soon be denied
ERR_YOUWILLBEBANNED::ERR_YOUWILLBEBANNED(const std::string &msg)
	: IError(466, msg) {};
ERR_YOUWILLBEBANNED::~ERR_YOUWILLBEBANNED(void) throw() {};

// nb:467
// short for:ERR_KEYSET
// desc:RFC1459 	<channel> :<reason> 	Returned when the channel key for a
// channel has already been set
ERR_KEYSET::ERR_KEYSET(const std::string &chan, const std::string &r)
	: IError(467, chan + " :" + r) {};
ERR_KEYSET::~ERR_KEYSET(void) throw() {};

// nb:471
// short for:ERR_CHANNELISFULL
// desc:RFC1459 	<channel> :<reason> 	Returned when attempting to join a
// channel which is set +l and is already full
ERR_CHANNELISFULL::ERR_CHANNELISFULL(const std::string &chan,
									 const std::string &r)
	: IError(471, chan + " :" + r) {};
ERR_CHANNELISFULL::~ERR_CHANNELISFULL(void) throw() {};

// nb:472
// short for:ERR_UNKNOWNMODE
// desc:RFC1459 	<char> :<reason> 	Returned when a given mode is unknow
ERR_UNKNOWNMODE::ERR_UNKNOWNMODE(const std::string &char_m,
								 const std::string &r)
	: IError(472, char_m + " :" + r) {};
ERR_UNKNOWNMODE::~ERR_UNKNOWNMODE(void) throw() {};

// nb:473
// short for:ERR_INVITEONLYCHAN
// desc:RFC1459 	<channel> :<reason> 	Returned when attempting to join a
// channel which is invite only without an invitation
ERR_INVITEONLYCHAN::ERR_INVITEONLYCHAN(const std::string &chan,
									   const std::string &r)
	: IError(473, chan + " :" + r) {};
ERR_INVITEONLYCHAN::~ERR_INVITEONLYCHAN(void) throw() {};

// nb:474
// short for:ERR_BANNEDFROMCHAN
// desc:RFC1459 	<channel> :<reason> 	Returned when attempting to join a
// channel a user is banned from
ERR_BANNEDFROMCHAN::ERR_BANNEDFROMCHAN(const std::string &chan,
									   const std::string &r)
	: IError(474, chan + " :" + r) {};
ERR_BANNEDFROMCHAN::~ERR_BANNEDFROMCHAN(void) throw() {};

// nb:475
// short for:ERR_BADCHANNELKEY
// desc:RFC1459 	<channel> :<reason> 	Returned when attempting to join a
// key-locked channel either without a key or with the wrong key
ERR_BADCHANNELKEY::ERR_BADCHANNELKEY(const std::string &chan,
									 const std::string &r)
	: IError(475, chan + " :" + r) {};
ERR_BADCHANNELKEY::~ERR_BADCHANNELKEY(void) throw() {};

// nb:476
// short for:ERR_BADCHANMASK
// desc:RFC2812 	<channel> :<reason> 	The given channel mask was invalid
ERR_BADCHANMASK::ERR_BADCHANMASK(const std::string &chan, const std::string &r)
	: IError(476, chan + " :" + r) {};
ERR_BADCHANMASK::~ERR_BADCHANMASK(void) throw() {};

// nb:477
// short for:ERR_NOCHANMODES
// desc:RFC2812 	<channel> :<reason> 	Returned when attempting to set a
// mode on a channel which does not support channel modes, or channel mode
// changes. Also known as ERR_MODELESS
ERR_NOCHANMODES::ERR_NOCHANMODES(const std::string &chan, const std::string &r)
	: IError(477, chan + " :" + r) {};
ERR_NOCHANMODES::~ERR_NOCHANMODES(void) throw() {};

// nb:478
// short for:ERR_BANLISTFULL
// desc:RFC2812 	<channel> <char> :<reason> 	Returned when a channel access
// list (i.e. ban list etc) is full and cannot be added to
ERR_BANLISTFULL::ERR_BANLISTFULL(const std::string &channel, char mode_char,
								 const std::string &reason)
	: IError(478, channel + " " + mode_char + " :" + reason) {};
ERR_BANLISTFULL::~ERR_BANLISTFULL(void) throw() {};

// nb:481
// short for:ERR_NOPRIVILEGES
// desc:RFC1459 	:<reason> 	Returned by any command requiring special
// privileges (eg. IRC operator) to indicate the operation was unsuccessful
ERR_NOPRIVILEGES::ERR_NOPRIVILEGES(const std::string &r) : IError(481, r) {}
ERR_NOPRIVILEGES::~ERR_NOPRIVILEGES(void) throw() {};

// nb:482
// short for:ERR_CHANOPRIVSNEEDED
// desc:RFC1459 	<channel> :<reason> 	Returned by any command requiring
// special channel privileges (eg. channel operator) to indicate the operation
// was unsuccessful
ERR_CHANOPRIVSNEEDED::ERR_CHANOPRIVSNEEDED(const std::string &chan,
										   const std::string &r)
	: IError(482, chan + " :" + r) {};
ERR_CHANOPRIVSNEEDED::~ERR_CHANOPRIVSNEEDED(void) throw() {};

// nb:483
// short for:ERR_CANTKILLSERVER
// desc:RFC1459 	:<reason> 	Returned by KILL to anyone who tries to kill a
// server
ERR_CANTKILLSERVER::ERR_CANTKILLSERVER(const std::string &r) : IError(483, r) {}
ERR_CANTKILLSERVER::~ERR_CANTKILLSERVER(void) throw() {};

// nb:484
// short for:ERR_RESTRICTED
// desc:RFC2812 	:<reason> 	Sent by the server to a user upon connection to
// indicate the restricted nature of the connection (i.e. usermode +r)
ERR_RESTRICTED::ERR_RESTRICTED(const std::string &r) : IError(484, r) {}
ERR_RESTRICTED::~ERR_RESTRICTED(void) throw() {};

// nb:485
// short for:ERR_UNIQOPRIVSNEEDED
// desc:RFC2812 	:<reason> 	Any mode requiring 'channel creator' privileges
// returns this error if the client is attempting to use it while not a channel
// creator on the given channel
ERR_UNIQOPRIVSNEEDED::ERR_UNIQOPRIVSNEEDED(const std::string &r)
	: IError(485, r) {}
ERR_UNIQOPRIVSNEEDED::~ERR_UNIQOPRIVSNEEDED(void) throw() {};

// nb:491
// short for:ERR_NOOPERHOST
// desc:RFC1459 	:<reason> 	Returned by OPER to a client who cannot become
// an IRC operator because the server has been configured to disallow the
// client's host
ERR_NOOPERHOST::ERR_NOOPERHOST(const std::string &r) : IError(491, r) {}
ERR_NOOPERHOST::~ERR_NOOPERHOST(void) throw() {};

// nb:492
// short for:ERR_NOSERVICEHOST
// desc:RFC1459
ERR_NOSERVICEHOST::ERR_NOSERVICEHOST(const std::string &r) : IError(492, r) {};
ERR_NOSERVICEHOST::~ERR_NOSERVICEHOST(void) throw() {};

// nb:501
// short for:ERR_UMODEUNKNOWNFLAG
// desc:RFC1459 	:<reason> 	Returned by the server to indicate that a MODE
// message was sent with a nickname parameter and that the mode flag sent was
// not recognised
ERR_UMODEUNKNOWNFLAG::ERR_UMODEUNKNOWNFLAG(const std::string &r)
	: IError(501, r) {}
ERR_UMODEUNKNOWNFLAG::~ERR_UMODEUNKNOWNFLAG(void) throw() {};

// nb:502
// short for:ERR_USERSDONTMATCH
// desc:RFC1459 	:<reason> 	Error sent to any user trying to view or change
// the user mode for a user other than themselves
ERR_USERSDONTMATCH::ERR_USERSDONTMATCH(const std::string &r) : IError(502, r) {}
ERR_USERSDONTMATCH::~ERR_USERSDONTMATCH(void) throw() {};
