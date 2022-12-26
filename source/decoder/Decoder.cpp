#include "Decoder.hpp"

#include <cmath>

namespace httpxx {
    namespace decoder
    {
        void decodeRequest(http_info& res, const void* data, const size_t len)
        {
            if (len < HTTPXX_DECODER_REQ_MAX_SIZE)
            {
                res.errorType = 1000ul;
                return;
            }

            const char* request = (char*)(data);
            int16_t pos = findFirstPrintable(request, len);

            if(pos == HTTPXX_DECODER_ERROR)
            {
                // TODO: implement error types
                // bad packet error
                res.errorType = 1001ul;
                return;
            }

            std::pair<uint16_t, uint16_t> reqType = computeRequest(request + pos);
            req_t requestType = detectRequest(reqType);
            if (requestType == req_t::SIZE)
            {
                // detected bad request type
                res.errorType = 1002ul;
                return;
            }

        }

        void decodeResponse(http_info& res, const void* data, const size_t len)
        {
            
        }

        int16_t findFirstPrintable(const char* req, const size_t len)
        {
            if(len <= HTTPXX_DECODER_LIMIT_PACKET)
                return HTTPXX_DECODER_ERROR;

            for(uint16_t pos = 0u; 0 != HTTPXX_DECODER_MAX_REQ_SHIFT; ++pos)
            {
                uint16_t letter = (uint16_t)*(req + pos);
                if (letter == HTTPXX_DECODER_SPACE_LETTER)
                    continue;

                if (letter >= HTTPXX_DECODER_FIRST_READABLE_LETTER && 
                    letter <= HTTPXX_DECODER_LAST_READABLE_LETTER)
                    return pos;

                if (letter <= HTTPXX_DECODER_UNREADABLE_LETTERS || 
                    letter == HTTPXX_DECODER_DEL_LETTER)
                    break;
            }
            return HTTPXX_DECODER_ERROR;
        }

        // TODO: refactoring
        int16_t findLetter(const char* data, const size_t len, const char letter)
        {
            if (len - HTTPXX_DECODER_MAX_REQ_SHIFT <= 0)
                return HTTPXX_DECODER_ERROR;

            for(size_t i = 0u; i <= HTTPXX_DECODER_MAX_REQ_SHIFT; ++i)
            {
                if (*data == letter)
                    return i;
            }
            return HTTPXX_DECODER_ERROR;
        }

        std::pair<uint16_t, uint16_t> computeRequest(const char* req)
        {
            uint16_t middle = static_cast<int16_t>(*(req + 1));
            uint16_t left = static_cast<uint16_t>(*req) + middle;

            constexpr uint16_t conflictUnl_left = 163u;
            uint16_t right = (left != conflictUnl_left)? 
                static_cast<uint16_t>(*(req + 2)): 
                static_cast<uint16_t>(*(req + 3));
            right += middle;
            return {left, right};
        }

        req_t detectRequest(const std::pair<uint16_t, uint16_t>& p)
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