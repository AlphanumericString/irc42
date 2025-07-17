#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>

class Client
{
  private:
	int sock_fd;	//socket file descriptor,
	std::string	nick;	//nickname,
	std::string name;	//username,
	std::string	host;	//hostname,

  public:
	// Constructors
	Client();
	Client(Client const &original); // when are we gonna use this ?!
	// Destructors
	~Client();
	// Operator overloads
	Client &operator=(Client const &original);
	// Getters
	// Setters
	// Member functions
	// Exceptions
};

#endif // !CLIENT_HPP
