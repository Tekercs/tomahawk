#include "core.h"
#include <thread>

Server::Server()
{
	this->serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	this->portNumber = 80;                   // default portnumber
    this->resourceFolderPath = "./resource"; // default resource folder path

    bzero((char *) &this->serverAddress, sizeof(this->serverAddress));
    this->serverAddress.sin_family = AF_INET;
    this->serverAddress.sin_port = htons((uint16_t) this->portNumber);
    this->serverAddress.sin_addr.s_addr = INADDR_ANY;

	this->clientLength = sizeof(this->clientAddress);
}

Server& Server::getInstance()
{
	static Server instance;

	return instance;
}

void Server::start()
{
    bind(this->serverSocket, (struct sockaddr *) &this->serverAddress, sizeof(this->serverAddress));
	listen(this->serverSocket, 5);

    while (true)
    {
	    int clientSocket = accept(this->serverSocket, (struct sockaddr *) &this->clientAddress, (socklen_t *) &this->clientLength);
	    if(clientSocket >= 0)
			std::thread(Server::threadEntry, clientSocket).join();
		else
			std::cout << "Unable to accept the connection" << std::endl;
    }
}

void Server::threadEntry(const int &clientSocket)
{
	ClientConnection client(clientSocket);

	std::string clientRequestString;
	client >> clientRequestString;
	Request request(clientRequestString);

    client << "HTTP/1.1 200 OK \n Date: Sun, 14 Jan 2016 03:36:20 GMT \nServer: c++ test server \nContent-Length: 146 \nContent-Type: text/html \nConnection: closed \n\n<form method=\"post\"><button>send</button><input type=\"hidden\" value=\"medve\" name=\"hegy\"/><input type=\"hidden\" value=\"halal\" name=\"gyerek\"/> </form>\n";

    client.close();
}

Server& Server::setPortNumber(const int &newPortNumber)
{
    this->portNumber = newPortNumber;
    this->serverAddress.sin_port = htons((uint16_t) this->portNumber);
    return *this;
}

Server& Server::setResourceFolderPath(const std::string &newResourceFolderPath)
{
    this->resourceFolderPath = newResourceFolderPath;
    return *this;
}

int Server::getPortNumber()
{
    return this->portNumber;
}

Server& server()
{
    return Server::getInstance();
}