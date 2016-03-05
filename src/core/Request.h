//
// Created by sebestyen on 05/03/16.
//

#ifndef TOMAHAWK_REQUEST_H
#define TOMAHAWK_REQUEST_H

#include <iostream>
#include <map>
#include <vector>

namespace Core
{
    class Request
    {

        private:
            std::string method
                      , url
                      , httpVersion
                      , body
                      ;
            std::map<std::string, std::string> properties
                                              ,parameters
                                              ;

            std::vector<std::string> requestStringToVector(const std::string &requestString);
            void parseHeader(const std::vector<std::string> &requestLines)
               , separateBody(const std::vector<std::string> &requestLines)
               , parseBody()
               , decodeUrlEncodedFormData()
               , parseQueryStrings()
               ;

        public:
            Request(const std::string &requestString);

            bool isBodyNotEmpty();
            std::string getUrl()
                      , getMethod()
                      , getHttpVersion()
                      , getProperty(const std::string &propertyName)
                      , getParameter(const std::string &parameterName)
                      , operator[](const std::string &fieldName)
                      , getBodyString()
                      ;
    };
}

#endif //TOMAHAWK_REQUEST_H
