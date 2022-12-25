#include "Decoder.hpp"

namespace httpxx {
    namespace decoder
    {
        void decodeRequest(http_info& res, const void* data, size_t len)
        {

        }

        void decodeResponse(http_info& res, const void* data, size_t len)
        {

        }

        [[deprecated]]
        uint16_t accumulateRequest(const char* req, uint16_t len)
        {
            uint16_t res = static_cast<int16_t>(*req);
            for(uint16_t i = len; i != 0; --i)
            {
                ++req;
                res += static_cast<int16_t>(*req);
            }
            constexpr uint16_t UnlReqConflict = 239ul;
            if (res == UnlReqConflict)
                res += static_cast<int16_t>(*(req+5));
            return res;
        }

       std::pair<uint16_t, uint16_t> computeRequest(const char* req)
        {
            uint16_t middle = static_cast<int16_t>(*++req);
            uint16_t left = static_cast<int16_t>(*req) + middle;
            uint16_t right = static_cast<int16_t>(*(req + 2)) + middle;

            return {left, right};
        }

        req_t detectRequest(std::pair<uint16_t, uint16_t>& p)
        {
            if( p.first == HTTPXX_REQUEST_GET_LEFT && p.second == HTTPXX_REQUEST_GET_RIGHT)
                return req_t::GET;
            if( p.first == HTTPXX_REQUEST_POST_LEFT && p.second == HTTPXX_REQUEST_POST_RIGHT)
                return req_t::POST;
            if( p.first == HTTPXX_REQUEST_PUT_LEFT && p.second == HTTPXX_REQUEST_PUT_RIGHT)
                return req_t::PUT;
            if( p.first == HTTPXX_REQUEST_PATCH_LEFT && p.second == HTTPXX_REQUEST_PATCH_RIGHT)
                return req_t::PATCH;
            if( p.first == HTTPXX_REQUEST_DELETE_LEFT && p.second == HTTPXX_REQUEST_DELETE_RIGHT)
                return req_t::DELETE;
            if( p.first == HTTPXX_REQUEST_COPY_LEFT && p.second == HTTPXX_REQUEST_COPY_RIGHT)
                return req_t::COPY;
            if( p.first == HTTPXX_REQUEST_HEAD_LEFT && p.second == HTTPXX_REQUEST_HEAD_RIGHT)
                return req_t::HEAD;
            if( p.first == HTTPXX_REQUEST_OPTIONS_LEFT && p.second == HTTPXX_REQUEST_OPTIONS_RIGHT)
                return req_t::OPTIONS;
            if( p.first == HTTPXX_REQUEST_LINK_LEFT && p.second == HTTPXX_REQUEST_LINK_RIGHT)
                return req_t::LINK;
            if( p.first == HTTPXX_REQUEST_UNLINK_LEFT && p.second == HTTPXX_REQUEST_UNLINK_RIGHT)
                return req_t::UNLINK;
            if( p.first == HTTPXX_REQUEST_PURGE_LEFT && p.second == HTTPXX_REQUEST_PURGE_RIGHT)
                return req_t::PURGE;
            if( p.first == HTTPXX_REQUEST_LOCK_LEFT && p.second == HTTPXX_REQUEST_LOCK_RIGHT)
                return req_t::LOCK;
            if( p.first == HTTPXX_REQUEST_UNLOCK_LEFT && p.second == HTTPXX_REQUEST_UNLOCK_RIGHT)
                return req_t::UNLOCK;
            if( p.first == HTTPXX_REQUEST_PROPFIND_LEFT && p.second == HTTPXX_REQUEST_PROPFIND_RIGHT)
                return req_t::PROPFIND;
            if( p.first == HTTPXX_REQUEST_VIEW_LEFT && p.second == HTTPXX_REQUEST_VIEW_RIGHT)
                return req_t::VIEW;
            return req_t::SIZE;
        }
    } // ! namespace decoder
} // ! namespace httpxx