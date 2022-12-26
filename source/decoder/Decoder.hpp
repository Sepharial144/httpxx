#ifndef _HTTPXX_DECODER_HPP_
#define _HTTPXX_DECODER_HPP_

#include "DecoderDefinitions.hpp"
#include "httpxx_types.hpp"

#include <utility>

namespace httpxx {
    namespace decoder
    {
        void decodeRequest(http_info& res, const void* data, const size_t len);

        void decodeResponse(http_info& res, const void* data, const size_t len);

        int16_t findFirstPrintable(const char* req, const size_t len);

        std::pair<uint16_t, uint16_t> computeRequest(const char* req);
        
        req_t detectRequest(const std::pair<uint16_t, uint16_t>& p);

    } // ! namespace decoder
} // ! namespace httpxx

#endif // !_HTTPXX_DECODER_HPP_