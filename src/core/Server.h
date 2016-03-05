//
// Created by sebestyen on 05/03/16.
//

#ifndef TOMAHAWK_SERVER_H
#define TOMAHAWK_SERVER_H

#include <netinet/in.h>
#include <string.h>
#include <iostream>
#include <map>
#include <vector>

namespace Core
{
    class Server
    {
        private:
            int serverSocket
              , portNumber
              , clientLength
              ;
            struct sockaddr_in serverAddress
                             , clientAddress
                             ;
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
                  , &setPortNumber(const int &newPortNumber)
                  ;

            std::string getResourceFolderPath();

    };

    Server& server();
}

#endif //TOMAHAWK_SERVER_H
