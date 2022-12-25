#ifndef _HTTPXX_FACTORY_HPP_
#define _HTTPXX_FACTORY_HPP_

#include "httpxx_types.hpp"
 
namespace httpxx
{
    namespace factory
    {
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
    } // ! namespace factory
} // ! namespace httpx

#endif // !_HTTPXX_FACTORY_HPP_