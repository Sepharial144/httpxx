#ifndef _HTTPXX_ENCODER_REQUEST_GET_HPP_
#define _HTTPXX_ENCODER_REQUEST_GET_HPP_

#include "httpxx_types.hpp"
#include "Factory.hpp"
#include "encoder/Encoder.hpp"

#include <cstdint>
#include <cstring>
#include <string>
#include <gtest/gtest.h>

class EncodeRequestGet: public ::testing::TestWithParam<httpxx::http_t>
{
public:
    explicit EncodeRequestGet();
    virtual ~EncodeRequestGet() {};

    const char* getExpectedValue() const;
    const char* getResultValue() const;
    size_t getStatus() const;

    void generateRequestHttpParametrized();

protected:
    void SetUp() override;

private:
    std::string generateHttpVersion(httpxx::http_t http_type);

private:
    const char* m_url;
    const char* m_head;
    const char* m_data;
    httpxx::http_t m_httpType;
    size_t m_lastStatus;
    std::array<uint8_t, 1024> m_request;
    std::string m_expected;
};

INSTANTIATE_TEST_SUITE_P(HTTP11_RequestParamsGET, EncodeRequestGet, ::testing::Values(httpxx::http_t::HTTP_VERSION_11));
INSTANTIATE_TEST_SUITE_P(HTTP2_RequestParamsGET,  EncodeRequestGet, ::testing::Values(httpxx::http_t::HTTP_VERSION_2));
INSTANTIATE_TEST_SUITE_P(HTTP3_RequestParamsGET,  EncodeRequestGet, ::testing::Values(httpxx::http_t::HTTP_VERSION_3));


#endif // !_HTTPXX_ENCODER_REQUEST_GET_TEST_HPP_