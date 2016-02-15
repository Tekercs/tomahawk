#include "core.h"
#include <unistd.h>

ClientConnection::ClientConnection(const int &address)
{
	this->clientAddress = address;
}

int ClientConnection::getAddress()
{
	return this->clientAddress;
}

void ClientConnection::operator<<(const std::string &responseMessage)
{
	write(this->clientAddress, responseMessage.c_str(), responseMessage.size());
}

void ClientConnection::operator>>(std::string &requestString)
{
	char buffer[255];
	ssize_t messageLength = 0;

	do
	{
		bzero(buffer, 255);
		messageLength = read(this->clientAddress, buffer, 255);
		requestString.append(buffer);

	}while(messageLength == 255);

}

void ClientConnection::close()
{
	shutdown(this->clientAddress, 2);	
}