//
// Created by sebestyen on 05/03/16.
//

#ifndef TOMAHAWK_CLIENTCONNECTION_H
#define TOMAHAWK_CLIENTCONNECTION_H

#include <iostream>
#include <string.h>
#include "Response.h"

namespace Core
{
    class ClientConnection
    {
        private:
            int clientAddress;

        public:
            ClientConnection(const int &address);

            void operator>>(std::string &requestString)
               , operator<<(const std::string &responseMessage)
               , operator<<(Response &response)
               , close()
               ;

            int getAddress();
    };
}



#endif //TOMAHAWK_CLIENTCONNECTION_H
