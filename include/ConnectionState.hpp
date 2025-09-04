/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConnectionState.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoulard <bgoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:37:45 by bgoulard          #+#    #+#             */
/*   Updated: 2025/08/06 18:26:15 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

// maybe in a class if we add util functions to this
// maybe moove to client since mostly used by this?

// maybe add a to kick?
// idk... might be usefull to have somthing to drop the connection
#include <ostream>
typedef enum conState {
	NOT_LOGGED = 0,
	REGISTERING = 1,
	REGISTERED = 2,
	TIMED_OUT = 3,
	DISCONNECTING = 4,
	DISCONNECTED = 5,
} t_conState;

std::ostream &operator<<(std::ostream &o, const t_conState &c);

