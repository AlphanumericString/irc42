#ifndef SERVER_HPP
#define SERVER_HPP

#include <string>
#include <vector>

#define SERV_PORT "8080"
#define BACKLOG 10

class Server
{
private:
	int							_serverPort;		//-> port listened by the server
	int							_serverSocketFD;	//-> server socket's file descriptor
	std::vector<struct pollfd>	_pollFDs;			//-> vector holding all the pollfds
	
	void	hintsSetUp();

public:
	// Constructors
		Server();
		Server(const Server &);
	// Destructors
		~Server();
	// Operator overloads
		Server &operator=(const Server &);
	// Getters
		int const	&getServerSocketFD() const;
	// Setters
	// Member functions
		void	setUpServer();
		void	work();
	// Exceptions
};

#endif // !SERVER_HPP
