#include "ClientConnection.h"
#include <unistd.h>
#include <ctime>
#include <sys/socket.h>

Core::ClientConnection::ClientConnection(const int &address)
{
	this->clientAddress = address;
}

int Core::ClientConnection::getAddress()
{
	return this->clientAddress;
}

void Core::ClientConnection::operator<<(const std::string &responseMessage)
{
	write(this->clientAddress, responseMessage.c_str(), responseMessage.size());
}

void Core::ClientConnection::operator<<(Response &response)
{
    time_t currentTime;
    time(&currentTime);
    std::string actualTime = ctime(&currentTime);
    actualTime = actualTime.substr(0, actualTime.size()-1);

    response.setProperty("Date", actualTime);

    std::string responseString = response.toString();
    write(this->clientAddress, responseString.c_str(), responseString.size());
}

void Core::ClientConnection::operator>>(std::string &requestString)
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

void Core::ClientConnection::close()
{
	shutdown(this->clientAddress, 2);	
}