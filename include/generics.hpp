/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generics.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoulard <bgoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:35:22 by bgoulard          #+#    #+#             */
/*   Updated: 2025/07/07 15:35:22 by bgoulard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sstream>

template<typename t>
std::string	to_string(const t &var)
{
	std::stringstream	ss;

	ss << var;
	return (ss.str());
}

#define _stringify(x) #x
#define stringiy(x) _stringify(#x)
#define CTAB_SIZE(tab)	(sizeof(tab) / sizeof(tab[0]))
