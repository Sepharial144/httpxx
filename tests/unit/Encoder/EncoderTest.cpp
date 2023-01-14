#include "encoder/Encoder.hpp"
#include "Factory.hpp"
#include "EncoderTest.hpp"

#include <cstring>
#include <string>
#include <gtest/gtest.h>
#include <array>

using namespace httpxx;
using namespace factory;
using namespace encoder;

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
    EXPECT_EQ(2ul, offset);
    EXPECT_EQ(true, std::equal(std::begin(data), 
                               std::end(data), 
                               std::begin(expected_1)));

    std::memset(&data[0], 0, 3);
    offset = whiteSpace(&data[0], 0ul);
    EXPECT_EQ(1ul, offset);
    EXPECT_EQ(true, std::equal(std::begin(data), 
                               std::end(data), 
                               std::begin(expected_2)));

    std::memset(&data[0],  0, 3);
    offset = whiteSpace(&data[0], 2ul);
    EXPECT_EQ(3ul, offset);
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
    std::array<uint8_t, 9> version_11 = {0};
    std::array<uint8_t, 6> version_2 = {0};
    std::array<uint8_t, 6> version_3 = {0};

    std::array<uint8_t, 9> expect_version_11 = {'H','T','T','P','/','1','.','1','\0'};
    std::array<uint8_t, 6> expect_version_2  = {'H','T','T','P','2','\0'};
    std::array<uint8_t, 6> expect_version_3  = {'H','T','T','P','3','\0'};

    EXPECT_EQ(factory::getHttpVersionSize<http_t::HTTP_VERSION_11>(), encodeHttpVersion(version_11.data(), 0ul, http_t::HTTP_VERSION_11));
    EXPECT_EQ(version_11, expect_version_11);

    EXPECT_EQ(factory::getHttpVersionSize<http_t::HTTP_VERSION_2>(),  encodeHttpVersion(version_2.data(), 0ul, http_t::HTTP_VERSION_2));
    EXPECT_EQ(version_2, expect_version_2);

    EXPECT_EQ(factory::getHttpVersionSize<http_t::HTTP_VERSION_3>(),  encodeHttpVersion(version_3.data(), 0ul, http_t::HTTP_VERSION_3));
    EXPECT_EQ(version_3, expect_version_3);

    std::memset(version_11.data(), 0, 9ul);
    std::memset(version_2.data(), 0, 6ul);
    std::memset(version_3.data(), 0, 6ul);

    std::array<uint8_t, 9> expect_version2_11 = {'\0','H','T','T','P','/','1','.','1',};
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

/*
TEST(EncoderTest, EncodeField)
{
    const char* testData = "Field";
    const size_t len = strlen(testData);
    head_field field = encoder::field(testData);
    EXPECT_STREQ(field.data, testData);
    EXPECT_EQ(field.len, len);
}
*/

TEST(EncoderTest, HeadFieldInit)
{
    header_info headInformation = {0};
    head_field hostField = field("localhost");
    EXPECT_STREQ(hostField.data, "localhost");
    EXPECT_EQ(hostField.len, strlen("localhost"));
}

TEST(EncoderTest, HeadInfoInitialization)
{
    header_info headInformation = { 
        field("localhost"), 
        field("8080"),
        field("Agent"),
        field("Accept"),
        field("Language"),
        field("Connection"),
        field("ConnectionType"),
        field("100")
        };

    EXPECT_STREQ(headInformation.hostName.data, "localhost");
    EXPECT_EQ(headInformation.hostName.len, strlen("localhost"));

    EXPECT_STREQ(headInformation.port.data, "8080");
    EXPECT_EQ(headInformation.port.len, strlen("8080"));

    EXPECT_STREQ(headInformation.userAgent.data, "Agent");
    EXPECT_EQ(headInformation.userAgent.len, strlen("Agent"));

    EXPECT_STREQ(headInformation.accept.data, "Accept");
    EXPECT_EQ(headInformation.accept.len, strlen("Accept"));

    EXPECT_STREQ(headInformation.lang.data, "Language");
    EXPECT_EQ(headInformation.lang.len, strlen("Language"));

    EXPECT_STREQ(headInformation.connection.data, "Connection");
    EXPECT_EQ(headInformation.connection.len, strlen("Connection"));

    EXPECT_STREQ(headInformation.contentType.data, "ConnectionType");
    EXPECT_EQ(headInformation.contentType.len, strlen("ConnectionType"));

    EXPECT_STREQ(headInformation.length.data, "100");
    EXPECT_EQ(headInformation.length.len, strlen("100"));
}

