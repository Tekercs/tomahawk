//
// Created by sebestyen on 05/03/16.
//

#ifndef TOMAHAWK_RESPONSE_H
#define TOMAHAWK_RESPONSE_H

#include <iostream>
#include <string.h>
#include <map>

namespace Core
{
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
                      , statusCode
                      ;
            std::map<std::string, std::string> properties;
            std::string fetchFileMimeType(const std::string filePath);

        public:
            Response();
            std::string toString()
                      , getBody()
                      , getProperty(const std::string &propertyName)
                      ;

            bool isEmptyBody();
            Response &setProperty(const std::string &name, const std::string &value)
                   , &setStatusCode(const std::string &newStatusCode)
                   , &setBody(const std::string &filePath)
                   , &setBody(const std::string &content, const std::string &mimeType)
                   ;
    };
}

#endif //TOMAHAWK_RESPONSE_H
