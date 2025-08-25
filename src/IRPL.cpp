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
	ss << " " << c.getNick() << " :" << string << "\r\n";
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
				"(version:" IRC_SERVER_VERSION ".") {};
RPL_CREATED::~RPL_CREATED(void) {};

RPL_MYINFO::RPL_MYINFO()
	: IRPL(004, SERVER_NAME_DFLT
		   " " IRC_SERVER_VERSION
		   " " /* available user modes   available chanel modes*/) {}
RPL_MYINFO::~RPL_MYINFO() {};

RPL_BOUNCE::RPL_BOUNCE()
	: IRPL(005, "") {
		  // TODO:
		  // implement when server is multi-server capable
		  //	- pick a server not full in list of connected server,
		  //	- set _s to "Try server <server_name>, port <port_number>"
		  //	end.
	  };
RPL_BOUNCE::~RPL_BOUNCE() {};

RPL_TRACELINK::RPL_TRACELINK() : IRPL(200, "") {
	// TODO:
	// server stuff.
	// didnt really get it.
}
RPL_TRACELINK::~RPL_TRACELINK() {};

RPL_TRACECONNECTING::RPL_TRACECONNECTING() : IRPL(201, "") {
	// TODO:
	// server stuff.
	// didnt really get it.
}
RPL_TRACECONNECTING::~RPL_TRACECONNECTING(void) {}

// nb:202
// short for:RPL_TRACEHANDSHAKE
// desc:RFC1459 	H.S. <class> <server> 	See RFC
RPL_TRACEHANDSHAKE::RPL_TRACEHANDSHAKE() : IRPL(202, "") {
	// TODO:
	// server stuff.
	// didnt really get it.
}
RPL_TRACEHANDSHAKE::~RPL_TRACEHANDSHAKE(void) {};

// nb:203
// short for:RPL_TRACEUNKNOWN
// desc:RFC1459 	???? <class> [<connection_address>] 	See RFC
RPL_TRACEUNKNOWN::RPL_TRACEUNKNOWN() : IRPL(203, "") {
	// TODO:
	// server stuff.
	// didnt really get it.
}
RPL_TRACEUNKNOWN::~RPL_TRACEUNKNOWN(void) {};

// nb:204
// short for:RPL_TRACEOPERATOR
// desc:RFC1459 	Oper <class> <nick> 	See RFC
RPL_TRACEOPERATOR::RPL_TRACEOPERATOR() : IRPL(204, "") {
	// TODO:
	// server stuff.
	// didnt really get it.
}
RPL_TRACEOPERATOR::~RPL_TRACEOPERATOR(void) {};

// nb:205
// short for:RPL_TRACEUSER
// desc:RFC1459 	User <class> <nick> 	See RFC
RPL_TRACEUSER::RPL_TRACEUSER() : IRPL(205, "") {
	// TODO:
	// server stuff.
	// didnt really get it.
}
RPL_TRACEUSER::~RPL_TRACEUSER(void) {};

// nb:206
// short for:RPL_TRACESERVER
// desc:RFC1459 	Serv <class> <int>S <int>C <server>
// <nick!user|*!*>@<host|server> [V<protocol_version>] 	See RFC
RPL_TRACESERVER::RPL_TRACESERVER() : IRPL(206, "") {
	// TODO:
	// server stuff.
	// didnt really get it.
}
RPL_TRACESERVER::~RPL_TRACESERVER(void) {};

// nb:207
// short for:RPL_TRACESERVICE
// desc:RFC2812 	Service <class> <name> <type> <active_type> 	See RFC
RPL_TRACESERVICE::RPL_TRACESERVICE() : IRPL(207, "") {
	// TODO:
	// server stuff.
	// didnt really get it.
}
RPL_TRACESERVICE::~RPL_TRACESERVICE(void) {};

// nb:208
// short for:RPL_TRACENEWTYPE
// desc:RFC1459 	<newtype> 0 <client_name> 	See RFC
RPL_TRACENEWTYPE::RPL_TRACENEWTYPE() : IRPL(208, "") {
	// TODO:
	// server stuff.
	// didnt really get it.
}
RPL_TRACENEWTYPE::~RPL_TRACENEWTYPE(void) {};

// nb:209
// short for:RPL_TRACECLASS
// desc:RFC2812 	Class <class> <count> 	See RFC
RPL_TRACECLASS::RPL_TRACECLASS() : IRPL(209, "") {
	// TODO:
	// server stuff.
	// didnt really get it.
}
RPL_TRACECLASS::~RPL_TRACECLASS(void) {};