TEST(EncoderTest, TranslateNumber)
{
    char result[5] = {0};

    size_t number = 12345;
    translateNumber(&result[0], static_cast<uint16_t>(number));
    EXPECT_STREQ("12345", &result[0]);

    number = 65535;
    translateNumber(&result[0], static_cast<uint16_t>(number));
    EXPECT_STREQ("65535", &result[0]);
}

TEST(EncoderTest, EncodeCustomHead)
{
    TestAlignedHeader head;

    const char*  testData = "Head wrapped into structure\r\n";
    constexpr size_t lenData = 29ul;
    std::array<uint8_t, lenData> expected = {'H','e','a','d',' ','w','r','a','p','p','e','d',' ','i','n','t','o',' ','s','t','r','u','c','t','u','r','e','\r','\n'};
    std::array<uint8_t, lenData> result = {0};
    size_t status = encodeHead<TestAlignedHeader>(result.data(), 0, head);

    EXPECT_EQ(lenData, sizeof(TestAlignedHeader));
    EXPECT_EQ(status, lenData);
    EXPECT_EQ(status, strlen(testData));
    EXPECT_EQ(result, expected);
}


TEST(EncoderTest, EncodeProperties)
{
    std::array<uint8_t, 50> result;

    const char* first  = "first";
    const char* second = "second";
    const char* expect = "first, second\r\n";

    constexpr size_t rows = 2ul;
    const uint64_t properties[rows] = { 
        reinterpret_cast<uint64_t>(&first[0]), 
        reinterpret_cast<uint64_t>(&second[0])
    };

    constexpr size_t lenSeparator = 2ul;
    const char separator[lenSeparator] = {',', ' '};

    size_t status = encodeProperties(result.data(), 0, 
                                    &properties[0], rows, 
                                    separator, lenSeparator);

    EXPECT_EQ(status, strlen(expect));
    EXPECT_STREQ(expect, reinterpret_cast<const char*>(result.data()));
}

TEST(EncoderTest, ArrayToRefference)
{
    std::array<uint8_t, 1024> result;
    

    uint64_t first  = arrayReference<const char>("First");
    uint64_t second = arrayReference<const char>("Second");

    const uint8_t* firstLetter = reinterpret_cast<uint8_t*>(first);
    const uint8_t* secondLetter = reinterpret_cast<uint8_t*>(second);
    EXPECT_EQ('F', *firstLetter);
    EXPECT_EQ('S', *secondLetter);
}

TEST(EncoderTest, EncodeFiled)
{
    std::array<uint8_t, 50> result;

    const char* field  = "Accept";
    const char* first  = "first";
    const char* second = "second";
    const char* expect = "Accept: first, second\r\n";

    constexpr size_t lenSeparator = 2ul;
    const char separator[lenSeparator] = {',', ' '};

    constexpr size_t rows = 2ul;
    const uint64_t properties[rows] = { 
        reinterpret_cast<uint64_t>(&first[0]), 
        reinterpret_cast<uint64_t>(&second[0])
    };

    size_t status = encodeField(result.data(), 0,
                                field, strlen(field), 
                                &properties[0], rows, 
                                separator, lenSeparator);

    EXPECT_EQ(status, strlen(expect));
    EXPECT_STREQ(expect, reinterpret_cast<const char*>(result.data()));
}

TEST(EncoderTest, EncodeHead)
{
    std::array<uint8_t, 1024> result = {0};

    constexpr size_t rows = 2ul;
    const uint64_t properties[rows] = { 
        arrayReference<const char>("Accept: first, second"), 
        arrayReference<const char>("Connection: good")
    };

    const char* expect  = "Accept: first, second\r\nConnection: good\r\n";
    size_t status = encodeHead(result.data(), 0,
                                &properties[0], rows);
    EXPECT_EQ(status, strlen(expect));
    EXPECT_STREQ(expect, reinterpret_cast<const char*>(result.data()));


    const char* expect2 = " Accept: first, second\r\nConnection: good\r\n";
    result = {0};
    size_t offset = 1ul;
    std::memset(result.data(), ' ', offset);
    status = encodeHead(result.data(), offset,
                        &properties[0], rows);

    EXPECT_EQ(status, strlen(expect2));
    EXPECT_STREQ(expect2, reinterpret_cast<const char*>(result.data()));

}