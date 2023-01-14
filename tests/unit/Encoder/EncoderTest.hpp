#ifndef _HTTPXX_ENCODER_TEST_HPP_
#define _HTTPXX_ENCODER_TEST_HPP_

#include <cstdint>

#pragma pack(push, 1)

struct TestAlignedHeader
{
    uint8_t data[29] = {'H','e','a','d',' ','w','r','a','p','p','e','d',' ','i','n','t','o',' ','s','t','r','u','c','t','u','r','e','\r','\n'};
};

#pragma pack(pop)

#endif // !_HTTPXX_ENCODER_TEST_HPP_