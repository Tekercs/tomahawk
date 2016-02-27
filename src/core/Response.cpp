#include "core.h"
#include <fstream>

// Created by sebestyen on 17/02/16.

Response::Response()
{
    this->body = "";
    this->httpVersion = "HTTP/1.1";
    this->statusCode = "200 OK";
    this->properties["Server"] = "Tomahawk";
    this->properties["Connection"] = "closed";
}

std::string Response::toString()
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

Response &Response::setBody(const std::string &filePath)
{
    std::string path = server().getResourceFolderPath()
                               .append(filePath);

    std::ifstream file;
    file.open(path, std::ios::binary);

    std::string fileContent;
    fileContent.clear();
    if(file.is_open())
    {
        std::string fileLine;
        while (getline(file, fileLine))
            fileContent.append(fileLine);

        file.close();
    }

    this->body = fileContent;
    this->properties["Content-Length"] = std::to_string(this->body.size());

    this->properties["Content-Type"] = this->fetchFileMimeType(filePath);

    return *this;
}

std::string Response::fetchFileMimeType(const std::string filePath)
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

Response &Response::setBody(const std::string &content, const std::string &mimeType)
{
    this->setProperty("Content-Type", mimeType);
    this->body = content;
    this->setProperty("Content-Length", std::to_string(this->body.size()));

    return *this;
}

std::string Response::getBody()
{
    return this->body;
}

Response &Response::setProperty(const std::string &name, const std::string &value)
{
    this->properties[name] = value;

    return *this;
}

std::string Response::getProperty(const std::string &propertyName)
{
    return this->properties[propertyName];
}

Response &Response::setStatusCode(const std::string &newStatusCode)
{
    this->statusCode = newStatusCode;
    return *this;
}

bool Response::isEmptyBody()
{
    return this->body.empty();
}