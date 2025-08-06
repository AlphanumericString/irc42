/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShellServerHandler.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoulard <bgoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:43:49 by bgoulard          #+#    #+#             */
/*   Updated: 2025/08/06 18:28:52 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/// @file ShellServerHandler.hpp
/// @brief

#include <string>
#include <vector>

#include "Server.hpp"

/// @class ShellServerHandler
/// @brief
class ShellServerHandler {
  public:
	static void	cmdHandler(Server &serv);

  private:
	typedef enum { DISPLAY_INFO, QUIT, UNKNOWN } ShellServerCmd;
	static ShellServerCmd strToCmd(std::string s, Server &serv);
	static int handle_monitor(std::string s, Server &serv);
	static int handle_quit(std::string s, Server &serv);
	static int handle_test(std::string s, Server &serv);
};
