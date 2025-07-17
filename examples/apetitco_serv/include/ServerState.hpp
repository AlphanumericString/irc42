#ifndef SERVERSTATE_HPP
#define SERVERSTATE_HPP

#include <list>
#include <string>

#include "Channel.hpp"
#include <Client.hpp>

class Server;

class ServerState {
  public:
	typedef enum {
		STARTING,
		RUNNING,
		STOPPING,
		// PAUSED, ? maybe
		ERROR
	} Status;

	ServerState(int port, const std::string password, Server &master);
	ServerState &operator=(const ServerState &original);
	bool operator==(const ServerState &original) const;
	bool operator!=(const ServerState &original) const;
	~ServerState();

	std::string const &getName() const;
	std::string const &getPassword() const;
	std::string const		  &getPort() const;
	std::string		   getMinimalInfo(void) const;

	void setStatus(Status status);
	Status getStatus(void) const;

  private:
	ServerState::Status	 _status;
	std::string			 _name;
	std::string			 _password;
	std::string			 _port;
	std::list< Client >	 _clients;
	std::list< Channel > _channels;
	Server				*_master;
};

#endif // !SERVERSTATE_HPP
