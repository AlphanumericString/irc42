/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShellServer.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoulard <bgoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:43:49 by bgoulard          #+#    #+#             */
/*   Updated: 2025/07/08 14:43:49 by bgoulard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <vector>

#include "Server.hpp"

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
