#include "Response.h"
#include "Server.h"
#include <fstream>

// Created by sebestyen on 17/02/16.

Core::Response::Response()
{
    this->body = "";
    this->httpVersion = "HTTP/1.1";
    this->statusCode = "200 OK";
    this->properties["Server"] = "Tomahawk";
    this->properties["Connection"] = "closed";
}

std::string Core::Response::toString()
{
    std::string responseString;
    responseString.append(this->httpVersion)
                  .append(" ")
                  .append(this->statusCode)
                  .append("\r\n");

    for(const auto &property : this->properties)
        responseString.append(property.first)
                      .append(": ")
                      .append(property.second)
                      .append("\r\n");

    responseString.append("\r\n");

    if(!this->isEmptyBody())
    {
        responseString.append(this->body)
                      .append("\r\n");
    }

    return responseString;

}

Core::Response &Core::Response::setBody(const std::string &filePath)
{
    this->body.clear();

    if(!filePath.empty() && filePath != "/")
    {
        std::string path = server().getResourceFolderPath()
                .append(filePath);

        std::ifstream file;
        file.open(path, std::ios::binary);

        if(file.good())
        {
            if(file.is_open())
            {
                std::string fileLine;
                while (getline(file, fileLine))
                    this->body.append(fileLine);

                file.close();
            }

            this->properties["Content-Length"] = std::to_string(this->body.size());
            this->properties["Content-Type"] = this->fetchFileMimeType(filePath);
            this->setStatusCode("200 OK");
        }
        else
            this->setStatusCode("404 Not Found");
    }
    else
        this->setStatusCode("404 Not Found");

    return *this;
}

std::string Core::Response::fetchFileMimeType(const std::string filePath)
{
    std::map<std::string, std::string> mimeTypes = {
             {".css" , "text/css"}
            ,{".jpg" , "image/jpeg"}
            ,{".png" , "image/png"}
            ,{".html", "text/html"}
            ,{".js"  , "application/x-javascript"}
    };

    unsigned long dotPosition = filePath.find(".");
    std::string temp = filePath.substr(dotPosition);
    temp = mimeTypes[temp];
    if(temp != "")
        return temp;
    else
        return "*/*";
}

Core::Response &Core::Response::setBody(const std::string &content, const std::string &mimeType)
{
    this->body = content;
    this->setProperty("Content-Type", mimeType);
    this->setProperty("Content-Length", std::to_string(this->body.size()));
    this->setStatusCode("200 OK");

    return *this;
}

std::string Core::Response::getBody()
{
    return this->body;
}

Core::Response &Core::Response::setProperty(const std::string &name, const std::string &value)
{
    this->properties[name] = value;

    return *this;
}

std::string Core::Response::getProperty(const std::string &propertyName)
{
    return this->properties[propertyName];
}

Core::Response &Core::Response::setStatusCode(const std::string &newStatusCode)
{
    this->statusCode = newStatusCode;
    return *this;
}

bool Core::Response::isEmptyBody()
{
    return this->body.empty();
}