// nb:210
// short for:RPL_TRACERECONNECT
// desc:RFC2812
RPL_TRACERECONNECT::RPL_TRACERECONNECT() : IRPL(210, "") {
	// TODO:
	// server stuff.
	// didnt really get it.
}
RPL_TRACERECONNECT::~RPL_TRACERECONNECT(void) {};

// nb:211
// short for:RPL_STATSLINKINFO
// desc:RFC1459 	<linkname> <sendq> <sent_msgs> <sent_bytes> <recvd_msgs>
// <rcvd_bytes> <time_open> 	Reply to STATS (See RFC)
RPL_STATSLINKINFO::RPL_STATSLINKINFO() : IRPL(212, "") {
	// TODO:
	// server stuff.
	// didnt really get it.
}
RPL_STATSLINKINFO::~RPL_STATSLINKINFO(void) {};

// nb:212
// short for:RPL_STATSCOMMANDS
// desc:RFC1459 	<command> <count> [<byte_count> <remote_count>] 	Reply to
// STATS (See RFC)
RPL_STATSCOMMANDS::RPL_STATSCOMMANDS() : IRPL(212, "") {
	// TODO:
	// server stuff.
	// didnt really get it.
}
RPL_STATSCOMMANDS::~RPL_STATSCOMMANDS(void) {};

// nb:213
// short for:RPL_STATSCLINE
// desc:RFC1459 	C <host> * <name> <port> <class> 	Reply to STATS (See RFC)
RPL_STATSCLINE::RPL_STATSCLINE() : IRPL(213, "") {
	// TODO:
	// server stuff.
	// didnt really get it.
}
RPL_STATSCLINE::~RPL_STATSCLINE(void) {};

// nb:214
// short for:RPL_STATSNLINE
// desc:RFC1459 	N <host> * <name> <port> <class> 	Reply to STATS (See
// RFC), Also known as RPL_STATSOLDNLINE (ircu, Unreal)
RPL_STATSNLINE::RPL_STATSNLINE() : IRPL(214, "") {
	// TODO:
	// server stuff.
	// didnt really get it.
}
RPL_STATSNLINE::~RPL_STATSNLINE(void) {};

// nb:215
// short for:RPL_STATSILINE
// desc:RFC1459 	I <host> * <host> <port> <class> 	Reply to STATS (See RFC)
RPL_STATSILINE::RPL_STATSILINE() : IRPL(215, "") {
	// TODO:
	// server stuff.
	// didnt really get it.
}
RPL_STATSILINE::~RPL_STATSILINE(void) {};

// nb:216
// short for:RPL_STATSKLINE
// desc:RFC1459 	K <host> * <username> <port> <class> 	Reply to STATS (See
// RFC)
RPL_STATSKLINE::RPL_STATSKLINE() : IRPL(216, "") {
	// TODO:
	// server stuff.
	// didnt really get it.
}
RPL_STATSKLINE::~RPL_STATSKLINE(void) {};

