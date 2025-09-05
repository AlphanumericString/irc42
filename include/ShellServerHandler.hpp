/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShellServerHandler.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoulard <bgoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:43:49 by bgoulard          #+#    #+#             */
/*   Updated: 2025/08/07 16:02:53 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/// @file ShellServerHandler.hpp
/// @brief

#include <string>

#include "Server.hpp"

/// @class ShellServerHandler
/// @brief
class ShellServerHandler {
  public:
	/// @brief Takes user input and pass it to strToCmd() to process the string.
	///
	/// Prints a prompt to STDOUT, then wait for user input on STDIN before
	/// processing the input string via ShellServerHandler::strToCmd().
	/// @param serv The Server object the command will be sent to.
	static void cmdHandler(Server &serv, std::string line);

  private:
	/// @enum
	typedef enum { DISPLAY_INFO, QUIT, UNKNOWN } ShellServerCmd;

	/// @brief Command to display monitoring information about the 'serv' Server
	/// object.
	/// @param s
	/// @param serv The Server object the command will use to fetch information.
	/// @return
	static int handle_monitor(std::string s, Server &serv);
	static int handle_dbg(std::string s, Server &serv);

	/// @brief Command to shut down the Server object.
	/// @param s
	/// @param serv The Server object the command will shut down.
	/// @return
	static int handle_quit(std::string s, Server &serv);

	/// @brief
	/// @param s
	/// @param serv
	/// @return
	static int handle_test(std::string s, Server &serv);

	/// @brief Parse the string to check for a command to be ran.
	/// @param s The string to parse.
	/// @param serv The Server object the command will be sent to.
	/// @return
	static ShellServerCmd strToCmd(std::string s, Server &serv);
};
