#include "Factory.hpp"

#include <gtest/gtest.h>

using namespace httpxx;

TEST(FactoryTest, RequestName) {
    EXPECT_EQ("GET", factory::getRequestString<req_t::GET>());
    EXPECT_EQ("POST", factory::getRequestString<req_t::POST>());
    EXPECT_EQ("PUT", factory::getRequestString<req_t::PUT>());
    EXPECT_EQ("PATCH", factory::getRequestString<req_t::PATCH>());
    EXPECT_EQ("DELETE", factory::getRequestString<req_t::DELETE>());
    EXPECT_EQ("COPY", factory::getRequestString<req_t::COPY>());
    EXPECT_EQ("HEAD", factory::getRequestString<req_t::HEAD>());
    EXPECT_EQ("OPTIONS", factory::getRequestString<req_t::OPTIONS>());
    EXPECT_EQ("LINK", factory::getRequestString<req_t::LINK>());
    EXPECT_EQ("UNLINK", factory::getRequestString<req_t::UNLINK>());
    EXPECT_EQ("PURGE", factory::getRequestString<req_t::PURGE>());
    EXPECT_EQ("LOCK", factory::getRequestString<req_t::LOCK>());
    EXPECT_EQ("UNLOCK", factory::getRequestString<req_t::UNLOCK>());
    EXPECT_EQ("PROPFIND", factory::getRequestString<req_t::PROPFIND>());
    EXPECT_EQ("VIEW", factory::getRequestString<req_t::VIEW>());
}

