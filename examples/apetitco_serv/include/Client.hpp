#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>

class Client
{
  private:
	int			_sock_fd;	///< Socket file descriptor.
	std::string	_nick;		///< Nickname.
	std::string _name;		///< Username.
	std::string	_host;		///< Hostname.

  public:
	/// @brief
	Client();
	/// @brief
	/// @param original
	Client(Client const &original); // when are we gonna use this ?!
	/// @brief
	~Client();
	/// @brief
	Client &operator=(Client const &original);
};

#endif // !CLIENT_HPP
