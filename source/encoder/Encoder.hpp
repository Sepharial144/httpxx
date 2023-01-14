#ifndef _HTTPXX_ENCODER_HPP_
#define _HTTPXX_ENCODER_HPP_

#include "httpxx_types.hpp"
#include <cstring>

//#ifdef HTTPXX_HTTP_ENABLE_VERSION
//    #define HTTP_VERSION HTTPXX_HTTP_ENABLE_VERSION
//#else
#define HTTP_VERSION 11
//#endif

namespace httpxx 
{
    namespace encoder
    {
        int32_t request(const req_t request_type, 
                    const http_t http_type,
                    void* res, const size_t len,
                    const void* url, const size_t u_len, 
                    const void* head, const size_t h_len, 
                    const void* body, const size_t b_len);

        int32_t request(const req_t request_type,
                    void* res, const size_t len,
                    const void* url, const size_t u_len, 
                    const void* head, const size_t h_len, 
                    const void* body, const size_t b_len);

        int32_t request(const req_t request_type,
                    void* res, const size_t len,
                    const uint64_t* head_fields_arr, 
                    const void* body, const size_t b_len);

        size_t encodeHead(uint8_t* res, const size_t offset, 
                          const uint64_t* field_ref_array, const size_t prop_rows);

        head_field field(const char* field);

        size_t encodeField(uint8_t* res, const size_t offset, 
                        const char* field_name, const size_t field_len,
                        const uint64_t* prop_ref_array, const size_t prop_rows,
                        const char separator[], const size_t len_separator);

        size_t encodeProperties(uint8_t* res, const size_t offset, 
                    const uint64_t* prop_ref_array, const size_t prop_rows,
                    const char separator[], const size_t len_separator);

        size_t encodeHost(uint8_t* res, const size_t offset, const char* host, const size_t len);

        size_t encodeRequestType(uint8_t* res, const size_t offset, req_t request_type);

        size_t encodeUrl(uint8_t* res, const size_t offset, const char* url, const size_t url_len);

        size_t encodeHttpVersion(uint8_t* res, const size_t offset);

        size_t encodeHttpVersion(uint8_t* res, const size_t offset, http_t http_type);

        size_t encodeLine(uint8_t* res, const size_t offset, const char* line, const size_t len);

        size_t translateNumber(char* res, uint16_t number);

        size_t endLine(uint8_t* res, const size_t offset);

        size_t whiteSpace(uint8_t* res, const size_t offset);

        template <class CustomHead>
        size_t encodeHead(uint8_t* res, const size_t offset, const CustomHead& head)
        {
            size_t len = offset;
            constexpr char clrf[2] = {0x0D, 0x0A};
            const void* pHead = &head;
            std::memcpy(res + offset, (const void*)&head, sizeof(CustomHead));
            len += sizeof(CustomHead);
            return len;
        }

        template <typename T>
        constexpr uint64_t arrayReference(const T* letter_arr)
        {
            return reinterpret_cast<uint64_t>(&letter_arr[0]);
        }

    } // ! namespace encode
} // ! namespace httpxx

#endif // !_HTTPXX_ENCODER_HPP_