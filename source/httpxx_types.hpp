#ifndef _HTTPXX_TYPES_HPP_
#define _HTTPXX_TYPES_HPP_
 
#include <cstddef>
#include <cstdint>

#define HTTPXX_HTTP_VERSION 0

namespace httpxx
{

    enum class mess_t
    {
        REQUEST,
        RESPONSE
    };

    enum req_t: uint16_t
    {
        GET,
        POST,
        PUT,
        PATCH,
        DELETE,
        COPY,
        HEAD,
        OPTIONS,
        LINK,
        UNLINK,
        PURGE,
        LOCK,
        UNLOCK,
        PROPFIND,
        VIEW,
        SIZE = 15,
    };

    enum http_t: uint16_t
    {
        HTTP_VERSION_11 = 11,
        HTTP_VERSION_2 = 2,
        HTTP_VERSION_3 = 3
    };

    struct http_info
    {
        mess_t type;
        req_t req_type;
        uint32_t len;
        uint64_t errorType;
    };

}

#endif // !_HTTPXX_TYPES_HPP_