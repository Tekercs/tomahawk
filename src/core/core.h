#ifndef WEB_CORE
#define WEB_CORE

#include <netinet/in.h>
#include <string.h>
#include <iostream>
#include <map>
#include <vector>

class Response
{
    private:
        /**
          * TODO
          * finish the status code list
          * https://www.w3.org/Protocols/rfc2616/rfc2616-sec10.html
          */

        std::string body
                  , httpVersion
                  , statusCode;
        std::map<std::string, std::string> properties;
        std::string fetchFileMimeType(const std::string filePath);

    public:
        Response();
        std::string toString()
                  , getBody()
                  , getProperty(const std::string &propertyName);

        bool isEmptyBody();
        Response &setProperty(const std::string &name, const std::string &value)
               , &setStatusCode(const std::string &newStatusCode)
               , &setBody(const std::string &filePath)
               , &setBody(const std::string &content, const std::string &mimeType);
};

class Request
{	

	private:
		std::string method
                  , url
                  , httpVersion
                  , body;
		std::map<std::string, std::string> properties
                                          ,parameters;

        std::vector<std::string> requestStringToVector(const std::string &requestString);
		void parseHeader(const std::vector<std::string> &requestLines)
           , separateBody(const std::vector<std::string> &requestLines)
		   , parseBody()
           , decodeUrlEncodedFormData()
           , parseQueryStrings();

	public:
		Request(const std::string &requestString);

		bool isBodyNotEmpty();
		std::string getUrl()
                  , getMethod()
		          , getHttpVersion()
		          , getProperty(const std::string &propertyName)
                  , getParameter(const std::string &parameterName)
                  , operator[](const std::string &fieldName)
                  , getBodyString();
};

class ClientConnection
{
	private:
		int clientAddress;

	public:
		ClientConnection(const int &address);

		void operator>>(std::string &requestString)
           , operator<<(const std::string &responseMessage)
           , operator<<(Response &response)
           , close();

		int getAddress();
};

class Server
{
	private:
		int serverSocket
          , portNumber
          , clientLength;
	    struct sockaddr_in serverAddress
                         , clientAddress;
        std::string resourceFolderPath;

		Server();
		Server(Server const&) = delete;

		void operator = (Server const&) = delete;
		static void threadEntry(const int &clientSocket);

	public:
		static Server& getInstance();
		void start();
        int getPortNumber();
        Server  &setResourceFolderPath(const std::string &newResourceFolderPath)
              , &setPortNumber(const int &newPortNumber);

        std::string getResourceFolderPath();

};

Server& server();

#endif
