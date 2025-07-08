/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConectionState.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoulard <bgoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:37:45 by bgoulard          #+#    #+#             */
/*   Updated: 2025/07/08 15:37:45 by bgoulard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma	once

// maybe in a class if we add util functions to this

typedef enum	conState {
	NOT_LOGGED,
	REGISTERING,
	REGISTERED,
	TIMED_OUT
} t_conState;
