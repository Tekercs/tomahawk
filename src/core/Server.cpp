#include "Server.h"
#include <thread>
#include "ClientConnection.h"
#include "Request.h"

Core::Server::Server()
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

Core::Server& Core::Server::getInstance()
{
	static Server instance;

	return instance;
}

void Core::Server::start()
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

void Core::Server::threadEntry(const int &clientSocket)
{
    Core::ClientConnection client(clientSocket);

	std::string clientRequestString;
	client >> clientRequestString;
	Request request(clientRequestString);

    Response response;
    response.setBody(request.getUrl());

    client << response;

    client.close();
}

Core::Server& Core::Server::setPortNumber(const int &newPortNumber)
{
    this->portNumber = newPortNumber;
    this->serverAddress.sin_port = htons((uint16_t) this->portNumber);
    return *this;
}

Core::Server& Core::Server::setResourceFolderPath(const std::string &newResourceFolderPath)
{
    this->resourceFolderPath = newResourceFolderPath;
    return *this;
}

int Core::Server::getPortNumber()
{
    return this->portNumber;
}

Core::Server& Core::server()
{
    return Core::Server::getInstance();
}

std::string Core::Server::getResourceFolderPath()
{
    return this->resourceFolderPath;
}