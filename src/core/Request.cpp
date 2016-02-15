#include "core.h"
#include <sstream>


Request::Request(const std::string &requestString)
{
    std::vector<std::string> requestLines = this->requestStringToVector(requestString);

	this->parseHeader(requestLines);

    if(this->isBodyNotEmpty())
        this->separateBody(requestLines);
}

std::vector<std::string> Request::requestStringToVector(const std::string &requestString)
{
    std::vector<std::string> requestStringLines;
    std::stringstream stream(requestString);

    std::string temp;
    while(getline(stream, temp))
        requestStringLines.push_back(temp);

    return requestStringLines;
}

void Request::parseHeader(const std::vector<std::string> &requestLines)
{

    std::stringstream firstLineStream(requestLines[0]);
    getline(firstLineStream, this->method, ' ');
    getline(firstLineStream, this->url, ' ');
    getline(firstLineStream, this->httpVersion, ' ');

    int i = 1;
    std::string tempLine = requestLines[i];
    while(i < requestLines.size() && tempLine != "\r")
    {
        unsigned long propertySeparator =  tempLine.find(':');
        this->properties[tempLine.substr(0, propertySeparator)] = tempLine.substr(propertySeparator+1);

        i++;
        tempLine = requestLines[i];
    }
}


bool Request::isBodyNotEmpty()
{
    if(this->properties.find("Content-Length") != this->properties.end())
        return (std::stoi(this->properties["Content-Length"], nullptr)) > 0;
    else
        return false;
}

void Request::separateBody(const std::vector<std::string> &requestLines)
{

    int8_t bodyIndex = 0;
    do
    {
        bodyIndex++;
    }while(requestLines[bodyIndex] != "\r");

    this->body = "";
    for(int8_t i = bodyIndex; i < requestLines.size(); i++)
        this->body.append(requestLines[i]);

    this->body = this->body.substr(1);

    this->parseBody();
}

void Request::parseBody()
{

    /**
     * TODO
     * create for JSON and XML as well
     * Create DOM parser class for XML
     */
    std::map<std::string, int8_t> mimeTypes = {
        {"application/x-www-form-urlencoded", 0}
        //,{"multipart/form-data", 1}
        //,{"application/json", 2}
    };

    switch (mimeTypes[this->properties["Content-Type"]])
    {
        case 0:
            this->decodeUrlEncodedFormData();
        break;
    }

}

void Request::decodeUrlEncodedFormData()
{
    std::stringstream bodyStream(this->body);
    std::string keyValuePair;
    while(getline(bodyStream, keyValuePair, '&'))
    {
        unsigned long keyValueSeparatorPosition = keyValuePair.find('=');
        this->parameters[keyValuePair.substr(0, keyValueSeparatorPosition)] = keyValuePair.substr(keyValueSeparatorPosition + 1);
    }
}

std::string Request::getBodyString()
{
    return this->body;
}

std::string Request::getProperty(const std::string &propertyName)
{
    return this->properties[propertyName];
}

std::string Request::getParameter(const std::string &parameterName)
{
    std::cout << parameterName.size() << this->parameters[parameterName].size();
    return this->parameters[parameterName];
}

std::string Request::getMethod()
{
	return this->method;
}

std::string Request::getUrl()
{
	return this->url;
}

std::string Request::getHttpVersion()
{
	return this->httpVersion;
}