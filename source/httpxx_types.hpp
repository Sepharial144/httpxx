#ifndef _HTTPXX_TYPES_HPP_
#define _HTTPXX_TYPES_HPP_
 
#include <cstdint>

namespace httpxx
{
    enum req
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
        VIEW
    };

    struct header
    {

    };

    struct http_info
    {
        req type;
        uint32_t len;
    };

}

#endif // !_HTTPXX_TYPES_HPP_