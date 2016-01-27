#ifndef WEB_CORE
#define WEB_CORE

#include <netinet/in.h>
#include <string.h>
#include <iostream>

class Server
{
	private:
		int serverSocket,  portNumber, clientLength;
	    struct sockaddr_in serverAddress, clientAddress;

		Server();
		Server(Server const&) = delete;
		void operator = (Server const&) = delete;

		static void threadEntry(int clientSocket);
	
	public:
		static Server& getInstance();
		void start();
};

#endif
