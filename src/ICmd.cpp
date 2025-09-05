/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ICmd.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoulard <bgoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 16:08:31 by bgoulard          #+#    #+#             */
/*   Updated: 2025/08/15 16:08:31 by bgoulard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ICmd.hpp"

#include <cstdlib>
#include <vector>

#include "Channel.hpp"
#include "ConnectionState.hpp"
#include "IError_populated.hpp"
#include "IRPL.hpp"
#include "IRPL_populated.hpp"
#include "smart_ptr.hpp"

// ------------
// registration core
// -----------

std::vector< IRPL * > CMD_PASS::execute(Server &s, Client &client) {
	std::vector< IRPL * > ret;

	if (_args.size() < CMD_PASS::minArg)
		ret.push_back(new ERR_NEEDMOREPARAMS(_args[0]));
	else if (client.getConState() >= REGISTERED)
		ret.push_back(new ERR_ALREADYREGISTERED());
	else if (s.getServerState().getPassword().compare(_args[1]) != 0)
		ret.push_back(new ERR_PASSWDMISMATCH());
	if (ret.size() > 0)
		return ret;

	if (client.getConState() < REGISTERED) {
		client.setConState(REGISTERING);
		client.hasPass = true;
	}

	if (client.getConState() == REGISTERING && client.hasNick == true &&
		client.hasUser == true && client.hasPass == true) {
		ret.push_back(new RPL_WELCOME(client.getNick(), client.getHost()));
		ret.push_back(new RPL_YOURHOST());
		ret.push_back(new RPL_CREATED());
		ret.push_back(new RPL_MYINFO());
		client.setConState(REGISTERED);
	}
	return std::vector< IRPL * >(); // return empty aka no response
}

std::vector< IRPL * > CMD_NICK::execute(Server &s, Client &client) {
	std::vector< IRPL * > ret;

	// error checks
	if (_args.size() < CMD_NICK::minArg)
		ret.push_back(new ERR_NONICKNAMEGIVEN());
	for (std::list< Client >::const_iterator it =
			 s.getServerState().getClients().begin();
		 it != s.getServerState().getClients().end() && ret.size() == 0; it++)
		if (it->getNick().compare(_args[1]) == 0)
			ret.push_back(new ERR_NICKNAMEINUSE(_args[1]));

	if (ret.size() > 0)
		return ret;

	try {
		// change nick in copies in channels and other locations
		for (std::list< Channel >::iterator it =
				 s.getServerState().getChannels().begin();
			 it != s.getServerState().getChannels().end(); it++) {
			if (it->hasMember(client) ||
				it->isInvited(client)) // if in channel lists
				it->updateNick(client, _args[1], s);
		}
		RPL_FULLCUSTOM rpl(":" + client.getNick() + " NICK :" + _args[1] +
						   "\r\n");
		client.setNickname(_args[1]); // change self at end
		ret.push_back(new RPL_FULLCUSTOM(rpl));
	} catch (...) {
		ret.push_back(new ERR_ERRONEUSNICKNAME(_args[1]));
		return ret;
	}
	if (client.getConState() < REGISTERED) {
		client.setConState(REGISTERING);
		client.hasNick = true;
	}
	if (client.getConState() == REGISTERING && client.hasNick == true &&
		client.hasPass == true && client.hasUser == true) {
		ret.push_back(new RPL_WELCOME(client.getNick(), client.getHost()));
		ret.push_back(new RPL_YOURHOST());
		ret.push_back(new RPL_CREATED());
		ret.push_back(new RPL_MYINFO());
		client.setConState(REGISTERED);
	}
	return ret;
};

std::vector< IRPL * > CMD_USER::execute(Server &s, Client &client) {
	std::vector< IRPL * > ret;
	std::string			  _real_name;

	if (_raw.find_last_of(":") == std::string::npos ||
		_args.size() < CMD_USER::minArgs)
		ret.push_back(new ERR_NEEDMOREPARAMS(_args[0]));
	else if (client.getConState() >= REGISTERED)
		ret.push_back(new ERR_ALREADYREGISTERED());

	if (ret.size() > 0)
		return ret;
	(void)s;

	_real_name = _args[4].substr(1); // skip leading ':'
	client.setUserName(_args[1]);
	client.setRealname(_real_name);

	const std::string c_hostname = client.getHost();

	if (client.getConState() < REGISTERED) {
		client.setConState(REGISTERING);
		client.hasUser = true;
	}

	if (client.getConState() == REGISTERING && client.hasNick == true &&
		client.hasUser == true && client.hasPass == true) {
		ret.push_back(new RPL_WELCOME(client.getNick(), c_hostname));
		ret.push_back(new RPL_YOURHOST());
		ret.push_back(new RPL_CREATED());
		ret.push_back(new RPL_MYINFO());
		client.setConState(REGISTERED);
	}
	return ret;
}

std::vector< IRPL * > CMD_CAP::execute(Server &s, Client &client) {
	(void)s;
	(void)client;

	std::vector< IRPL * > ret;

	ret.clear(); // make sure it's empty and init as empty
	if (_args.size() < 2)
		ret.push_back(new ERR_NEEDMOREPARAMS(_args[0]));
	else if (_args[1] == "LS")						 // LS -> disponible
		ret.push_back(new RPL_CUSTOM("CAP * LS :")); // no capabilities
	else if (_args[1] == "END") // END -> end of negotiation
		;						// no response
	else
		ret.push_back(
			new RPL_CUSTOM("410 * " + _args[1] + " :Invalid CAP subcommand"));
	return ret;
}

std::vector< IRPL * > CMD_QUIT::execute(Server &s, Client &client) {
	std::vector< IRPL * > ret;
	std::string			  msg = "Client Quit";

	if (_args.size() >= 2) {
		if (_raw.find_last_of(":") != std::string::npos)
			msg = _raw.substr(_raw.find_last_of(":") + 1);
		else
			msg = _args[1];
	}
	// broadcast to all channels the client is part of
	for (std::list< Channel >::iterator it =
			 s.getServerState().getChannels().begin();
		 it != s.getServerState().getChannels().end(); it++) {
		if (it->hasMember(client)) {
			it->broadcast(":" + client.infostr() + " QUIT :" + msg + "\r\n",
						  client, s);
			it->removeMember(client);
		}
	}
	client.setConState(DISCONNECTING);
	return ret;
}

// ------------
// msg core
// -----------

std::vector< IRPL * > CMD_JOIN::execute(Server &s, Client &client) {
	std::vector< IRPL * > ret;
	std::string			  ch_name;
	Channel				 *ch;

	if (client.getConState() != REGISTERED) {
		ret.push_back(new ERR_NOTREGISTERED());
	} else if (_args.size() < 2)
		ret.push_back(new ERR_NEEDMOREPARAMS(_args[0]));
	else if (_args[1][0] != '#')
		ret.push_back(new ERR_NOSUCHCHANNEL(ch_name));
	if (ret.size() > 0)
		return ret;

	ch_name = _args[1];
	ch = s.getServerState().getChannel(ch_name);
	if (ch != NULLPTR) { // chanel exists
		if (ch->hasMember(client) == true) {
			ret.push_back(new ERR_USERONCHANNEL(client.getNick(), ch_name));
			return ret;
		}

		// TODO:
		// check max users
		// check invite only
		// check password
		// check when doing mode

		try {
			ch->addMember(client);
		} catch (std::exception &e) {
			ret.push_back(new ERR_CANNOTSENDTOCHAN(ch_name));
			return ret;
		}
		ret.push_back(new RPL_JOIN(client.infostr(), ch_name));
		ch->broadcast(ret.back()->toString(s, client), client, s);

		if (ch->getMode() & MODE_T)
			ret.push_back(new RPL_TOPIC(ch_name, ch->getTopic()));
		else
			ret.push_back(new RPL_NOTOPIC(ch_name));
		ch->broadcast(ret.back()->toString(s, client), client, s);

		ret.push_back(new RPL_NAMREPLY(ch_name, ch->getMembers(),
									   ch->getOperators(), ch->getMode()));
		ch->broadcast(ret.back()->toString(s, client), client, s);

		ret.push_back(new RPL_ENDOFNAMES(ch_name));
		ch->broadcast(ret.back()->toString(s, client), client, s);

	} else { // create channel
		Channel new_ch(ch_name, client);

		s.getServerState().getChannels().push_back(new_ch);
		ch = s.getServerState().getChannel(ch_name);
		ch->addMember(client);
		ch->addOperator(client);
		ret.push_back(new RPL_JOIN(client.infostr(), ch_name));
		ret.push_back(new RPL_NOTOPIC(ch_name));
		ret.push_back(new RPL_NAMREPLY(ch_name, ch->getMembers(),
									   ch->getOperators(), ch->getMode()));
		ret.push_back(new RPL_ENDOFNAMES(ch_name));
	}
	return ret;
}

std::vector< IRPL * > CMD_PRIVMSG::execute(Server &s, Client &client) {
	std::vector< IRPL * > ret;

	ret.clear();

	if (_args.size() < CMD_PRIVMSG::minArg) // basic errors
		ret.push_back(new ERR_NEEDMOREPARAMS(_args[0]));
	else if (_raw.find_last_of(":") == std::string::npos)
		ret.push_back(new ERR_NOTEXTTOSEND());
	else if (client.getConState() != REGISTERED)
		ret.push_back(new ERR_NOTREGISTERED());
	if (ret.size() > 0)
		return ret;
	std::string target = _args[1];

	if (target.empty())
		ret.push_back(new ERR_NOSUCHNICK(target));
	Channel *ch = NULLPTR;

	ch = s.getServerState().getChannel(target);
	if (target[0] == '#') {
		if (ch == NULLPTR)
			ret.push_back(new ERR_NOSUCHCHANNEL(target));
		else if (ch->hasMember(client) == false)
			ret.push_back(new ERR_CANNOTSENDTOCHAN(target));
		else {
			ch->broadcast(":" + client.infostr() + " PRIVMSG " + target + " :" +
							  _raw.substr(_raw.find_last_of(":") + 1) + "\r\n",
						  client, s);
			client.resetIdleSince(); // valid message, reset idle timer
		}
	} else if (ch == NULLPTR && !ret.size()) {
		Client *cl = NULLPTR;
		cl = s.getServerState().getClient(target);
		if (cl == NULLPTR)
			ret.push_back(new ERR_NOSUCHNICK(target));
		else {
			cl->appendToOutputBuffer(
				":" + client.infostr() + " PRIVMSG " + target + " :" +
				_raw.substr(_raw.find_last_of(":") + 1) + "\r\n");
			client.resetIdleSince(); // valid message, reset idle timer
		}
	}

	return ret;
}

std::vector< IRPL * > CMD_PART::execute(Server &s, Client &client) {
	std::vector< IRPL * > ret;

	if (_args.size() < CMD_PART::minArg) // basic errors
		ret.push_back(new ERR_NEEDMOREPARAMS(_args[0]));
	else if (client.getConState() != REGISTERED)
		ret.push_back(new ERR_NOTREGISTERED());
	else if (_args[1][0] != '#') // < quick filter
		ret.push_back(new ERR_NOSUCHCHANNEL(_args[1]));
	if (ret.size() > 0)
		return ret;

	std::string ch_name = _args[1];
	std::string reason;
	Channel	   *ch = s.getServerState().getChannel(ch_name);

	if (ch == NULLPTR)
		ret.push_back(new ERR_NOSUCHCHANNEL(ch_name));
	else if (ch->hasMember(client) == false)
		ret.push_back(new ERR_NOTONCHANNEL(ch_name));
	if (ret.size() > 0)
		return ret;

	if (_raw.find_last_of(":") != std::string::npos)
		reason = _raw.substr(_raw.find_last_of(":") + 1);
	else if (_args.size() >= 3)
		reason = _args[2];
	else
		reason = "Client parted"; // we try to have a message for certain client
								  // sensible to that

	ret.push_back(new RPL_FULLCUSTOM(":" + client.infostr() + " PART " +
									 ch_name + " :" + reason + "\r\n"));
	ch->broadcast(ret.back()->toString(s, client), client, s);

	ch->removeMember(client);
	if (ch->isOperator(client))
		ch->removeOperator(client);
	if (ch->isEmpty())
		s.getServerState().getChannels().remove(*ch);
	return ret;
}

// ------------
// info core : [whois, whowas, version]
// -----------

std::vector< IRPL * > CMD_WHOIS::execute(Server &s, Client &client) {
	std::vector< IRPL * > ret;

	if (client.getConState() != REGISTERED) // fast check
		ret.push_back(new ERR_NOTREGISTERED());
	else if (_args.size() < CMD_WHOIS::minArg)
		ret.push_back(new ERR_NEEDMOREPARAMS(_args[0]));
	else if (_args[1].empty())
		ret.push_back(new ERR_NONICKNAMEGIVEN());
	else if (_args[1] == "*")
		ret.push_back(new ERR_WILDTOPLEVEL(_args[1]));
	if (ret.size() > 0)
		return ret;

	Client *target = s.getServerState().getClient(_args[1]);
	if (target == NULLPTR) {
		ret.push_back(new ERR_NOSUCHNICK(_args[1]));
		return ret;
	}
	ret.push_back(new RPL_WHOISUSER(target->getNick(), target->getUserName(),
									target->getHost(), target->getRealName()));
	// RPL_WHOISCHANNELS
	std::string ch_list;
	for (std::list< Channel >::iterator it =
			 s.getServerState().getChannels().begin();
		 it != s.getServerState().getChannels().end(); it++) {
		if (it->hasMember(*target)) {
			if (!ch_list.empty())
				ch_list += " ";
			if (it->isOperator(*target))
				ch_list += "@";
			ch_list += it->getName();
		}
	}
	if (!ch_list.empty())
		ret.push_back(new RPL_WHOISCHANNELS(target->getNick(), ch_list));
	ret.push_back(new RPL_WHOISSERVER(target->getNick(),
									  s.getServerState().getName(),
									  s.getServerState().getDescription()));
	ret.push_back(new RPL_WHOISIDLE(target->getNick(), target->getIdleSince()));
	ret.push_back(new RPL_ENDOFWHOIS(target->getNick()));
	return ret;
}

std::vector< IRPL * > CMD_WHOWAS::execute(Server &s, Client &client) {
	std::vector< IRPL * > ret;

	if (client.getConState() != REGISTERED) // fast check
		ret.push_back(new ERR_NOTREGISTERED());
	else if (_args.size() < CMD_WHOWAS::minArg)
		ret.push_back(new ERR_NEEDMOREPARAMS(_args[0]));
	else if (_args[1].empty())
		ret.push_back(new ERR_NONICKNAMEGIVEN());
	if (ret.size() > 0)
		return ret;

	if (_args.size() == 3 && _args[1] != s.getServerState().getName()) {
		ret.push_back(new ERR_NOSUCHSERVER(_args[1]));
		return ret;
	}

	std::vector< PrevClients > prev_clients =
		s.getServerState().getPrevClients(_args[1]);

	if (prev_clients.size() == 0)
		return (ret.push_back(new ERR_WASNOSUCHNICK(_args[1])), ret);

	for (std::vector< PrevClients >::iterator it = prev_clients.begin();
		 it != prev_clients.end(); it++) {
		ret.push_back(new RPL_WHOWASUSER(it->_nick, it->_username,
										 it->_hostname, it->_realname));
		ret.push_back(new RPL_WHOISSERVER(it->_nick,
										  s.getServerState().getName(),
										  s.getServerState().getDescription()));
	}

	ret.push_back(new RPL_ENDOFWHOWAS(_args[1]));

	return ret;
}

std::vector< IRPL * > CMD_PING::execute(Server &s, Client &client) {
	(void)client;

	std::vector< IRPL * > ret;

	if (_args.size() < 2)
		return (ret.push_back(new ERR_NEEDMOREPARAMS(_args[0])), ret);
	if (_args[1].empty() || _args[1].compare(s.getServerState().getName()) != 0)
		return (ret.push_back(new ERR_NOORIGIN()), ret);
	ret.push_back(new RPL_CUSTOM("PONG :" + _args[1]));
	return (ret);
}

std::vector< IRPL * > CMD_VERSION::execute(Server &s, Client &client) {
	(void)s;
	std::vector< IRPL * > ret;

	if (client.getConState() != REGISTERED) // fast check
		ret.push_back(new ERR_NOTREGISTERED());
	if (ret.size() > 0)
		return ret;

	ret.push_back(new RPL_VERSION("ft_irc", "bgoulard", "v1.0"));
	return ret;
}

// ------------
// operator core : [KICK, INVITE, TOPIC, MODE]
// ------------

std::vector< IRPL * > CMD_KICK::execute(Server &s, Client &client) {
	std::vector< IRPL * > ret;

	if (client.getConState() != REGISTERED) // fast check
		ret.push_back(new ERR_NOTREGISTERED());
	else if (_args.size() < CMD_KICK::minArg)
		ret.push_back(new ERR_NEEDMOREPARAMS(_args[0]));
	else if (_args[1].empty() || _args[1][0] != '#')
		ret.push_back(new ERR_NOSUCHCHANNEL(_args[1]));
	if (ret.size() > 0)
		return ret;
	std::string ch_name = _args[1];
	std::string target_name = _args[2];
	std::string msg = "";
	if (_args.size() >= 4) {
		if (_raw.find_last_of(":") != std::string::npos)
			msg = _raw.substr(_raw.find_last_of(":") + 1);
		else
			msg = _args[3];
	} else
		msg = "you got too silly"; // default message if none provided

	Channel *ch = s.getServerState().getChannel(ch_name);
	if (ch == NULLPTR)
		ret.push_back(new ERR_NOSUCHCHANNEL(ch_name));
	else if (ch->hasMember(client) == false)
		ret.push_back(new ERR_NOTONCHANNEL(ch_name));
	else if (ch->isOperator(client) == false)
		ret.push_back(new ERR_CHANOPRIVSNEEDED(ch_name));
	if (ret.size() > 0)
		return ret;
	Client *target = s.getServerState().getClient(target_name);

	if (target == NULLPTR)
		ret.push_back(new ERR_NOSUCHNICK(target_name));
	else if (ch->hasMember(*target) == false)
		ret.push_back(new ERR_USERNOTINCHANNEL(target_name, ch_name));
	if (ret.size() > 0)
		return ret;
	ch->broadcast_full(":" + client.infostr() + " KICK " + ch_name + " " +
						   target_name + ":" + msg + "\r\n",
					   s);
	ch->removeOperator(*target);
	ch->removeMember(*target);
	return ret;
}

// std::vector< IRPL * > CMD_INVITE::execute(Server &s, Client &client) {}
// std::vector< IRPL * > CMD_TOPIC::execute(Server &s, Client &client) {}

// params:
// <channel> {+|-}<modes> {<mode params>}
// ||
// <client> {+|-}<modes> {<mode params>}

static void
args_to_pairs(std::vector< std::pair< ChanMod, std::string > > &mode_changes,
			  const std::vector< std::string > &args, int start) {
	unsigned int offset_arg = start + 1;
	ChanMod		 md;
	std::string	 param;
	bool		 set = (args[start][0] == '+');

	for (unsigned int i = 1; i < args[start].length(); i++) {
		param = "";
		switch (args[start][i]) {
		case 'i':
			md = MODE_I;
			break;
		case 'k':
			md = MODE_K;
			break;
		case 'l':
			md = MODE_L;
			break;
		case 't':
			md = MODE_T;
			break;
		case 'o':
			md = MODE_O;
			break;
		default:
			md = MODE_UNKNOWN;
			break;
		}
		if (set &&
			(md == MODE_L || md == MODE_K || md == MODE_O || md == MODE_T)) {
			if (offset_arg < args.size())
				param = args[offset_arg++];
			else
				throw std::runtime_error("Not enough parameters for " +
										 args[i]);
		}
		if (md == MODE_UNKNOWN)
			throw std::runtime_error("Unknown mode " + args[i]);
		mode_changes.push_back(std::make_pair(md, param));
	}
}

std::vector< IRPL * > CMD_MODE::execute(Server &s, Client &client) {
	std::vector< IRPL * >							 ret;
	std::vector< std::pair< ChanMod, std::string > > mode_changes;

	if (client.getConState() != REGISTERED) // fast check
		ret.push_back(new ERR_NOTREGISTERED());
	else if (_args.size() < CMD_MODE::minArg)
		ret.push_back(new ERR_NEEDMOREPARAMS(_args[0]));
	else if (_args[1].empty())
		ret.push_back(new ERR_NOSUCHCHANNEL(_args[1]));
	if (ret.size() > 0)
		return ret;

	Channel *ch = s.getServerState().getChannel(_args[1]);
	Client	*target = s.getServerState().getClient(_args[1]);
	mode_changes.reserve(MODE_NUMBER);

	try {
		if (_args.size() > 2)
			args_to_pairs(mode_changes, _args, 2);
	} catch (std::exception &e) {
		return (ret.push_back(new ERR_NEEDMOREPARAMS(_args[0])), ret);
	}
	if (ch == NULLPTR && target == NULLPTR) {
		ret.push_back(new ERR_NOSUCHNICK(_args[1]));
	} else if (ch != NULLPTR) {
		if (_args.size() == 2) {
			std::string params = "";
			std::string modes = ch->getModeStrFormat(&params);

			ret.push_back(new RPL_CHANNELMODEIS(ch->getName(), modes, params));
		} else {

			if (_args[2][0] != '+' && _args[2][0] != '-')
				return (ret.push_back(new ERR_UNKNOWNMODE(_args[2])), ret);
			if (ch->hasMember(client) == false)
				return (ret.push_back(new ERR_NOTONCHANNEL(ch->getName())),
						ret);
			if (ch->isOperator(client) == false)
				return (ret.push_back(new ERR_CHANOPRIVSNEEDED(ch->getName())),
						ret);
			// move to internal PRIVATE function
			bool		tpc_change = false;
			bool		set = (_args[2][0] == '+');
			std::string resp_modes = (set ? "+" : "-");
			std::string resp_params = "";

			for (std::vector< std::pair< ChanMod, std::string > >::iterator it =
					 mode_changes.begin();
				 it != mode_changes.end() && ret.size() == 0; it++) {
				switch (it->first) {
				case MODE_I:
					if (set)
						ch->setMode(ch->getMode() | MODE_I);
					else
						ch->unsetMode(MODE_I);
					resp_modes += "i";
					break;
				case MODE_T:
					if (set) {
						ch->setMode(ch->getMode() | MODE_T);
						ch->setTopic(it->second);
						if (!resp_params.empty())
							resp_params += " ";
						resp_params += it->second;
					} else {
						ch->unsetMode(MODE_T);
						ch->setTopic("");
					}
					tpc_change = true;
					resp_modes += "t";
					break;
				case MODE_K:
					if (set) {
						ch->setMode(ch->getMode() | MODE_K);
						ch->setKey(it->second);
						if (!resp_params.empty())
							resp_params += " ";
						resp_params += it->second;
					} else {
						ch->unsetMode(MODE_K);
						ch->setKey("");
					}
					resp_modes += "k";
					break;
				case MODE_L:
					if (set) {
						ch->setMode(ch->getMode() | MODE_L);
						ch->setUserLimit(atoi(it->second.c_str()));
						if (!resp_params.empty())
							resp_params += " ";
						resp_params += it->second;
					} else {
						ch->unsetMode(MODE_L);
						ch->setUserLimit(0);
					}
					resp_modes += "l";
					break;
				case MODE_O:
					try {
						Client &cl = ch->getMember(it->second);
						if (set)
							ch->addOperator(cl);
						else
							ch->removeOperator(cl);
						resp_modes += "o";
						if (!resp_params.empty())
							resp_params += " ";
						resp_params += it->second;
					} catch (...) {
						ret.push_back(new ERR_NOSUCHNICK(it->second));
					}
					break;
				case MODE_NUMBER:
				case MODE_UNKNOWN:
				default:
					ret.push_back(new ERR_UNKNOWNMODE(_args[2]));
					break;
				}
			} // end for
			if (ret.size() > 0)
				return ret;
			if (tpc_change) {
				if (!ch->getTopic().empty())
					ch->broadcast_full(":" + client.infostr() + " TOPIC " +
										   ch->getName() + " :" +
										   ch->getTopic() + "\r\n",
									   s);
				else
					ch->broadcast_full(":" + client.infostr() + " TOPIC " +
										   ch->getName() + " :\r\n",
									   s);
			}
			ch->broadcast_full(
				":" + client.infostr() + " MODE " + ch->getName() + " " +
					resp_modes +
					(resp_params.empty() ? "" : " " + resp_params) + "\r\n",
				s);

		} // end set/unset
	} else { // target is a client
		// unsupported
		ret.push_back(new ERR_UMODEUNKNOWNFLAG());
	}
	return ret;
}
