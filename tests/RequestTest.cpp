#include "lib/gtest/include/gtest/gtest.h"
#include "core.h"

// ide jönnek a tesztek
class GetRequestTest : public ::testing::Test
{
    protected:
        Request *request;

        // Before, set up a Response Object
        virtual void SetUp()
        {
            std::string requestString =
                    "GET /medve?igen=nem&halal=medve HTTP/1.1\r\n"
                    "Host: localhost:9090\r\n"
                    "Connection: keep-alive\r\n"
                    "Cache-Control: max-age=0\r\n"
                    "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8\r\n"
                    "Upgrade-Insecure-Requests: 1\r\n"
                    "User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/48.0.2564.109 Safari/537.36\r\n"
                    "Accept-Encoding: gzip, deflate, sdch\r\n"
                    "Accept-Language: en-US,en;q=0.8,hu;q=0.6\r\n"
                    "\r\n";

            this->request = new Request(requestString);
        }

        virtual void TearDown()
        {
            delete this->request;
        }

};

TEST_F(GetRequestTest, firstLineParsing)
{
    ASSERT_EQ("GET", request->getMethod());
    ASSERT_EQ("HTTP/1.1", request->getHttpVersion());
    ASSERT_EQ("/medve", request->getUrl());
}


TEST_F(GetRequestTest, propertyParsing)
{
    ASSERT_EQ("localhost:9090", request->getProperty("Host"));
    ASSERT_EQ("keep-alive", request->getProperty("Connection"));
    ASSERT_EQ("max-age=0", request->getProperty("Cache-Control"));
    ASSERT_EQ("en-US,en;q=0.8,hu;q=0.6", request->getProperty("Accept-Language"));
}

TEST_F(GetRequestTest, queryStringParsing)
{
    ASSERT_EQ("nem", request->getParameter("igen"));
    ASSERT_EQ("medve", request->getParameter("halal"));
}

class PostRequestTest : public ::testing::Test
{
    protected:
        Request *request;

        virtual void SetUp()
        {
            std::string requestString =
                    "POST / HTTP/1.1\r\n"
                    "Host: localhost:9090\r\n"
                    "Connection: keep-alive\r\n"
                    "Content-Length: 23\r\n"
                    "Cache-Control: max-age=0\r\n"
                    "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8\r\n"
                    "Origin: http://localhost:9090\r\n"
                    "Upgrade-Insecure-Requests: 1\r\n"
                    "User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/48.0.2564.109 Safari/537.36\r\n"
                    "Content-Type: application/x-www-form-urlencoded\r\n"
                    "Referer: http://localhost:9090/\r\n"
                    "Accept-Encoding: gzip, deflate\r\n"
                    "Accept-Language: en-US,en;q=0.8,hu;q=0.6\r\n"
                    "\r\n"
                    "hegy=medve&gyerek=halal";

            this->request = new Request(requestString);
        }

        virtual void TearDown()
        {
            delete this->request;
        }
};

TEST_F(PostRequestTest, testMusthaveProperties)
{
    ASSERT_NE("", request->getProperty("Content-Length"));
    ASSERT_TRUE(std::stoi(request->getProperty("Content-Length"), nullptr) > 0);
}

TEST_F(PostRequestTest, testUrlEncodedBodyParse)
{
    ASSERT_EQ("medve", request->getParameter("hegy"));
    ASSERT_EQ("halal", request->getParameter("gyerek"));
}