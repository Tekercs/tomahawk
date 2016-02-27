#include "core.h"
#include <unistd.h>
#include <ctime>

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

void ClientConnection::operator<<(Response &response)
{
    time_t currentTime;
    time(&currentTime);
    std::string actualTime = ctime(&currentTime);
    actualTime = actualTime.substr(0, actualTime.size()-1);

    response.setProperty("Date", actualTime);

    std::string responseString = response.toString();
    write(this->clientAddress, responseString.c_str(), responseString.size());
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