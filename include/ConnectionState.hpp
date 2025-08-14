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
typedef enum conState {
	NOT_LOGGED,
	REGISTERING_PASS,
	REGISTERING_NICK,
	REGISTERING_USER,
	REGISTERED,
	TIMED_OUT
} t_conState;
