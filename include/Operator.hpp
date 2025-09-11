/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 16:38:34 by apetitco          #+#    #+#             */
/*   Updated: 2025/09/11 10:22:14 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/// @file Operator.hpp
/// @brief
///
/// NOT TO BE CONFUSED WITH CHANNEL OPERATORS !!!

#include "Client.hpp"

/// @class Operator
/// @brief Operators are a specific kind of Client that can disconnect/reconnect
/// the server as well as for another Client to be disconnected.
class Operator : Client {
  public:
	/// @brief Close the connection between the provided Client `client` and the
	/// server.
	/// @param client
	void disconnectClient(Client &client);

	/// @brief
	void disconnectServer();

	/// @brief
	void reconnectServer();

  private:
};
