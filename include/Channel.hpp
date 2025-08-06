/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoulard <bgoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 12:58:52 by bgoulard          #+#    #+#             */
/*   Updated: 2025/08/06 11:56:33 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#define UNUSED __attribute__((unused))

#include <string>

/// @class Channel
/// @brief Represents a single channel.
class Channel {
  private:
	typedef enum { // need to read doc, make these more explicit
		MODE_UNKNOWN,
		MODE_L,
		MODE_T,
		MODE_I,
	} ChanMod;

	UNUSED std::string name;  // name,
	UNUSED std::string topic; // topic,
	UNUSED ChanMod	   mode;  // modes,
	// member list with their privileges (operator, voice, etc.),
	//   std::list -> user in the middle can leave when-ever
	//   question is list of pair? list of self defined type?
	//   idk - decision paralisis AAAAAAAAa /hj
	// channel-specific settings like user limits or keys.

  public:
	// Constructors
	Channel();
	Channel(Channel const &original); // when are we gonna use this ?!
	// Destructors
	~Channel();
	// Operator overloads
	Channel &operator=(Channel const &original);
	// Getters
	// Setters
	// Member functions
	// Exceptions
};

#undef UNUSED
