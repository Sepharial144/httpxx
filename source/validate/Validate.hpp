#ifndef _HTTPXX_VALIDATE_HPP_
#define _HTTPXX_VALIDATE_HPP_

#include "httpxx_types.hpp"

namespace httpxx 
{
    namespace validate
    {
        req_t typeRequest(const char* data);

        int16_t url(const char* url, size_t len);
        
    } // namespace validate
} // namespace httpxx

#endif // !_HTTPXX_VALIDATE_HPP_