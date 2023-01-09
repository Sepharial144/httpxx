#include "Encoder.hpp"
#include "Factory.hpp"

#include <cstring>
#include <ios>

namespace httpxx 
{
    int32_t encode(const req_t request_type, 
                   const http_t http_type,
                   const void* url, const size_t u_len, 
                   const void* head, const size_t h_len, 
                   const void* body, const size_t b_len, 
                   void* res, const size_t len)
    {
        uint8_t* result = (uint8_t*)res;
        size_t resultLen = encodeRequestType(result, 0ul, request_type);
        resultLen = whiteSpace(result, resultLen);

        resultLen = encodeUrl(result, resultLen, (const char*)url, u_len);
        resultLen = whiteSpace(result, resultLen);

        resultLen = encodeHttpVersion(result, resultLen, http_type);
        resultLen = endLine(result, resultLen);

        resultLen = encodeLine(result, resultLen, (const char*)head, h_len);
        resultLen = endLine(result, resultLen);
        resultLen = endLine(result, resultLen);

        return encodeLine(result, resultLen, (const char*)body, b_len);
    }

    size_t encodeRequestType(uint8_t* res, const size_t offset, req_t request_type)
    {
        const char* reqType = nullptr;
        size_t resSize = 0ul;

        if (request_type == req_t::GET)
        {
            reqType = factory::getRequestParams<req_t::GET>(resSize);
        }
        else if (request_type == req_t::POST)
        {
            reqType = factory::getRequestParams<req_t::POST>(resSize);
        } else 
        {
            return 0;
        }
        std::memcpy(res + offset, reqType, resSize);

        return offset + resSize;
    }

    size_t encodeUrl(uint8_t* res, const size_t offset, const char* url, const size_t url_len)
    {
        std::memcpy(res + offset, url, url_len);
        return offset + url_len;
    }

    size_t encodeHttpVersion(uint8_t* res, const size_t offset, http_t http_type)
    {
        size_t httpLength = 0ul;
        const char* httpVersion = nullptr;

        if (http_type == http_t::HTTP_VERSION_11)
        {
            httpVersion = factory::getHttpVersion<http_t::HTTP_VERSION_11>();
            httpLength = factory::getHttpVersionSize<http_t::HTTP_VERSION_11>();
        } 
        else if (http_type == http_t::HTTP_VERSION_2)
        {
            httpVersion = factory::getHttpVersion<http_t::HTTP_VERSION_2>();
            httpLength = factory::getHttpVersionSize<http_t::HTTP_VERSION_2>();
        } 
        else if (http_type == http_t::HTTP_VERSION_3)
        {
            httpVersion = factory::getHttpVersion<http_t::HTTP_VERSION_3>();
            httpLength = factory::getHttpVersionSize<http_t::HTTP_VERSION_3>();
        } else 
        {
            return 0ul;
        }

        std::memcpy(res + offset, httpVersion, httpLength);
        return offset + httpLength;
    }

    size_t encodeLine(uint8_t* res, const size_t offset, const char* line, const size_t len)
    {
        std::memcpy(res + offset, line, len);
        return offset + len;
    }

    size_t endLine(uint8_t* res, const size_t offset)
    {
        constexpr size_t len = 2ul;
        constexpr char clrf[len] = {0x0D, 0x0A};
        std::memcpy(res + offset, &clrf[0], len);
        return offset + len;
    }

    size_t whiteSpace(uint8_t* res, const size_t offset)
    {
        constexpr char whiteSpace = ' ';
        size_t len = 1ul;
        std::memcpy(res + offset, &whiteSpace, len);
        return offset + len;
    }
} // ! namespace httpxx