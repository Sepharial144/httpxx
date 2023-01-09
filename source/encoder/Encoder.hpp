#ifndef _HTTPXX_ENCODER_HPP_
#define _HTTPXX_ENCODER_HPP_

#include "httpxx_types.hpp"

namespace httpxx 
{
    int32_t encode(const req_t request_type, 
                   const http_t http_type,
                   const void* url, const size_t u_len, 
                   const void* head, const size_t h_len, 
                   const void* body, const size_t b_len,
                   void* res, const size_t len);

    size_t encodeRequestType(uint8_t* res, const size_t offset, req_t request_type);

    size_t encodeUrl(uint8_t* res, const size_t offset, const char* url, const size_t url_len);

    size_t encodeHttpVersion(uint8_t* res, const size_t offset, http_t http_type);

    size_t encodeLine(uint8_t* res, const size_t offset, const char* line, const size_t len);

    size_t endLine(uint8_t* res, const size_t offset);

    size_t whiteSpace(uint8_t* res, const size_t offset);

} // ! namespace httpxx

#endif // !_HTTPXX_ENCODER_HPP_