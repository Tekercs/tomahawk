#ifndef TOMAHAWK_CORE
#define TOMAHAWK_CORE

#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

class Server
{
	private:
		int serverSocket, clientSocket, portNumber, clientLength;
	    struct sockaddr_in serverAddress, clientAddress;
		char buffer[255];

		Server();
		Server(Server const&) = delete;
		void operator = (Server const&) = delete;
	
	public:
		static Server& getInstance();
		void start();
	
};

Server& server()
{
	return Server::getInstance();
}

#endif
