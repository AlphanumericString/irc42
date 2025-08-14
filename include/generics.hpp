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
#include <vector>
#pragma once

template < typename t > std::string to_string(const t &var) {
	std::stringstream ss;

	ss << var;
	return (ss.str());
}

inline std::vector< std::string > split(const std::string &str_src,
								 const std::string &delimiter) {
	std::vector< std::string > tokens;
	size_t					   pos;
	std::string				   s = str_src;

	while ((pos = s.find(delimiter)) != std::string::npos) {
		tokens.push_back(s.substr(0, pos));
		s.erase(0, pos + delimiter.length());
	}
	tokens.push_back(s);
	return tokens;
}

#define _stringify(x)  #x
#define stringiy(x)	   _stringify(#x)
#define CTAB_SIZE(tab) (sizeof(tab) / sizeof(tab[0]))
#define DBG_LOG(x)	   std::cerr << "[LOG]" << x << std::endl

#define AL_LOW "abcdefghijklmnopqrstuvwxyz"
#define AL_CAP "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define ALPHA  AL_LOW AL_CAP
#define NUM	   "0123456789"
#define ALNUM  ALPHA NUM
