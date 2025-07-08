# irc42
irc 42 project

Everything in C++ 98.

Allowed syscalls and functions:

| func | tldr |
|----------------|-----------------|
|socket| create a socket|
|close| close a fd|
|setsockopt| set options on a socket|
|getsockname| get local address of a socket|
|getprotobyname| get protocol by name|
|gethostbyname| get host by name|
|getaddrinfo| get address info for a host|
|freeaddrinfo| free address info|
|bind| bind a socket to an address|
|connect| connect a socket to an address|
|listen| listen for incoming connections|
|accept| accept an incoming connection|
|htons| convert host byte order to network byte order (short)|
|htonl| convert host byte order to network byte order (long)|
|ntohs| convert network byte order to host byte order (short)|
|ntohl| convert network byte order to host byte order (long)|
|inet_addr| convert IPv4 address from text to binary form|
|inet_ntoa| convert IPv4 address from binary to text form|
|send| send data on a socket|
|recv| receive data on a socket|
|signal| set a signal handler|
|sigaction| set a signal handler with options|
|lseek| move the file offset of a file descriptor|
|fstat| get file status information|
|fcntl| manipulate file descriptor flags|
|poll| wait for events on file descriptors|
|epoll| wait for events on file descriptors (Linux specific)|

+ everything in c++98.

anything else is forbidden.
