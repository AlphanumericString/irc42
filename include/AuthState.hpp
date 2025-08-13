/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AuthState.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoulard <bgoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:37:45 by bgoulard          #+#    #+#             */
/*   Updated: 2025/08/13 14:53:43 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma	once

// maybe in a class if we add util functions to this
// even if they're all static

typedef enum AuthState {
	AUTH_NO,
	AUTH_OK,
} t_authState ;	//authentication status,
