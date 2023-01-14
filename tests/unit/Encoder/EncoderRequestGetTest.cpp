#include "encoder/Encoder.hpp"
#include "Factory.hpp"
#include "EncodeRequestGet.hpp"

#include <cstring>
#include <string>
#include <gtest/gtest.h>

using namespace httpxx;

TEST_P(EncodeRequestGet, ParametrizedHttp)
{
    generateRequestHttpParametrized();
    size_t len = getStatus();
    const char* result = getResultValue();
    const char* expected = getExpectedValue();

    EXPECT_EQ(len, strlen(expected));
    EXPECT_STREQ(result, expected);
}

TEST(EncodeRequestGetTest, Http11EncodeRequestGET)
{
    std::array<uint8_t, 1024> request = {0};
    const char* url = "/url";
    const char* head = "Connection: keep-alive";
    const char* data = "{json data}";
    
    std::string expected = "GET /url HTTP/1.1\r\nConnection: keep-alive\r\n{json data}";

    size_t status = encoder::request(req_t::GET,
            reinterpret_cast<void*>(request.data()), request.size(),
            reinterpret_cast<const void*>(url), strlen(url), 
            reinterpret_cast<const void*>(head), strlen(head), 
            reinterpret_cast<const void*>(data), strlen(data));

    EXPECT_EQ(status, expected.size());
    EXPECT_STREQ(expected.data(), reinterpret_cast<const char*>(request.data()));
}

TEST(EncodeRequestGetTest, Http2EncodeRequestGET)
{
    #undef HTTP_VERSION
    #define HTTP_VERSION 2

    std::array<uint8_t, 1024> request = {0};
    const char* url = "/url";
    const char* head = "Connection: keep-alive";
    const char* data = "{json data}";
    
    std::string expected = "GET /url HTTP2\r\nConnection: keep-alive\r\n{json data}";

    size_t status = encoder::request(req_t::GET,
            reinterpret_cast<void*>(request.data()), request.size(),
            reinterpret_cast<const void*>(url), strlen(url), 
            reinterpret_cast<const void*>(head), strlen(head), 
            reinterpret_cast<const void*>(data), strlen(data));

    EXPECT_EQ(status, expected.size());
    EXPECT_STREQ(expected.data(), reinterpret_cast<const char*>(request.data()));
    
    #undef HTTP_VERSION
}

TEST(EncodeRequestGetTest, Http3EncodeRequestGET)
{
    #define HTTP_VERSION 3

    std::array<uint8_t, 1024> request = {0};
    const char* url = "/url";
    const char* head = "Connection: keep-alive";
    const char* data = "{json data}";
    
    std::string expected = "GET /url HTTP3\r\nConnection: keep-alive\r\n{json data}";

    size_t status = encoder::request(req_t::GET,
            reinterpret_cast<void*>(request.data()), request.size(),
            reinterpret_cast<const void*>(url), strlen(url), 
            reinterpret_cast<const void*>(head), strlen(head), 
            reinterpret_cast<const void*>(data), strlen(data));

    EXPECT_EQ(status, expected.size());
    EXPECT_STREQ(expected.data(), reinterpret_cast<const char*>(request.data()));
    
    #undef HTTP_VERSION
}


TEST(EncoderTest, EncodeRequestType)
{
    std::array<uint8_t, 3> request;
    std::array<uint8_t, 3> expected = {'G','E','T'};
    EXPECT_EQ(factory::getRequestSize<req_t::GET>(), encoder::encodeRequestType(request.data(), 0ul, req_t::GET));
    EXPECT_STREQ(reinterpret_cast<const char*>(request.data()), 
                 reinterpret_cast<const char*>(expected.data()));
}

TEST(EncoderTest, EncodeRequestTypeShifted)
{
    std::array<uint8_t, 4> request = {0};
    std::array<uint8_t, 4> expected = {' ','G','E','T'};

    std::array<uint8_t, 5> request2 = {0};
    std::array<uint8_t, 5> expected2 = {' ',' ','G','E','T'};

    size_t offset = 1ul;
    EXPECT_EQ(factory::getRequestSize<req_t::GET>() + offset, encoder::encodeRequestType(request.data(), offset, req_t::GET));
    EXPECT_STREQ(reinterpret_cast<const char*>(request.data()), 
                 reinterpret_cast<const char*>(expected.data()));

    offset = 2ul;
    EXPECT_EQ(factory::getRequestSize<req_t::GET>() + offset, encoder::encodeRequestType(request2.data(), offset, req_t::GET));
    EXPECT_STREQ(reinterpret_cast<const char*>(request2.data()), 
                 reinterpret_cast<const char*>(expected2.data()));
}

