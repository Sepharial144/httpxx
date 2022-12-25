#ifndef _HTTPXX_HPP_
#define _HTTPXX_HPP_

#include <iostream>

#include "Request.hpp"
 
namespace httpxx
{
    template <mess_t type_message>
    constexpr void encode(http_info& res, const void* data, size_t len)
    {
        if (type_message == mess_t::REQUEST)
            return;
        if (type_message == mess_t::RESPONSE)
            return;
    }

    template <mess_t type_message>
    constexpr void decode(http_info& res, const void* data, size_t len)
    {
        if (type_message == mess_t::REQUEST)
            return;
        if (type_message == mess_t::RESPONSE)
            return;

    }
}

#endif // !_HTTPXX_HPP_