#ifndef WEB_CORE
#define WEB_CORE

#include <netinet/in.h>
#include <string.h>
#include <iostream>
#include <map>
#include <vector>

class Request
{	

	private:
		std::string method;
		std::string url;
		std::string httpVersion;
        std::string body;
		std::map<std::string, std::string> properties;
		std::map<std::string, std::string> parameters;

        std::vector<std::string> requestStringToVector(const std::string &requestString);
		void parseHeader(const std::vector<std::string> &requestLines);
        void separateBody(const std::vector<std::string> &requestLines);
		void parseBody();
        void decodeUrlEncodedFormData();
        void parseQueryStrings();

	public:
		Request(const std::string &requestString);

		bool isBodyNotEmpty();
		std::string getMethod();
		std::string getUrl();
		std::string getHttpVersion();
		std::string getProperty(const std::string &propertyName);
		std::string getParameter(const std::string &parameterName);
        std::string getBodyString();
};

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

		static void threadEntry(const int &clientSocket);

	public:
		static Server& getInstance();
		void start();
};


#endif
