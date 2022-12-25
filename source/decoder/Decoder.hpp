#ifndef _HTTPXX_DECODER_HPP_
#define _HTTPXX_DECODER_HPP_

#include <cstddef>
#include <cstdint>
#include <utility>

#include "httpxx_types.hpp"

#define HTTPXX_REQUEST_GET_LEFT 138u
#define HTTPXX_REQUEST_GET_RIGHT 69u
#define HTTPXX_REQUEST_POST_LEFT 158u
#define HTTPXX_REQUEST_POST_RIGHT 163u
#define HTTPXX_REQUEST_PUT_LEFT 170u
#define HTTPXX_REQUEST_PUT_RIGHT 85u
#define HTTPXX_REQUEST_PATCH_LEFT 130u
#define HTTPXX_REQUEST_PATCH_RIGHT 132u
#define HTTPXX_REQUEST_DELETE_LEFT 138u
#define HTTPXX_REQUEST_DELETE_RIGHT 138u
#define HTTPXX_REQUEST_COPY_LEFT 158u
#define HTTPXX_REQUEST_COPY_RIGHT 168u
#define HTTPXX_REQUEST_HEAD_LEFT 138u
#define HTTPXX_REQUEST_HEAD_RIGHT 137u
#define HTTPXX_REQUEST_OPTIONS_LEFT 160u
#define HTTPXX_REQUEST_OPTIONS_RIGHT 153u
#define HTTPXX_REQUEST_LINK_LEFT 146u
#define HTTPXX_REQUEST_LINK_RIGHT 148u
#define HTTPXX_REQUEST_UNLINK_LEFT 156u
#define HTTPXX_REQUEST_UNLINK_RIGHT 151u
#define HTTPXX_REQUEST_PURGE_LEFT 170u
#define HTTPXX_REQUEST_PURGE_RIGHT 156u
#define HTTPXX_REQUEST_LOCK_LEFT 158u
#define HTTPXX_REQUEST_LOCK_RIGHT 154u
#define HTTPXX_REQUEST_UNLOCK_LEFT 156u
#define HTTPXX_REQUEST_UNLOCK_RIGHT 157u
#define HTTPXX_REQUEST_PROPFIND_LEFT 164u
#define HTTPXX_REQUEST_PROPFIND_RIGHT 162u
#define HTTPXX_REQUEST_VIEW_LEFT 146u
#define HTTPXX_REQUEST_VIEW_RIGHT 160u

namespace httpxx {
    namespace decoder
    {
        void decodeRequest(http_info& res, const void* data, size_t len);

        void decodeResponse(http_info& res, const void* data, size_t len);

        [[deprecated]] uint16_t accumulateRequest(const char* req, uint16_t len = 3u);

        std::pair<uint16_t, uint16_t> computeRequest(const char* req);
        
        req_t detectRequest(std::pair<uint16_t, uint16_t>& p);

    } // ! namespace decoder
} // ! namespace httpxx

#endif // !_HTTPXX_DECODER_HPP_