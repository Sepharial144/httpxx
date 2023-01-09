#ifndef _HTTPXX_FACTORY_HPP_
#define _HTTPXX_FACTORY_HPP_

#include "httpxx_types.hpp"
 
namespace httpxx
{
    namespace factory
    {
        template <http_t http_version>
        constexpr const char* getHttpVersion()
        {
            if (http_version == http_t::HTTP_VERSION_11)
                return "HTTP1/1";

            if (http_version == http_t::HTTP_VERSION_2)
                return "HTTP2";

            if (http_version == http_t::HTTP_VERSION_3)
                return "HTTP3";
        }

        template <http_t http_version>
        constexpr size_t getHttpVersionSize()
        {
            if (http_version == http_t::HTTP_VERSION_11)
                return 7ul;

            if (http_version == http_t::HTTP_VERSION_2 || 
                http_version == http_t::HTTP_VERSION_3)
                return 5ul;
        }

        template <req_t type>
        constexpr uint16_t getRequestSize()
        {
            if (type == req_t::GET || type == req_t::PUT)
                return 3u;
            if (type == req_t::POST || 
                type == req_t::COPY || 
                type == req_t::HEAD || 
                type == req_t::LINK || 
                type == req_t::LOCK || 
                type == req_t::VIEW)
                return 4u;
            
            if (type == req_t::PATCH || type == req_t::PURGE)
                return 5u;

            if (type == req_t::DELETE || type == req_t::UNLINK || type == req_t::UNLOCK)
                return 6u;

            if (type == req_t::OPTIONS)
                return 7u;

            if (type == req_t::PROPFIND)
                return 8u;

            return static_cast<uint16_t>(req_t::SIZE);
        }

        template <req_t type>
        constexpr const char* getRequestString()
        {
            if (type == req_t::GET)
                return "GET";
            if (type == req_t::POST)
                return "POST";
            if (type == req_t::PUT)
                return "PUT";
            if (type == req_t::PATCH)
                return "PATCH";
            if (type == req_t::DELETE)
                return "DELETE";
            if (type == req_t::COPY)
                return "COPY";
            if (type == req_t::HEAD)
                return "HEAD";
            if (type == req_t::OPTIONS)
                return "OPTIONS";
            if (type == req_t::LINK)
                return "LINK";
            if (type == req_t::UNLINK)
                return "UNLINK";
            if (type == req_t::PURGE)
                return "PURGE";
            if (type == req_t::LOCK)
                return "LOCK";
            if (type == req_t::UNLOCK)
                return "UNLOCK";
            if (type == req_t::PROPFIND)
                return "PROPFIND";
            if (type == req_t::VIEW)
                return "VIEW";
            return nullptr;
        }

        template <req_t type>
        constexpr const char* getRequestParams(size_t& len)
        {
            len = getRequestSize<type>();
            return getRequestString<type>();
        }
    } // ! namespace factory
} // ! namespace httpx

#endif // !_HTTPXX_FACTORY_HPP_