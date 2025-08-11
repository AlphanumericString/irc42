/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoulard <bgoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:49:12 by bgoulard          #+#    #+#             */
/*   Updated: 2025/08/11 16:57:53 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/// @file Message.hpp
/// @brief

// there are no 'normal' message any message sent in chat rooms are technically
// PRIVMSG to #chat
// this class will be a tokenizer to TMessage (Tokenized Message)

#include "Channel.hpp"

/// @class Message
/// @brief Represents an IRC protocol message.
class	Message {
public:
	Message(Channel& destination);

private:

	Channel&	destination_;
};
