/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRPL.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoulard <bgoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 13:41:54 by bgoulard          #+#    #+#             */
/*   Updated: 2025/08/15 13:41:54 by bgoulard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdexcept>
#include <string>

#include "Client.hpp"
#include "Server.hpp"

class IRPL {
  public:
	IRPL(int code, std::string desc) : _code(code), string(desc) {
		if (_code < 0 || _code > 999)
			throw std::invalid_argument("IRPL code must be between 0 and 999");
		if (string.empty())
			throw std::invalid_argument("IRPL description cannot be empty");
	}
	IRPL(const IRPL &other) : _code(other._code), string(other.string) {};
	IRPL &operator=(const IRPL &other) {
		if (this != &other) {
			_code = other._code;
			string = other.string;
		}
		return *this;
	}
	virtual ~IRPL() {};
	virtual std::string toString(const Server &s, const Client &c);

  protected:
	int			_code;
	std::string string;
};

/*
*
# 	Name 	Origin 	Format 	Comments
001 	RPL_WELCOME 	RFC2812 	:Welcome to the Internet Relay Network <nick>!<user>@<host> 	The first message sent after client registration. The text used varies widely
002 	RPL_YOURHOST 	RFC2812 	:Your host is <servername>, running version <version> 	Part of the post-registration greeting. Text varies widely
003 	RPL_CREATED 	RFC2812 	:This server was created <date> 	Part of the post-registration greeting. Text varies widely
004 	RPL_MYINFO 	RFC2812 	<server_name> <version> <user_modes> <chan_modes> 	Part of the post-registration greeting
005 	RPL_BOUNCE 	RFC2812 	:Try server <server_name>, port <port_number> 	Sent by the server to a user to suggest an alternative server, sometimes used when the connection is refused because the server is already full. Also known as RPL_SLINE (AustHex), and RPL_REDIR Also see #010.

200 	RPL_TRACELINK 	RFC1459 	Link <version>[.<debug_level>] <destination> <next_server> [V<protocol_version> <link_uptime_in_seconds> <backstream_sendq> <upstream_sendq>] 	See RFC
201 	RPL_TRACECONNECTING 	RFC1459 	Try. <class> <server> 	See RFC
202 	RPL_TRACEHANDSHAKE 	RFC1459 	H.S. <class> <server> 	See RFC
203 	RPL_TRACEUNKNOWN 	RFC1459 	???? <class> [<connection_address>] 	See RFC
204 	RPL_TRACEOPERATOR 	RFC1459 	Oper <class> <nick> 	See RFC
205 	RPL_TRACEUSER 	RFC1459 	User <class> <nick> 	See RFC
206 	RPL_TRACESERVER 	RFC1459 	Serv <class> <int>S <int>C <server> <nick!user|*!*>@<host|server> [V<protocol_version>] 	See RFC
207 	RPL_TRACESERVICE 	RFC2812 	Service <class> <name> <type> <active_type> 	See RFC
208 	RPL_TRACENEWTYPE 	RFC1459 	<newtype> 0 <client_name> 	See RFC
209 	RPL_TRACECLASS 	RFC2812 	Class <class> <count> 	See RFC
210 	RPL_TRACERECONNECT 	RFC2812
211 	RPL_STATSLINKINFO 	RFC1459 	<linkname> <sendq> <sent_msgs> <sent_bytes> <recvd_msgs> <rcvd_bytes> <time_open> 	Reply to STATS (See RFC)
212 	RPL_STATSCOMMANDS 	RFC1459 	<command> <count> [<byte_count> <remote_count>] 	Reply to STATS (See RFC)
213 	RPL_STATSCLINE 	RFC1459 	C <host> * <name> <port> <class> 	Reply to STATS (See RFC)
214 	RPL_STATSNLINE 	RFC1459 	N <host> * <name> <port> <class> 	Reply to STATS (See RFC), Also known as RPL_STATSOLDNLINE (ircu, Unreal)
215 	RPL_STATSILINE 	RFC1459 	I <host> * <host> <port> <class> 	Reply to STATS (See RFC)
216 	RPL_STATSKLINE 	RFC1459 	K <host> * <username> <port> <class> 	Reply to STATS (See RFC)
217 	RPL_STATSQLINE 	RFC1459
// other ref: 217 	RPL_STATSPLINE 	ircu
218 	RPL_STATSYLINE 	RFC1459 	Y <class> <ping_freq> <connect_freq> <max_sendq> 	Reply to STATS (See RFC)
219 	RPL_ENDOFSTATS 	RFC1459 	<query> :<info> 	End of RPL_STATS* list.
221 	RPL_UMODEIS 	RFC1459 	<user_modes> [<user_mode_params>] 	Information about a user's own modes. Some daemons have extended the mode command and certain modes take parameters (like channel modes).
231 	RPL_SERVICEINFO 	RFC1459
232 	RPL_ENDOFSERVICES 	RFC1459
233 	RPL_SERVICE 	RFC1459
234 	RPL_SERVLIST 	RFC2812 	<name> <server> <mask> <type> <hopcount> <info> 	A service entry in the service list
235 	RPL_SERVLISTEND 	RFC2812 	<mask> <type> :<info> 	Termination of an RPL_SERVLIST list
240 	RPL_STATSVLINE 	RFC2812
241 	RPL_STATSLLINE 	RFC1459 	L <hostmask> * <servername> <maxdepth> 	Reply to STATS (See RFC)
242 	RPL_STATSUPTIME 	RFC1459 	:Server Up <days> days <hours>:<minutes>:<seconds> 	Reply to STATS (See RFC)
243 	RPL_STATSOLINE 	RFC1459 	O <hostmask> * <nick> [:<info>] 	Reply to STATS (See RFC); The info field is an extension found in some IRC daemons, which returns info such as an e-mail address or the name/job of an operator
244 	RPL_STATSHLINE 	RFC1459 	H <hostmask> * <servername> 	Reply to STATS (See RFC)
246 	RPL_STATSPING 	RFC2812
247 	RPL_STATSBLINE 	RFC2812
249 	RPL_STATSULINE 			Extension to RFC1459?
250 	RPL_STATSDLINE 	RFC2812
251 	RPL_LUSERCLIENT 	RFC1459 	:There are <int> users and <int> invisible on <int> servers 	Reply to LUSERS command, other versions exist (eg. RFC2812); Text may vary.
252 	RPL_LUSEROP 	RFC1459 	<int> :<info> 	Reply to LUSERS command - Number of IRC operators online
253 	RPL_LUSERUNKNOWN 	RFC1459 	<int> :<info> 	Reply to LUSERS command - Number of unknown/unregistered connections
254 	RPL_LUSERCHANNELS 	RFC1459 	<int> :<info> 	Reply to LUSERS command - Number of channels formed
255 	RPL_LUSERME 	RFC1459 	:I have <int> clients and <int> servers 	Reply to LUSERS command - Information about local connections; Text may vary.
256 	RPL_ADMINME 	RFC1459 	<server> :<info> 	Start of an RPL_ADMIN* reply. In practise, the server parameter is often never given, and instead the info field contains the text 'Administrative info about <server>'. Newer daemons seem to follow the RFC and output the server's hostname in the 'server' parameter, but also output the server name in the text as per traditional daemons.
257 	RPL_ADMINLOC1 	RFC1459 	:<admin_location> 	Reply to ADMIN command (Location, first line)
258 	RPL_ADMINLOC2 	RFC1459 	:<admin_location> 	Reply to ADMIN command (Location, second line)
259 	RPL_ADMINEMAIL 	RFC1459 	:<email_address> 	Reply to ADMIN command (E-mail address of administrator)
261 	RPL_TRACELOG 	RFC1459 	File <logfile> <debug_level> 	See RFC
262 	RPL_TRACEPING 			Extension to RFC1459?
262 	RPL_TRACEEND 	RFC2812 	<server_name> <version>[.<debug_level>] :<info> 	Used to terminate a list of RPL_TRACE* replies
263 	RPL_TRYAGAIN 	RFC2812 	<command> :<info> 	When a server drops a command without processing it, it MUST use this reply. Also known as RPL_LOAD_THROTTLED and RPL_LOAD2HI, I'm presuming they do the same thing.

300 	RPL_NONE 	RFC1459 		Dummy reply, supposedly only used for debugging/testing new features, however has appeared in production daemons.
301 	RPL_AWAY 	RFC1459 	<nick> :<message> 	Used in reply to a command directed at a user who is marked as away
302 	RPL_USERHOST 	RFC1459 	:*1<reply> *( ' ' <reply> ) 	Reply used by USERHOST (see RFC)
303 	RPL_ISON 	RFC1459 	:*1<nick> *( ' ' <nick> ) 	Reply to the ISON command (see RFC)
304 	RPL_TEXT
305 	RPL_UNAWAY 	RFC1459 	:<info> 	Reply from AWAY when no longer marked as away
306 	RPL_NOWAWAY 	RFC1459 	:<info> 	Reply from AWAY when marked away
307 	RPL_USERIP
311 	RPL_WHOISUSER 	RFC1459 	<nick> <user> <host> * :<real_name> 	Reply to WHOIS - Information about the user
312 	RPL_WHOISSERVER 	RFC1459 	<nick> <server> :<server_info> 	Reply to WHOIS - What server they're on
313 	RPL_WHOISOPERATOR 	RFC1459 	<nick> :<privileges> 	Reply to WHOIS - User has IRC Operator privileges
314 	RPL_WHOWASUSER 	RFC1459 	<nick> <user> <host> * :<real_name> 	Reply to WHOWAS - Information about the user
315 	RPL_ENDOFWHO 	RFC1459 	<name> :<info> 	Used to terminate a list of RPL_WHOREPLY replies
316 	RPL_WHOISCHANOP 	RFC1459
317 	RPL_WHOISIDLE 	RFC1459 	<nick> <seconds> :seconds idle 	Reply to WHOIS - Idle information
318 	RPL_ENDOFWHOIS 	RFC1459 	<nick> :<info> 	Reply to WHOIS - End of list
319 	RPL_WHOISCHANNELS 	RFC1459 	<nick> :*( ( '@' / '+' ) <channel> ' ' ) 	Reply to WHOIS - Channel list for user (See RFC)
321 	RPL_LISTSTART 	RFC1459 	Channels :Users Name 	Channel list - Header
322 	RPL_LIST 	RFC1459 	<channel> <#_visible> :<topic> 	Channel list - A channel
323 	RPL_LISTEND 	RFC1459 	:<info> 	Channel list - End of list
324 	RPL_CHANNELMODEIS 	RFC1459 	<channel> <mode> <mode_params>
325 	RPL_UNIQOPIS 	RFC2812 	<channel> <nickname>
331 	RPL_NOTOPIC 	RFC1459 	<channel> :<info> 	Response to TOPIC when no topic is set
332 	RPL_TOPIC 	RFC1459 	<channel> :<topic> 	Response to TOPIC with the set topic
341 	RPL_INVITING 	RFC1459 	<nick> <channel> 	Returned by the server to indicate that the attempted INVITE message was successful and is being passed onto the end client. Note that RFC1459 documents the parameters in the reverse order. The format given here is the format used on production servers, and should be considered the standard reply above that given by RFC1459.
342 	RPL_SUMMONING 	RFC1459 	<user> :<info> 	Returned by a server answering a SUMMON message to indicate that it is summoning that user
345 	RPL_INVITED 	GameSurge 	<channel> <user being invited> <user issuing invite> :<user being invited> has been invited by <user issuing invite> 	Sent to users on a channel when an INVITE command has been issued
346 	RPL_INVITELIST 	RFC2812 	<channel> <invitemask> 	An invite mask for the invite mask list
347 	RPL_ENDOFINVITELIST 	RFC2812 	<channel> :<info> 	Termination of an RPL_INVITELIST list
348 	RPL_EXCEPTLIST 	RFC2812 	<channel> <exceptionmask> 	An exception mask for the exception mask list. Also known as RPL_EXLIST (Unreal, Ultimate)
349 	RPL_ENDOFEXCEPTLIST 	RFC2812 	<channel> :<info> 	Termination of an RPL_EXCEPTLIST list. Also known as RPL_ENDOFEXLIST (Unreal, Ultimate)
351 	RPL_VERSION 	RFC1459 	<version>[.<debuglevel>] <server> :<comments> 	Reply by the server showing its version details, however this format is not often adhered to
352 	RPL_WHOREPLY 	RFC1459 	<channel> <user> <host> <server> <nick> <H|G>[*][@|+] :<hopcount> <real_name> 	Reply to vanilla WHO (See RFC). This format can be very different if the 'WHOX' version of the command is used (see ircu).
353 	RPL_NAMREPLY 	RFC1459 	( '=' / '*' / '@' ) <channel> ' ' : [ '@' / '+' ] <nick> *( ' ' [ '@' / '+' ] <nick> ) 	Reply to NAMES (See RFC)
361 	RPL_KILLDONE 	RFC1459
362 	RPL_CLOSING 	RFC1459
363 	RPL_CLOSEEND 	RFC1459
364 	RPL_LINKS 	RFC1459 	<mask> <server> :<hopcount> <server_info> 	Reply to the LINKS command
365 	RPL_ENDOFLINKS 	RFC1459 	<mask> :<info> 	Termination of an RPL_LINKS list
366 	RPL_ENDOFNAMES 	RFC1459 	<channel> :<info> 	Termination of an RPL_NAMREPLY list
367 	RPL_BANLIST 	RFC1459 	<channel> <banid> [<time_left> :<reason>] 	A ban-list item (See RFC); <time left> and <reason> are additions used by KineIRCd
368 	RPL_ENDOFBANLIST 	RFC1459 	<channel> :<info> 	Termination of an RPL_BANLIST list
369 	RPL_ENDOFWHOWAS 	RFC1459 	<nick> :<info> 	Reply to WHOWAS - End of list
371 	RPL_INFO 	RFC1459 	:<string> 	Reply to INFO
372 	RPL_MOTD 	RFC1459 	:- <string> 	Reply to MOTD
373 	RPL_INFOSTART 	RFC1459
374 	RPL_ENDOFINFO 	RFC1459 	:<info> 	Termination of an RPL_INFO list
375 	RPL_MOTDSTART 	RFC1459 	:- <server> Message of the day - 	Start of an RPL_MOTD list
376 	RPL_ENDOFMOTD 	RFC1459 	:<info> 	Termination of an RPL_MOTD list
381 	RPL_YOUREOPER 	RFC1459 	:<info> 	Successful reply from OPER
382 	RPL_REHASHING 	RFC1459 	<config_file> :<info> 	Successful reply from REHASH
383 	RPL_YOURESERVICE 	RFC2812 	:You are service <service_name> 	Sent upon successful registration of a service
384 	RPL_MYPORTIS 	RFC1459
391 	RPL_TIME 	RFC1459 	<server> :<time string> 	Response to the TIME command. The string format may vary greatly. Also see #679.
392 	RPL_USERSSTART 	RFC1459 	:UserID Terminal Host 	Start of an RPL_USERS list
393 	RPL_USERS 	RFC1459 	:<username> <ttyline> <hostname> 	Response to the USERS command (See RFC)
394 	RPL_ENDOFUSERS 	RFC1459 	:<info> 	Termination of an RPL_USERS list
395 	RPL_NOUSERS 	RFC1459 	:<info> 	Reply to USERS when nobody is logged in

401 	ERR_NOSUCHNICK 	RFC1459 	<nick> :<reason> 	Used to indicate the nickname parameter supplied to a command is currently unused
402 	ERR_NOSUCHSERVER 	RFC1459 	<server> :<reason> 	Used to indicate the server name given currently doesn't exist
403 	ERR_NOSUCHCHANNEL 	RFC1459 	<channel> :<reason> 	Used to indicate the given channel name is invalid, or does not exist
404 	ERR_CANNOTSENDTOCHAN 	RFC1459 	<channel> :<reason> 	Sent to a user who does not have the rights to send a message to a channel
405 	ERR_TOOMANYCHANNELS 	RFC1459 	<channel> :<reason> 	Sent to a user when they have joined the maximum number of allowed channels and they tried to join another channel
406 	ERR_WASNOSUCHNICK 	RFC1459 	<nick> :<reason> 	Returned by WHOWAS to indicate there was no history information for a given nickname
407 	ERR_TOOMANYTARGETS 	RFC1459 	<target> :<reason> 	The given target(s) for a command are ambiguous in that they relate to too many targets
408 	ERR_NOSUCHSERVICE 	RFC2812 	<service_name> :<reason> 	Returned to a client which is attempting to send an SQUERY (or other message) to a service which does not exist
409 	ERR_NOORIGIN 	RFC1459 	:<reason> 	PING or PONG message missing the originator parameter which is required since these commands must work without valid prefixes
411 	ERR_NORECIPIENT 	RFC1459 	:<reason> 	Returned when no recipient is given with a command
412 	ERR_NOTEXTTOSEND 	RFC1459 	:<reason> 	Returned when NOTICE/PRIVMSG is used with no message given
413 	ERR_NOTOPLEVEL 	RFC1459 	<mask> :<reason> 	Used when a message is being sent to a mask without being limited to a top-level domain (i.e. * instead of *.au)
414 	ERR_WILDTOPLEVEL 	RFC1459 	<mask> :<reason> 	Used when a message is being sent to a mask with a wild-card for a top level domain (i.e. *.*)
415 	ERR_BADMASK 	RFC2812 	<mask> :<reason> 	Used when a message is being sent to a mask with an invalid syntax
416 	ERR_TOOMANYMATCHES 	IRCnet 	<command> [<mask>] :<info> 	Returned when too many matches have been found for a command and the output has been truncated. An example would be the WHO command, where by the mask '*' would match everyone on the network! Ouch!
421 	ERR_UNKNOWNCOMMAND 	RFC1459 	<command> :<reason> 	Returned when the given command is unknown to the server (or hidden because of lack of access rights)
422 	ERR_NOMOTD 	RFC1459 	:<reason> 	Sent when there is no MOTD to send the client
423 	ERR_NOADMININFO 	RFC1459 	<server> :<reason> 	Returned by a server in response to an ADMIN request when no information is available. RFC1459 mentions this in the list of numerics. While it's not listed as a valid reply in section 4.3.7 ('Admin command'), it's confirmed to exist in the real world.
424 	ERR_FILEERROR 	RFC1459 	:<reason> 	Generic error message used to report a failed file operation during the processing of a command
431 	ERR_NONICKNAMEGIVEN 	RFC1459 	:<reason> 	Returned when a nickname parameter expected for a command isn't found
432 	ERR_ERRONEUSNICKNAME 	RFC1459 	<nick> :<reason> 	Returned after receiving a NICK message which contains a nickname which is considered invalid, such as it's reserved ('anonymous') or contains characters considered invalid for nicknames. This numeric is misspelt, but remains with this name for historical reasons :)
433 	ERR_NICKNAMEINUSE 	RFC1459 	<nick> :<reason> 	Returned by the NICK command when the given nickname is already in use
436 	ERR_NICKCOLLISION 	RFC1459 	<nick> :<reason> 	Returned by a server to a client when it detects a nickname collision
437 	ERR_UNAVAILRESOURCE 	RFC2812 	<nick/channel/service> :<reason> 	Return when the target is unable to be reached temporarily, eg. a delay mechanism in play, or a service being offline
441 	ERR_USERNOTINCHANNEL 	RFC1459 	<nick> <channel> :<reason> 	Returned by the server to indicate that the target user of the command is not on the given channel
442 	ERR_NOTONCHANNEL 	RFC1459 	<channel> :<reason> 	Returned by the server whenever a client tries to perform a channel effecting command for which the client is not a member
443 	ERR_USERONCHANNEL 	RFC1459 	<nick> <channel> [:<reason>] 	Returned when a client tries to invite a user to a channel they're already on
444 	ERR_NOLOGIN 	RFC1459 	<user> :<reason> 	Returned by the SUMMON command if a given user was not logged in and could not be summoned
445 	ERR_SUMMONDISABLED 	RFC1459 	:<reason> 	Returned by SUMMON when it has been disabled or not implemented
446 	ERR_USERSDISABLED 	RFC1459 	:<reason> 	Returned by USERS when it has been disabled or not implemented
451 	ERR_NOTREGISTERED 	RFC1459 	:<reason> 	Returned by the server to indicate that the client must be registered before the server will allow it to be parsed in detail
461 	ERR_NEEDMOREPARAMS 	RFC1459 	<command> :<reason> 	Returned by the server by any command which requires more parameters than the number of parameters given
462 	ERR_ALREADYREGISTERED 	RFC1459 	:<reason> 	Returned by the server to any link which attempts to register again
463 	ERR_NOPERMFORHOST 	RFC1459 	:<reason> 	Returned to a client which attempts to register with a server which has been configured to refuse connections from the client's host
464 	ERR_PASSWDMISMATCH 	RFC1459 	:<reason> 	Returned by the PASS command to indicate the given password was required and was either not given or was incorrect
465 	ERR_YOUREBANNEDCREEP 	RFC1459 	:<reason> 	Returned to a client after an attempt to register on a server configured to ban connections from that client
466 	ERR_YOUWILLBEBANNED 	RFC1459 		Sent by a server to a user to inform that access to the server will soon be denied
467 	ERR_KEYSET 	RFC1459 	<channel> :<reason> 	Returned when the channel key for a channel has already been set
471 	ERR_CHANNELISFULL 	RFC1459 	<channel> :<reason> 	Returned when attempting to join a channel which is set +l and is already full
472 	ERR_UNKNOWNMODE 	RFC1459 	<char> :<reason> 	Returned when a given mode is unknown
473 	ERR_INVITEONLYCHAN 	RFC1459 	<channel> :<reason> 	Returned when attempting to join a channel which is invite only without an invitation
474 	ERR_BANNEDFROMCHAN 	RFC1459 	<channel> :<reason> 	Returned when attempting to join a channel a user is banned from
475 	ERR_BADCHANNELKEY 	RFC1459 	<channel> :<reason> 	Returned when attempting to join a key-locked channel either without a key or with the wrong key
476 	ERR_BADCHANMASK 	RFC2812 	<channel> :<reason> 	The given channel mask was invalid
477 	ERR_NOCHANMODES 	RFC2812 	<channel> :<reason> 	Returned when attempting to set a mode on a channel which does not support channel modes, or channel mode changes. Also known as ERR_MODELESS
478 	ERR_BANLISTFULL 	RFC2812 	<channel> <char> :<reason> 	Returned when a channel access list (i.e. ban list etc) is full and cannot be added to
481 	ERR_NOPRIVILEGES 	RFC1459 	:<reason> 	Returned by any command requiring special privileges (eg. IRC operator) to indicate the operation was unsuccessful
482 	ERR_CHANOPRIVSNEEDED 	RFC1459 	<channel> :<reason> 	Returned by any command requiring special channel privileges (eg. channel operator) to indicate the operation was unsuccessful
483 	ERR_CANTKILLSERVER 	RFC1459 	:<reason> 	Returned by KILL to anyone who tries to kill a server
484 	ERR_RESTRICTED 	RFC2812 	:<reason> 	Sent by the server to a user upon connection to indicate the restricted nature of the connection (i.e. usermode +r)
485 	ERR_UNIQOPRIVSNEEDED 	RFC2812 	:<reason> 	Any mode requiring 'channel creator' privileges returns this error if the client is attempting to use it while not a channel creator on the given channel
491 	ERR_NOOPERHOST 	RFC1459 	:<reason> 	Returned by OPER to a client who cannot become an IRC operator because the server has been configured to disallow the client's host
492 	ERR_NOSERVICEHOST 	RFC1459

501 	ERR_UMODEUNKNOWNFLAG 	RFC1459 	:<reason> 	Returned by the server to indicate that a MODE message was sent with a nickname parameter and that the mode flag sent was not recognised
502 	ERR_USERSDONTMATCH 	RFC1459 	:<reason> 	Error sent to any user trying to view or change the user mode for a user other than themselves
*/

// outside
class RPL_CAP : public IRPL {
  public:
	RPL_CAP(const std::string &capabilities);
	virtual ~RPL_CAP(void);
};

#include "IRPL_populated.hpp"
