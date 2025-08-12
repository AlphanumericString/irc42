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
#include <string>

#define MAX_NAME_LEN   200
#define PREFIX_CHARS   "#&"
#define DEFAULT_PREFIX PREFIX_CHARS[0]

class Client;

#define UNUSED __attribute__((unused))

/// @typedef ChanMod
/// @brief Enumeration for the channel modes.
/// @todo Fill Doxygen comments.
typedef enum {	  // need to read doc, make these more explicit
	MODE_UNKNOWN, ///< Unknown mode.
	MODE_L,		  ///< User limit for the channel.
	MODE_T,		  ///< Channel topic.
	MODE_I,		  ///< Invite-only channel.
} ChanMod;

class ChannelOperator;

/// @class Channel
/// @brief Represents a single channel.
///
/// Manages a chat room with its name, topic, modes, member list with their
/// privileges (operator, voice, etc.), and channel-specific settings like
/// user limits or keys. It handles message broadcasting to all members and
/// enforces channel modes.
class Channel {
  public:
	/// @brief
	/// @param name The Channel name.
	Channel(std::string const &name, Client &owner);

	/// @brief Copy constructor
	/// @param original
	Channel(Channel const &original); // when are we gonna use this ?!

	/// @brief Default constructor.
	~Channel();

	/// @brief Accessor for the `channelOperator_` attribute.
	/// @return A constant reference to a Client object.
	Client const &getChannelOperator() const;

	/// @brief Accessor for the `channelOperator_` attribute.
	/// @return A reference to a Client object.
	Client &getChannelOperator();

	/// @brief Assignment operator overload.
	/// @param original The Channel object we want to assign from.
	/// @return A reference to a Channel object.
	Channel &operator=(Channel const &original);

	class ChannelNameTooLongException : std::exception {
	  public:
		const char *what() const throw();
	};

	class ChannelInvalidNameException : std::exception {
	  public:
		const char *what() const throw();
	};

  private:
	/// @brief Default constructor.
	Channel();

	Client &
		channelOperator_; ///< The channel operator (or "owner") of the channel.
	std::string name_;	  ///< The name of the channel.
	std::string topic_;	  ///< Topic.
	ChanMod		mode_;	  ///< Modes.
	// member list with their privileges (operator, voice, etc.),
	//   std::list -> user in the middle can leave when-ever
	//   question is list of pair? list of self defined type?
	//   idk - decision paralisis AAAAAAAAa /hj
	// channel-specific settings like user limits or keys.
};

#undef UNUSED