// nb:217
// short for:RPL_STATSQLINE
// desc:RFC1459
RPL_STATSQLINE::RPL_STATSQLINE() : IRPL(217, "") {
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
RPL_STATSYLINE::RPL_STATSYLINE() : IRPL(218, "") {
	// TODO:
	// server stuff.
	// didnt really get it.
}
RPL_STATSYLINE::~RPL_STATSYLINE(void) {};

// nb:219
// short for:RPL_ENDOFSTATS
// desc:RFC1459 	<query> :<info> 	End of RPL_STATS* list.
RPL_ENDOFSTATS::RPL_ENDOFSTATS() : IRPL(219, "") {
	// TODO:
	// server stuff.
	// didnt really get it.
}
RPL_ENDOFSTATS::~RPL_ENDOFSTATS(void) {};

RPL_UMODEIS::RPL_UMODEIS(const std::string &modes) : IRPL(221, modes) {}
RPL_UMODEIS::~RPL_UMODEIS(void) {};

// might be useless - no server to server communications are needed for irc
RPL_SERVLIST::RPL_SERVLIST() : IRPL(234, "") {};
RPL_SERVLIST::~RPL_SERVLIST() {};

RPL_SERVLISTEND::RPL_SERVLISTEND(void) : IRPL(235, "End of service listing") {};
RPL_SERVLISTEND::~RPL_SERVLISTEND(void) {};

// nb:240
// short for:RPL_STATSVLINE
// desc:RFC2812
RPL_STATSVLINE::RPL_STATSVLINE() : IRPL(240, "") {};
RPL_STATSVLINE::~RPL_STATSVLINE(void) {};

// nb:241
// short for:RPL_STATSLLINE::RPL_STATSLLINE
// desc:RFC1459 	L <hostmask> * <servername> <maxdepth> 	Reply to STATS (See
// RFC)
RPL_STATSLLINE::RPL_STATSLLINE() : IRPL(241, "") {};
RPL_STATSLLINE::~RPL_STATSLLINE(void) {};

// nb:242
// short for:RPL_STATSUPTIME::RPL_STATSUPTIME
// desc:RFC1459 	:Server Up <days> days <hours>:<minutes>:<seconds> 	Reply to
// STATS (See RFC)
RPL_STATSUPTIME::RPL_STATSUPTIME() : IRPL(242, "") {};
RPL_STATSUPTIME::~RPL_STATSUPTIME(void) {};

// nb:243
// short for:RPL_STATSOLINE::RPL_STATSOLINE
// desc:RFC1459 	O <hostmask> * <nick> [:<info>] 	Reply to STATS (See
// RFC); The info field is an extension found in some IRC daemons, which returns
// info such as an e-mail address or the name/job of an operator
RPL_STATSOLINE::RPL_STATSOLINE() : IRPL(243, "") {};
RPL_STATSOLINE::~RPL_STATSOLINE(void) {};

// nb:244
// short for:RPL_STATSHLINE::RPL_STATSHLINE
// desc:RFC1459 	H <hostmask> * <servername> 	Reply to STATS (See RFC)
RPL_STATSHLINE::RPL_STATSHLINE() : IRPL(244, "") {};
RPL_STATSHLINE::~RPL_STATSHLINE(void) {};

// nb:246
// short for:RPL_STATSPING::RPL_STATSPING
// desc:RFC2812
RPL_STATSPING::RPL_STATSPING() : IRPL(246, "") {};
RPL_STATSPING::~RPL_STATSPING(void) {};

// nb:247
// short for:RPL_STATSBLINE::RPL_STATSBLINE
// desc:RFC2812
RPL_STATSBLINE::RPL_STATSBLINE() : IRPL(247, "") {};
RPL_STATSBLINE::~RPL_STATSBLINE(void) {};

// nb:249
// short for:RPL_STATSULINE::RPL_STATSULINE
// desc:Extension to RFC1459?
RPL_STATSULINE::RPL_STATSULINE() : IRPL(249, "") {};
RPL_STATSULINE::~RPL_STATSULINE(void) {};

// nb:250
// short for:RPL_STATSDLINE::RPL_STATSDLINE
// desc:RFC2812
RPL_STATSDLINE::RPL_STATSDLINE() : IRPL(250, "") {};
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
RPL_LUSEROP::RPL_LUSEROP(int nb_ops) : IRPL(252, "") {
	IRPL::string = to_string(nb_ops) + " :There are " + to_string(nb_ops) +
				   " IRC operators online";
};
RPL_LUSEROP::~RPL_LUSEROP(void) {};

// nb:253
// short for:RPL_LUSERUNKNOWN
// desc:RFC1459 	<int> :<info> 	Reply to LUSERS command - Number of
// unknown/unregistered connections
RPL_LUSERUNKNOWN::RPL_LUSERUNKNOWN(int nb_user_unk) : IRPL(253, "") {
	IRPL::string = to_string(nb_user_unk) + " :There are " +
				   to_string(nb_user_unk) + " unknown/unregistered connections";
};
RPL_LUSERUNKNOWN::~RPL_LUSERUNKNOWN(void) {};

// nb:254
// short for:RPL_LUSERCHANNELS
// desc:RFC1459 	<int> :<info> 	Reply to LUSERS command - Number of channels
// formed
RPL_LUSERCHANNELS::RPL_LUSERCHANNELS(int nb_chan) : IRPL(254, "") {
	IRPL::string = to_string(nb_chan) + " :There are " + to_string(nb_chan) +
				   " channels formed";
};
RPL_LUSERCHANNELS::~RPL_LUSERCHANNELS(void) {};

// nb:255
// short for:RPL_LUSERME
// desc:RFC1459 	:I have <int> clients and <int> servers 	Reply to LUSERS
// command - Information about local connections; Text may vary.
RPL_LUSERME::RPL_LUSERME(int nb_clients, int nb_server) : IRPL(255, "") {
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
	: IRPL(256, "") {
		  // TODO: implement
	  };
RPL_ADMINME::~RPL_ADMINME(void) {};

// nb:257
// short for:RPL_ADMINLOC1
// desc:RFC1459 	:<admin_location> 	Reply to ADMIN command (Location, first
// line)
RPL_ADMINLOC::RPL_ADMINLOC()
	: IRPL(257, "") {
		  // TODO: implement
	  };
RPL_ADMINLOC::~RPL_ADMINLOC(void) {};

// nb:258
// short for:RPL_ADMINLOC2
// desc:RFC1459 	:<admin_location> 	Reply to ADMIN command (Location, second
// line)
RPL_ADMINLOC2::RPL_ADMINLOC2()
	: IRPL(258, "") {
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
	: IRPL(261, "") {
		  // TODO: implement
	  };
RPL_TRACELOG::~RPL_TRACELOG(void) {};

// nb:262
// short for:RPL_TRACEPING
// desc:Extension to RFC1459?
RPL_TRACEPING::RPL_TRACEPING()
	: IRPL(262, "") {
		  // TODO: implement - ping related?
	  };
RPL_TRACEPING::~RPL_TRACEPING(void) {};

// nb:262
// short for:RPL_TRACEEND
// desc:RFC2812 	<server_name> <version>[.<debug_level>] :<info> 	Used to
// terminate a list of RPL_TRACE* replies
//   code is the same as RPL_TRACEPING? might be a bug in what I read
RPL_TRACEEND::RPL_TRACEEND()
	: IRPL(262, "") {
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
RPL_NONE::RPL_NONE() : IRPL(300, "") {}; // empty string
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
	: IRPL(302, "") {
		  // TODO: implement
	  };
RPL_USERHOST::~RPL_USERHOST(void) {};

// nb:303
// short for:RPL_ISON
// desc:RFC1459 	:*1<nick> *( ' ' <nick> ) 	Reply to the ISON command (see
// RFC)
RPL_ISON::RPL_ISON()
	: IRPL(303, "") {
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
RPL_WHOISUSER::RPL_WHOISUSER()
	: IRPL(311, "") {
		  // TODO: implement with whois cmd
	  };
RPL_WHOISUSER::~RPL_WHOISUSER(void) {};

// nb:312
// short for:RPL_WHOISSERVER
// desc:RFC1459 	<nick> <server> :<server_info> 	Reply to WHOIS - What server
// they're on
RPL_WHOISSERVER::RPL_WHOISSERVER()
	: IRPL(312, "") {
		  // TODO: implement with whois cmd
	  };
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
RPL_WHOWASUSER::RPL_WHOWASUSER()
	: IRPL(314, "") {
		  // TODO: implement with whois cmd
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
	: IRPL(317, nick + " " + to_string(secs) + " :seconds idle") {};
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
RPL_WHOISCHANNELS::RPL_WHOISCHANNELS(const std::string &nick /* channels */)
	: IRPL(319, nick + " :") {
		  // TODO: implement
	  };
RPL_WHOISCHANNELS::~RPL_WHOISCHANNELS(void) {};

// nb:321
// short for:RPL_LISTSTART
// desc:RFC1459 	Channels :Users Name 	Channel list - Header
RPL_LISTSTART::RPL_LISTSTART() : IRPL(321, "Channels: Users Name") {};
RPL_LISTSTART::~RPL_LISTSTART(void) {};

// nb:322
// short for:RPL_LIST
// desc:RFC1459 	<channel> <#_visible> :<topic> 	Channel list - A channel
RPL_LIST::RPL_LIST(/* (Channel *) or ChannelState? */) : IRPL(322, "") {
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
RPL_CHANNELMODEIS::RPL_CHANNELMODEIS() : IRPL(324, "") {};
RPL_CHANNELMODEIS::~RPL_CHANNELMODEIS(void) {};

// nb:325
// short for:RPL_UNIQOPIS
// desc:RFC2812 	<channel> <nickname>
RPL_UNIQOPIS::RPL_UNIQOPIS()
	: IRPL(325, "") {
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
// RPL_INVITED::RPL_INVITED() : IRPL(000, "") {};
// RPL_INVITED::~RPL_INVITED(void) {};

// // nb:346
// // short for:RPL_INVITELIST
// // desc:RFC2812 	<channel> <invitemask> 	An invite mask for the invite mask
// // list
// RPL_INVITELIST::RPL_INVITELIST() : IRPL(000, "") {};
// RPL_INVITELIST::~RPL_INVITELIST(void) {};

// // nb:347
// // short for:RPL_ENDOFINVITELIST
// // desc:RFC2812 	<channel> :<info> 	Termination of an RPL_INVITELIST list
// RPL_ENDOFINVITELIST::RPL_ENDOFINVITELIST() : IRPL(000, "") {};
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
RPL_VERSION::RPL_VERSION() : IRPL(351, "") {};
RPL_VERSION::~RPL_VERSION(void) {};

// nb:352
// short for:RPL_WHOREPLY
// desc:RFC1459 	<channel> <user> <host> <server> <nick> <H|G>[*][@|+]
// :<hopcount> <real_name> 	Reply to vanilla WHO (See RFC). This format can be
// very different if the 'WHOX' version of the command is used (see ircu).
RPL_WHOREPLY::RPL_WHOREPLY() : IRPL(000, "") {};
RPL_WHOREPLY::~RPL_WHOREPLY(void) {};

// nb:353
// short for:RPL_NAMREPLY
// desc:RFC1459 	( '=' / '*' / '@' ) <channel> ' ' : [ '@' / '+' ] <nick> *(
// ' ' [ '@' / '+' ] <nick> ) 	Reply to NAMES (See RFC)
RPL_NAMREPLY::RPL_NAMREPLY() : IRPL(000, "") {};
RPL_NAMREPLY::~RPL_NAMREPLY(void) {};

// nb:361
// short for:RPL_KILLDONE
// desc:RFC1459
RPL_KILLDONE::RPL_KILLDONE() : IRPL(361, "") {};
RPL_KILLDONE::~RPL_KILLDONE(void) {};

// nb:362
// short for:RPL_CLOSING
// desc:RFC1459
RPL_CLOSING::RPL_CLOSING() : IRPL(362, "") {};
RPL_CLOSING::~RPL_CLOSING(void) {};

// nb:363
// short for:RPL_CLOSEEND
// desc:RFC1459
RPL_CLOSEEND::RPL_CLOSEEND() : IRPL(363, "") {};
RPL_CLOSEEND::~RPL_CLOSEEND(void) {};

// nb:364
// short for:RPL_LINKS
// desc:RFC1459 	<mask> <server> :<hopcount> <server_info> 	Reply to the
// LINKS command
RPL_LINKS::RPL_LINKS() : IRPL(000, "") {};
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

// nb:367
// short for:RPL_BANLIST
// desc:RFC1459 	<channel> <banid> [<time_left> :<reason>] 	A ban-list item
// (See RFC); <time left> and <reason> are additions used by KineIRCd
RPL_BANLIST::RPL_BANLIST() : IRPL(000, "") {};
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
RPL_INFOSTART::RPL_INFOSTART() : IRPL(373, "") {};
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

////////////////////////////////////////////////////////////////////////////////
//									 ------									  //
//									 errors									  //
//									 ------									  //
////////////////////////////////////////////////////////////////////////////////

ERR_UNKNOWNCOMMAND::ERR_UNKNOWNCOMMAND(const std::string &cmd_predicate)
	: IError(421, cmd_predicate + ": Unknown command") {};
ERR_UNKNOWNCOMMAND::~ERR_UNKNOWNCOMMAND(void) throw() {}

ERR_NONICKNAMEGIVEN::ERR_NONICKNAMEGIVEN() : IError(431, "No nick given") {};
ERR_NONICKNAMEGIVEN::~ERR_NONICKNAMEGIVEN() throw() {}

ERR_ERRONEUSNICKNAME::ERR_ERRONEUSNICKNAME(const std::string &nick)
	: IError(432, nick + ": Erroneous nickname") {}
ERR_ERRONEUSNICKNAME::~ERR_ERRONEUSNICKNAME(void) throw() {}

ERR_NICKNAMEINUSE::ERR_NICKNAMEINUSE(const std::string &nick)
	: IError(433, nick + ": Nickname is already in use") {}
ERR_NICKNAMEINUSE::~ERR_NICKNAMEINUSE(void) throw() {}

ERR_NEEDMOREPARAMS::ERR_NEEDMOREPARAMS(const std::string &cmd)
	: IError(461, cmd + ": Not enough parameters") {}
ERR_NEEDMOREPARAMS::~ERR_NEEDMOREPARAMS(void) throw() {}

ERR_ALREADYREGISTERED::ERR_ALREADYREGISTERED()
	: IError(462, "You may not reregister") {};
ERR_ALREADYREGISTERED::~ERR_ALREADYREGISTERED(void) throw() {}

ERR_PASSWDMISMATCH::ERR_PASSWDMISMATCH() : IError(464, "Password incorrect") {};
ERR_PASSWDMISMATCH::~ERR_PASSWDMISMATCH(void) throw() {}
