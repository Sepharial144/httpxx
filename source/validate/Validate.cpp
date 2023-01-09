#include "Validate.hpp"

namespace httpxx 
{
    namespace validate
    {
        req_t typeRequest(const char* data)
        {
            if (*data == 'G' && *(data + 1) == 'E' && *(data + 2) == 'T')
                return req_t::GET;

            if (*data == 'P')
            {
                if(*(data + 1) == 'O' && 
                   *(data + 2) == 'S' && 
                   *(data + 3) == 'T')
                    return req_t::POST;

                if(*(data + 1) == 'U' && 
                   *(data + 2) == 'T') 
                    return req_t::PUT;

                if(*(data + 1) == 'A' && 
                   *(data + 2) == 'T' && 
                   *(data + 3) == 'C' && 
                   *(data + 4) == 'H')
                    return req_t::PATCH;

                if(*(data + 1) == 'U' && 
                   *(data + 2) == 'R' && 
                   *(data + 3) == 'G' && 
                   *(data + 4) == 'E')
                    return req_t::PURGE;

                if(*(data + 1) == 'R' && 
                   *(data + 2) == 'O' && 
                   *(data + 3) == 'P' && 
                   *(data + 4) == 'F' &&
                   *(data + 5) == 'I' &&
                   *(data + 6) == 'N' &&
                   *(data + 7) == 'D')
                    return req_t::PROPFIND;
            }

            if (*data == 'H')
            {
                if(*(data + 1) == 'E' && 
                   *(data + 2) == 'A' &&
                   *(data + 3) == 'D')
                   return req_t::HEAD;
            }

            if (*data == 'C' && 
                *(data + 1) == 'O' && 
                *(data + 2) == 'P' && 
                *(data + 3) == 'Y')
                return req_t::COPY;

            if (*data == 'L')
            {
                if(*(data + 1) == 'I' && 
                   *(data + 2) == 'N' &&
                   *(data + 3) == 'K')
                    return req_t::LINK;

                if(*(data + 1) == 'O' && 
                   *(data + 2) == 'C' &&
                   *(data + 3) == 'K')
                   return req_t::LOCK;
            }

            if (*data == 'U' && *(data + 1) == 'N' && *(data + 2) == 'L')
            {
                if(*(data + 3) == 'I' && 
                   *(data + 4) == 'N' &&
                   *(data + 5) == 'K')
                    return req_t::UNLINK;

                if(*(data + 3) == 'O' && 
                   *(data + 4) == 'C' &&
                   *(data + 5) == 'K')
                   return req_t::UNLOCK;
            }

            if (*data == 'O' && 
                *(data + 1) == 'P' && 
                *(data + 2) == 'T' && 
                *(data + 3) == 'I' && 
                *(data + 4) == 'O' && 
                *(data + 5) == 'N' &&
                *(data + 6) == 'S')
                return req_t::OPTIONS;

            if (*data == 'V' && 
                *(data + 1) == 'I' && 
                *(data + 2) == 'E' && 
                *(data + 3) == 'W')
                return req_t::VIEW;

            if (*data == 'D' && 
                *(data + 1) == 'E' && 
                *(data + 2) == 'L' && 
                *(data + 3) == 'E' &&
                *(data + 4) == 'T' &&
                *(data + 5) == 'E')
                return req_t::DELETE;

            return req_t::SIZE;
        }

        int16_t url(const char* url, size_t len)
        {

            // url begin error
            if (*url != '/')
                return -1;

            if (len == 1ul)
                return len;

            size_t pos = 0ul;
            while(pos != len)
            {
                if (*(url + pos) == '/')
                {
                    size_t remain = len - pos;
                    char nextLetter = *(url + pos + 1);
                    if (remain == 1 || nextLetter == ' ')
                    {
                        // last slash error
                        return -1;
                    }

                    if(nextLetter == '/') {
                        //double slash error
                        return -1;
                    }

                }

                char letter  = *url;
                if (letter <= '/' || letter >= ':' && letter <= '@')
                    //unreadble symbol
                ++pos;
            }

            return len;
        }
    } // namespace validate
} // namespace httpxx