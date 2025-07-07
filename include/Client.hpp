/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoulard <bgoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 12:58:32 by bgoulard          #+#    #+#             */
/*   Updated: 2025/07/07 12:58:32 by bgoulard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

class	Client
{
	private:

	public:
		// Constructors
		Client() {};
		Client(Client const &original){(void)original;}; // when are we gonna use this ?!
		// Destructors
		~Client() {};
		// Operator overloads
		Client	&operator=(Client const &original){(void)original; return (*this);};
		// Getters
		// Setters
		// Member functions
		// Exceptions
};
