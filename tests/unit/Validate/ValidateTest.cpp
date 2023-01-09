#include "Factory.hpp"
#include "validate/Validate.hpp"

#include <gtest/gtest.h>

using namespace httpxx;
using namespace validate;

TEST(ValidateTest, ValidateTypeRequest)
{
    const char* req = factory::getRequestString<req_t::GET>();
    EXPECT_EQ(typeRequest(req), req_t::GET);
    
    req = factory::getRequestString<req_t::POST>();
    EXPECT_EQ(typeRequest(req), req_t::POST);

    req = factory::getRequestString<req_t::PUT>();
    EXPECT_EQ(typeRequest(req), req_t::PUT);

    req = factory::getRequestString<req_t::PATCH>();
    EXPECT_EQ(typeRequest(req), req_t::PATCH);

    req = factory::getRequestString<req_t::DELETE>();
    EXPECT_EQ(typeRequest(req), req_t::DELETE);

    req = factory::getRequestString<req_t::COPY>();
    EXPECT_EQ(typeRequest(req), req_t::COPY);

    req = factory::getRequestString<req_t::HEAD>();
    EXPECT_EQ(typeRequest(req), req_t::HEAD);

    req = factory::getRequestString<req_t::OPTIONS>();
    EXPECT_EQ(typeRequest(req), req_t::OPTIONS);

    req = factory::getRequestString<req_t::LINK>();
    EXPECT_EQ(typeRequest(req), req_t::LINK);

    req = factory::getRequestString<req_t::UNLINK>();
    EXPECT_EQ(typeRequest(req), req_t::UNLINK);

    req = factory::getRequestString<req_t::UNLINK>();
    EXPECT_EQ(typeRequest(req), req_t::UNLINK);

    req = factory::getRequestString<req_t::PURGE>();
    EXPECT_EQ(typeRequest(req), req_t::PURGE);

    req = factory::getRequestString<req_t::LOCK>();
    EXPECT_EQ(typeRequest(req), req_t::LOCK);

    req = factory::getRequestString<req_t::UNLOCK>();
    EXPECT_EQ(typeRequest(req), req_t::UNLOCK);

    req = factory::getRequestString<req_t::PROPFIND>();
    EXPECT_EQ(typeRequest(req), req_t::PROPFIND);

    req = factory::getRequestString<req_t::VIEW>();
    EXPECT_EQ(typeRequest(req), req_t::VIEW);
}

TEST(ValidateTest, ValidateURL)
{
    std::string url = "/";
    EXPECT_EQ(validate::url(url.data(), url.size()), url.size());

    url = "/url/path";
    EXPECT_EQ(validate::url(url.data(), url.size()), url.size());

    url = "/url  ";
    EXPECT_EQ(validate::url(url.data(), url.size()), 4);
}

TEST(ValidateTest, ValidateURLError)
{
    std::string url = " ";
    EXPECT_EQ(validate::url(url.data(), url.size()), -1);

    url = "//";
    EXPECT_EQ(validate::url(url.data(), url.size()), -1);

    url = "/url/";
    EXPECT_EQ(validate::url(url.data(), url.size()), -1);

    url = "/url/    /";
    EXPECT_EQ(validate::url(url.data(), url.size()), -1);

}