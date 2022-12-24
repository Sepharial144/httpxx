#include "Factory.hpp"

#include <gtest/gtest.h>

using namespace httpxx;

TEST(FactoryTest, GET_Name) {
    EXPECT_EQ("GET", factory::getRequestString<req::GET>());
}

TEST(FactoryTest, POST_Name) {
    EXPECT_EQ("POST", factory::getRequestString<req::POST>());
}

TEST(FactoryTest, PUT_Name) {
    const std::string requestName = factory::getRequestString<req::PUT>();
    EXPECT_EQ("PUT", factory::getRequestString<req::PUT>());
}

TEST(FactoryTest, PATCH_Name) {
    EXPECT_EQ("PATCH", factory::getRequestString<req::PATCH>());
}

TEST(FactoryTest, DELETE_Name) {
    EXPECT_EQ("DELETE", factory::getRequestString<req::DELETE>());
}

TEST(FactoryTest, COPY_Name) {
    EXPECT_EQ("COPY", factory::getRequestString<req::COPY>());
}

TEST(FactoryTest, HEAD_Name) {
    EXPECT_EQ("HEAD", factory::getRequestString<req::HEAD>());
}

TEST(FactoryTest, OPTIONS_Name) {
    EXPECT_EQ("OPTIONS", factory::getRequestString<req::OPTIONS>());
}

TEST(FactoryTest, LINK_Name) {
    EXPECT_EQ("LINK", factory::getRequestString<req::LINK>());
}

TEST(FactoryTest, UNLINK_Name) {
    EXPECT_EQ("UNLINK", factory::getRequestString<req::UNLINK>());
}

TEST(FactoryTest, PURGE_Name) {
    EXPECT_EQ("PURGE", factory::getRequestString<req::PURGE>());
}

TEST(FactoryTest, LOCK_Name) {
    EXPECT_EQ("LOCK", factory::getRequestString<req::LOCK>());
}

TEST(FactoryTest, UNLOCK_Name) {
    EXPECT_EQ("UNLOCK", factory::getRequestString<req::UNLOCK>());
}

TEST(FactoryTest, PROPFIND_Name) {
    EXPECT_EQ("PROPFIND", factory::getRequestString<req::PROPFIND>());
}

TEST(FactoryTest, VIEW_Name) {
    EXPECT_EQ("VIEW", factory::getRequestString<req::VIEW>());
}

