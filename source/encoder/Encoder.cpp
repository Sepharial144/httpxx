#include "Encoder.hpp"
#include "Factory.hpp"

#include <cstring>
#include <ios>
#include <cmath>
#include <iostream>

namespace httpxx 
{
    namespace encoder
    {

        int32_t request(const req_t request_type, 
                    const http_t http_type,
                    void* res, const size_t len,
                    const void* url,  const size_t u_len, 
                    const void* head, const size_t h_len, 
                    const void* body, const size_t b_len)
        {
            uint8_t* result = reinterpret_cast<uint8_t*>(res);
            size_t resultLen = encodeRequestType(result, 0ul, request_type);
            resultLen = whiteSpace(result, resultLen);

            resultLen = encodeUrl(result, resultLen, (const char*)url, u_len);
            resultLen = whiteSpace(result, resultLen);

            resultLen = encodeHttpVersion(result, resultLen, http_type);
            resultLen = endLine(result, resultLen);

            resultLen = encodeLine(result, resultLen, (const char*)head, h_len);
            resultLen = endLine(result, resultLen);

            if (body != nullptr)
                return encodeLine(result, resultLen, (const char*)body, b_len);
            return resultLen;
        }


        int32_t request(const req_t request_type,
                    void* res, const size_t len,
                    const void* url, const size_t u_len, 
                    const void* head, const size_t h_len, 
                    const void* body, const size_t b_len)
        {
            uint8_t* result = reinterpret_cast<uint8_t*>(res);

            size_t resultLen = encodeRequestType(result, 0ul, request_type);
            resultLen = whiteSpace(result, resultLen);

            resultLen = encodeUrl(result, resultLen, reinterpret_cast<const char*>(url), u_len);
            resultLen = whiteSpace(result, resultLen);

            resultLen = encodeHttpVersion(result, resultLen); 
            resultLen = endLine(result, resultLen);

            resultLen = encodeLine(result, resultLen, reinterpret_cast<const char*>(head), h_len);
            resultLen = endLine(result, resultLen);

            if (body != nullptr)
                return encodeLine(result, resultLen, reinterpret_cast<const char*>(body), b_len);

            return resultLen;
        }


        int32_t request(const req_t request_type,
                    void* res, const size_t len,
                    const void* url, const size_t u_len,
                    const uint64_t* head_fields_arr, 
                    const void* body, const size_t b_len)
        {
            // TODO: finish the request implementation
            uint8_t* result = reinterpret_cast<uint8_t*>(res);

            size_t resultLen = encodeRequestType(result, 0ul, request_type);
            resultLen = whiteSpace(result, resultLen);

            resultLen = encodeUrl(result, resultLen, (const char*)url, u_len);
            resultLen = whiteSpace(result, resultLen);

            resultLen = encodeHttpVersion(result, resultLen); 
            return endLine(result, resultLen);
            return 0;
        }

        size_t encodeHead(uint8_t* res, const size_t offset, 
                          const uint64_t* field_ref_array, const size_t prop_rows)
        {
            //int32_t rowIndex = prop_rows;
            size_t length = offset;    
            // TODO: refactoring to use for loop, last time got segmentation fault
            for (int32_t i = 0; i != prop_rows; ++i)
            {
                uint8_t* pData = reinterpret_cast<uint8_t*>(*field_ref_array);
                while (*pData)
                {
                    std::memcpy(res + length, pData, 1ul);
                    ++length;
                    ++pData;
                }
                length = endLine(res, length);
                ++field_ref_array;
            }
                  
            return length;
        }

        
        head_field field(const char* field)
        {
            return head_field{field, strlen(field)};
        }


        size_t encodeField(uint8_t* res, const size_t offset, 
                        const char* field_name, const size_t field_len,
                        const uint64_t* prop_ref_array, const size_t prop_rows,
                        const char separator[], const size_t len_separator)
        {
            constexpr uint8_t fieldSeparator[2] = {':',' '};
            size_t length = offset;

            std::memcpy(res + length, field_name, field_len);
            length += field_len;
            std::memcpy(res + length, &fieldSeparator[0], 2ul);
            length += 2ul;
            return encodeProperties(res, length, prop_ref_array, prop_rows, separator, len_separator);
        }


        size_t encodeProperties(uint8_t* res, const size_t offset, 
                    const uint64_t* prop_ref_array, const size_t prop_rows,
                    const char separator[], const size_t len_separator)
        {
            int32_t rowIndex = prop_rows;
            size_t length = offset;    
            // TODO: refactoring to use for loop, last time got segmentation fault      
            while(--rowIndex != -1)
            {
                uint8_t* pData = reinterpret_cast<uint8_t*>(*prop_ref_array);
                while (*pData)
                {
                    std::memcpy(res + length, pData, 1ul);
                    ++length;
                    ++pData;
                }
                if(rowIndex != 0)
                {
                    std::memcpy(res + length, &separator[0], len_separator);
                    length += len_separator;
                }

                ++prop_ref_array;
            }
            return endLine(res, length);
        }
     
        // TODO: extend translate number to double, float
        size_t translateNumber(char* res, uint16_t number)
        {
            int16_t len = static_cast<int16_t>(log10(number)) + 1ul;
            res += len;
            *res = '\0';
            for (int16_t i = len; i >= 0; --i)
            {
                constexpr int16_t divider = 10u;
                --res;
                *res = static_cast<char>((number % divider) + 48u);
                number /= divider;
            }
            return static_cast<size_t>(len);
        }


        size_t encodeRequestType(uint8_t* res, const size_t offset, req_t request_type)
        {
            const char* reqType = nullptr;
            size_t resSize = 0ul;

            if (offset > 0)
                std::memset(res, ' ', offset);

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

        size_t encodeHttpVersion(uint8_t* res, const size_t offset)
        {
            size_t httpLength = 0ul;
            const char* httpVersion = nullptr;

            if (HTTP_VERSION == 11)
            {
                httpVersion = factory::getHttpVersion<http_t::HTTP_VERSION_11>();
                httpLength = factory::getHttpVersionSize<http_t::HTTP_VERSION_11>();
            } 
            else if (HTTP_VERSION == 2)
            {
                httpVersion = factory::getHttpVersion<http_t::HTTP_VERSION_2>();
                httpLength = factory::getHttpVersionSize<http_t::HTTP_VERSION_2>();
            } 
            else if (HTTP_VERSION == 3)
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
    } // ! namespace encoder
} // ! namespace httpxx