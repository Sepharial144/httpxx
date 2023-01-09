#include "encoder/Encoder.hpp"
#include "Factory.hpp"

#include <cstring>
#include <string>
#include <gtest/gtest.h>

using namespace httpxx;
using namespace factory;

TEST(EncoderTest, EncodeRequestType)
{
    std::array<uint8_t, 20> request;
    EXPECT_EQ(factory::getRequestSize<req_t::GET>(), encodeRequestType(request.data(), 0, req_t::GET));
    
    const std::string getRequest  = " GET";
    EXPECT_EQ(getRequest.size(), encodeRequestType(request.data(), 1ul, req_t::GET));

    EXPECT_EQ(factory::getRequestSize<req_t::POST>(), encodeRequestType(request.data(), 0, req_t::POST));

    // TODO finish for another request types
}

TEST(EncoderTest, EncodeUrl)
{
    std::string request = "/simple/url";
    std::array<uint8_t, 20> result;
    EXPECT_EQ(request.size(), encodeUrl(result.data(), 0ul, request.data(), request.size()));

    size_t offset = 1ul;
    EXPECT_EQ(request.size() + offset, encodeUrl(result.data(), offset, request.data(), request.size()));
}

TEST(EncoderTest, WhiteSpaceInput)
{
    uint8_t data[3]  = {'\0','\0','\0'};

    uint8_t expected_1[3] = {'\0',' ','\0'};
    uint8_t expected_2[3] = {' ','\0','\0'};
    uint8_t expected_3[3] = {'\0','\0',' '};

    size_t offset = whiteSpace(&data[0], 1ul);
    EXPECT_EQ(1ul, offset);
    EXPECT_EQ(true, std::equal(std::begin(data), 
                               std::end(data), 
                               std::begin(expected_1)));

    std::memset(&data[0],  0, 3);
    offset = whiteSpace(&data[0], 0ul);
    EXPECT_EQ(1ul, offset);
    EXPECT_EQ(true, std::equal(std::begin(data), 
                               std::end(data), 
                               std::begin(expected_2)));

    std::memset(&data[0],  0, 3);
    offset = whiteSpace(&data[0], 2ul);
    EXPECT_EQ(1ul, offset);
    EXPECT_EQ(true, std::equal(std::begin(data), 
                               std::end(data), 
                               std::begin(expected_3)));
}

TEST(EncoderTest, EndLineInput)
{
    uint8_t data[4] = {'\0', '\0', '\0', '\0'};
    uint8_t expected_1[4] = {'\r', '\n', '\0', '\0'};
    uint8_t expected_2[4] = {'\r', '\n', '\r', '\n'};
    uint8_t* pData = &data[0];

    size_t offset = endLine(pData, 0ul);
    EXPECT_EQ(offset, 2ul);
    EXPECT_EQ(true, std::equal(std::begin(data), 
                               std::end(data), 
                               std::begin(expected_1)));

    offset = endLine(pData, offset);
    EXPECT_EQ(offset, 4ul);
    EXPECT_EQ(true, std::equal(std::begin(data), std::end(data), std::begin(expected_2)));

}

TEST(EncoderTest, EncodeVersionHttp)
{
    std::array<uint8_t, 8> version_11 = {0};
    std::array<uint8_t, 6> version_2 = {0};
    std::array<uint8_t, 6> version_3 = {0};

    std::array<uint8_t, 8> expect_version_11 = {'H','T','T','P','1','/','1','\0'};
    std::array<uint8_t, 6> expect_version_2  = {'H','T','T','P','2','\0'};
    std::array<uint8_t, 6> expect_version_3  = {'H','T','T','P','3','\0'};

    EXPECT_EQ(factory::getHttpVersionSize<http_t::HTTP_VERSION_11>(), encodeHttpVersion(version_11.data(), 0ul, http_t::HTTP_VERSION_11));
    EXPECT_EQ(version_11, expect_version_11);

    EXPECT_EQ(factory::getHttpVersionSize<http_t::HTTP_VERSION_2>(),  encodeHttpVersion(version_2.data(), 0ul, http_t::HTTP_VERSION_2));
    EXPECT_EQ(version_2, expect_version_2);

    EXPECT_EQ(factory::getHttpVersionSize<http_t::HTTP_VERSION_3>(),  encodeHttpVersion(version_3.data(), 0ul, http_t::HTTP_VERSION_3));
    EXPECT_EQ(version_3, expect_version_3);

    std::memset(version_11.data(), 0, 8ul);
    std::memset(version_2.data(), 0, 6ul);
    std::memset(version_3.data(), 0, 6ul);

    std::array<uint8_t, 8> expect_version2_11 = {'\0','H','T','T','P','1','/','1'};
    std::array<uint8_t, 6> expect_version2_2  = {'\0','H','T','T','P','2'};
    std::array<uint8_t, 6> expect_version2_3  = {'\0','H','T','T','P','3'};

    size_t offset = 1ul;
    EXPECT_EQ(factory::getHttpVersionSize<http_t::HTTP_VERSION_11>() + offset, encodeHttpVersion(version_11.data(), offset, http_t::HTTP_VERSION_11));
    EXPECT_EQ(version_11, expect_version2_11);

    EXPECT_EQ(factory::getHttpVersionSize<http_t::HTTP_VERSION_2>()  + offset, encodeHttpVersion(version_2.data(), offset, http_t::HTTP_VERSION_2));
    EXPECT_EQ(version_2, expect_version2_2);

    EXPECT_EQ(factory::getHttpVersionSize<http_t::HTTP_VERSION_3>()  + offset, encodeHttpVersion(version_3.data(), offset, http_t::HTTP_VERSION_3));
    EXPECT_EQ(version_3, expect_version2_3);
}

TEST(EncoderTest, EncodeLine)
{
    constexpr size_t len = 9ul;
    const char* line = "test line";
    uint8_t expect_line[len] = {'t', 'e', 's', 't', ' ', 'l', 'i', 'n', 'e'};
    uint8_t result[len] = {0};

    EXPECT_EQ(len, encodeLine(&result[0], 0ul, line, len));
    EXPECT_EQ(true, std::equal(std::begin(result), 
                               std::end(result), 
                               std::begin(expect_line)));
}