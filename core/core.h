#ifndef WEB_CORE
#define WEB_CORE

#include <netinet/in.h>
#include <string.h>
#include <iostream>

class ClientConnection
{

	private:
		int clientAddress;

	public:
		ClientConnection(const int &address);
		void operator>>(std::string &requestString);
		void operator<<(const std::string &responseMessage);
		int getAddress();
		void close();
};

class Server
{
	private:
		int serverSocket,  portNumber, clientLength;
	    struct sockaddr_in serverAddress, clientAddress;

		Server();
		Server(Server const&) = delete;
		void operator = (Server const&) = delete;

		static void threadEntry(const int &clientAddress);
	
	public:
		static Server& getInstance();
		void start();
};


#endif
