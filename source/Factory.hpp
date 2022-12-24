#ifndef _FACTORY_HPP_
#define _FACTORY_HPP_

#include "httpxx_types.hpp"
 
namespace httpxx
{
    namespace factory
    {
        template <req type>
        constexpr const char* getRequestString()
        {
            if (type == req::GET)
                return "GET";
            if (type == req::POST)
                return "POST";
            if (type == req::PUT)
                return "PUT";
            if (type == req::PATCH)
                return "PATCH";
            if (type == req::DELETE)
                return "DELETE";
            if (type == req::COPY)
                return "COPY";
            if (type == req::HEAD)
                return "HEAD";
            if (type == req::OPTIONS)
                return "OPTIONS";
            if (type == req::LINK)
                return "LINK";
            if (type == req::UNLINK)
                return "UNLINK";
            if (type == req::PURGE)
                return "PURGE";
            if (type == req::LOCK)
                return "LOCK";
            if (type == req::UNLOCK)
                return "UNLOCK";
            if (type == req::PROPFIND)
                return "PROPFIND";
            if (type == req::VIEW)
                return "VIEW";
            return nullptr;
        }
    }
}

#endif // !_FACTORY_HPP_