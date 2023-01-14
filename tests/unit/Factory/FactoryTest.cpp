#include "Factory.hpp"

#include <gtest/gtest.h>

using namespace httpxx;
using namespace factory;

TEST(FactoryTest, RequestName) {
    EXPECT_EQ(getRequestString<req_t::GET>(),     "GET");
    EXPECT_EQ(getRequestString<req_t::POST>(),    "POST");
    EXPECT_EQ(getRequestString<req_t::PUT>(),     "PUT");
    EXPECT_EQ(getRequestString<req_t::PATCH>(),   "PATCH");
    EXPECT_EQ(getRequestString<req_t::DELETE>(),  "DELETE");
    EXPECT_EQ(getRequestString<req_t::COPY>(),    "COPY");
    EXPECT_EQ(getRequestString<req_t::HEAD>(),    "HEAD");
    EXPECT_EQ(getRequestString<req_t::OPTIONS>(), "OPTIONS");
    EXPECT_EQ(getRequestString<req_t::LINK>(),    "LINK");
    EXPECT_EQ(getRequestString<req_t::UNLINK>(),  "UNLINK");
    EXPECT_EQ(getRequestString<req_t::PURGE>(),   "PURGE");
    EXPECT_EQ(getRequestString<req_t::LOCK>(),    "LOCK");
    EXPECT_EQ(getRequestString<req_t::UNLOCK>(),  "UNLOCK");
    EXPECT_EQ(getRequestString<req_t::PROPFIND>(), "PROPFIND");
    EXPECT_EQ(getRequestString<req_t::VIEW>(),    "VIEW");
}

TEST(FactoryTest, RequestSize) {
    EXPECT_EQ(3u, getRequestSize<req_t::GET>());
    EXPECT_EQ(4u, getRequestSize<req_t::POST>());
    EXPECT_EQ(3u, getRequestSize<req_t::PUT>());
    EXPECT_EQ(5u, getRequestSize<req_t::PATCH>());
    EXPECT_EQ(6u, getRequestSize<req_t::DELETE>());
    EXPECT_EQ(4u, getRequestSize<req_t::COPY>());
    EXPECT_EQ(4u, getRequestSize<req_t::HEAD>());
    EXPECT_EQ(7u, getRequestSize<req_t::OPTIONS>());
    EXPECT_EQ(4u, getRequestSize<req_t::LINK>());
    EXPECT_EQ(6u, getRequestSize<req_t::UNLINK>());
    EXPECT_EQ(5u, getRequestSize<req_t::PURGE>());
    EXPECT_EQ(4u, getRequestSize<req_t::LOCK>());
    EXPECT_EQ(6u, getRequestSize<req_t::UNLOCK>());
    EXPECT_EQ(8u, getRequestSize<req_t::PROPFIND>());
    EXPECT_EQ(4u, getRequestSize<req_t::VIEW>());
}

TEST(FactoryTest, HttpVersionAndSize) {
    EXPECT_EQ(getHttpVersion<http_t::HTTP_VERSION_11>(), "HTTP/1.1");
    EXPECT_EQ(getHttpVersion<http_t::HTTP_VERSION_2>(), "HTTP2");
    EXPECT_EQ(getHttpVersion<http_t::HTTP_VERSION_3>(), "HTTP3");

    EXPECT_EQ(8ul, getHttpVersionSize<http_t::HTTP_VERSION_11>());
    EXPECT_EQ(5ul, getHttpVersionSize<http_t::HTTP_VERSION_2>());
    EXPECT_EQ(5ul, getHttpVersionSize<http_t::HTTP_VERSION_3>());
}

