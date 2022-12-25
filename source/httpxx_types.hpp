#ifndef _HTTPXX_TYPES_HPP_
#define _HTTPXX_TYPES_HPP_
 
#include <cstdint>

namespace httpxx
{

    enum class mess_t
    {
        REQUEST,
        RESPONSE
    };

    enum req_t
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

    struct header
    {

    };

    struct http_info
    {
        mess_t type;
        req_t req_type;
        uint32_t len;
    };

}

#endif // !_HTTPXX_TYPES_HPP_