#include "tomahawk-core.h" 
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <string>

Server& Server::getInstance()
{
	static Server instance;
	return instance;
}

Server::Server()
{

	this->serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	this->portNumber = 9090;

    bzero((char *) &this->serverAddress, sizeof(this->serverAddress));
    this->serverAddress.sin_family = AF_INET;
    this->serverAddress.sin_port = htons(this->portNumber);
    this->serverAddress.sin_addr.s_addr = INADDR_ANY;

	this->clientLength = sizeof(this->clientAddress);

	bind(this->serverSocket, (struct sockaddr *) &this->serverAddress, sizeof(this->serverAddress));
	this->start();
}

void Server::start()
{
	listen(this->serverSocket, 5);

    while (true)
    {
        
        this->clientSocket = accept(this->serverSocket, (struct sockaddr *) &this->clientAddress, (socklen_t *) &this->clientLength);
       	read(this->clientSocket, this->buffer, 250);

        std::string response = "HTTP/1.1 200 OK \n Date: Sun, 14 Jan 2016 03:36:20 GMT \nServer: c++ test server \nContent-Length: 18 \nContent-Type: text/html \nConnection: closed \n\n<h1>It's works</h1>\n";
        write(clientSocket, response.c_str(), response.size());

        shutdown(this->clientSocket, 2);

    }


}

