#include "Factory.hpp"
#include "decoder/Decoder.hpp"

#include <set>
#include <vector>
#include <string>
#include <gtest/gtest.h>

using namespace httpxx;

class DetectRequestTest : public ::testing::Test
{
    public:
        explicit DetectRequestTest() {};
        virtual  ~DetectRequestTest() {};

        void detectTest(const char* req, req_t expect)
        {
            std::pair<uint16_t, uint16_t> p = decoder::computeRequest(req);
            EXPECT_EQ(expect, decoder::detectRequest(p));
        }
};

TEST_F(DetectRequestTest, DetectRequest)
{
    detectTest("GET", req_t::GET);
    detectTest("POST", req_t::POST);
    detectTest("PUT", req_t::PUT);
    detectTest("PATCH", req_t::PATCH);
    detectTest("DELETE", req_t::DELETE);
    detectTest("COPY", req_t::COPY);
    detectTest("HEAD", req_t::HEAD);
    detectTest("OPTIONS", req_t::OPTIONS);
    detectTest("LINK", req_t::LINK);
    detectTest("UNLINK", req_t::UNLINK);
    detectTest("PURGE", req_t::PURGE);
    detectTest("LOCK", req_t::LOCK);
    detectTest("UNLOCK", req_t::UNLOCK);
    detectTest("PROPFIND", req_t::PROPFIND);
    detectTest("VIEW", req_t::VIEW);
}

TEST_F(DetectRequestTest, ErrorRequest)
{
    // TODO: create all tests with 3 letters based on alphabet
    detectTest("GTE", req_t::SIZE);
}
