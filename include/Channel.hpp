/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoulard <bgoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 12:58:52 by bgoulard          #+#    #+#             */
/*   Updated: 2025/07/07 12:58:52 by bgoulard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

class	Channel
{
	private:

	public:
		// Constructors
		Channel() {};
		Channel(Channel const &original) {(void)original;};// when are we gonna use this ?!
		// Destructors
		~Channel() {};
		// Operator overloads
		Channel	&operator=(Channel const &original){(void)original; return (*this);};
		// Getters
		// Setters
		// Member functions
		// Exceptions
};
