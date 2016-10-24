#include "lib/gtest/include/gtest/gtest.h"
#include "core/Response.h"
#include "core/Server.h"

//
// Created by sebestyen on 22/02/16.
//

TEST(ResponseTest, emptyResponse)
{
    std::string expectedResponse = "HTTP/1.1 200 OK\r\n"
                                   "Connection: closed\r\n"
                                   "Server: Tomahawk\r\n"
                                   "\r\n";

    Core::Response response;
    ASSERT_EQ(expectedResponse, response.toString());
}

TEST(ResponseTest, statusCode)
{
    Core::Response response;
    response.setStatusCode("405 METHOD NOT ALLOWED");

    std::string expectedResponse = "HTTP/1.1 405 METHOD NOT ALLOWED\r\n"
                                   "Connection: closed\r\n"
                                   "Server: Tomahawk\r\n"
                                   "\r\n";

    ASSERT_EQ(expectedResponse, response.toString());
}

TEST(ResponseTest, addNewHeaderProperty)
{
    Core::Response response;
    response.setProperty("Date", "retes")
            .setProperty("Test-Property", "working");

    std::string expectedResponse = "HTTP/1.1 200 OK\r\n"
                                   "Connection: closed\r\n"
                                   "Date: retes\r\n"
                                   "Server: Tomahawk\r\n"
                                   "Test-Property: working\r\n"
                                   "\r\n";

    ASSERT_EQ(expectedResponse, response.toString());
}

TEST(ResponseTest, overrideHeaderProperty)
{
    Core::Response response;
    response.setProperty("Content-Type", "text/html")
            .setProperty("Server", "retes")
            .setProperty("Content-Type", "text/css");

    std::string expectedResponse = "HTTP/1.1 200 OK\r\n"
                                   "Connection: closed\r\n"
                                   "Content-Type: text/css\r\n"
                                   "Server: retes\r\n"
                                   "\r\n";

    ASSERT_EQ(expectedResponse, response.toString());
}

TEST(ResponseTest, plainTextBody)
{
    Core::Response response;

    std::string exampleSentence = "Medve fut le ajegyörl, vigyázzon katinéni";
    response.setBody(exampleSentence, "text/plain");

    std::string expectedResponse;
    expectedResponse.append("HTTP/1.1 200 OK\r\nConnection: closed\r\nContent-Length: ")
                    .append(std::to_string(exampleSentence.size()))
                    .append("\r\nContent-Type: text/plain\r\nServer: Tomahawk\r\n\r\nMedve fut le ajegyörl, vigyázzon katinéni\r\n");

    ASSERT_EQ(expectedResponse, response.toString());
}

TEST(ResponseTest, sendFileContent)
{
    Core::server().setResourceFolderPath("../../tests/test_resources");

    Core::Response response1;
    response1.setBody("/igen.html");

    ASSERT_EQ("text/html", response1.getProperty("Content-Type"));
    ASSERT_EQ("igen", response1.getBody());
    ASSERT_EQ("4", response1.getProperty("Content-Length"));
    ASSERT_EQ(4, response1.getBody().size());

    std::string expectedResponse1 = "HTTP/1.1 200 OK\r\n"
                                   "Connection: closed\r\n"
                                   "Content-Length: 4\r\n"
                                   "Content-Type: text/html\r\n"
                                   "Server: Tomahawk\r\n"
                                   "\r\n"
                                   "igen"
                                   "\r\n";

    ASSERT_EQ(expectedResponse1, response1.toString());

    Core::Response response2;
    response2.setBody("/style.css");

    ASSERT_EQ("text/css", response2.getProperty("Content-Type"));
    ASSERT_EQ("body{color:red;}", response2.getBody());
    ASSERT_EQ("16", response2.getProperty("Content-Length"));
    ASSERT_EQ(16, response2.getBody().size());

    std::string expectedResponse2 = "HTTP/1.1 200 OK\r\n"
                                    "Connection: closed\r\n"
                                    "Content-Length: 16\r\n"
                                    "Content-Type: text/css\r\n"
                                    "Server: Tomahawk\r\n"
                                    "\r\n"
                                    "body{color:red;}"
                                    "\r\n";

    ASSERT_EQ(expectedResponse2, response2.toString());
}