#include "EncodeRequestGet.hpp"

EncodeRequestGet::EncodeRequestGet()
  :m_url{"/url"},
   m_head{"Connection: keep-alive"},
   m_data{"{json data}"},
   m_httpType{GetParam()},
   m_lastStatus{0ul}    
{
    std::memset(m_request.data(), 0, 1024);
    m_expected.reserve(1024);
    m_expected.clear();
}

void EncodeRequestGet::SetUp()
{
    std::memset(m_request.data(), 0, 1024);
    m_expected.reserve(1024);
    m_expected.clear();

    m_expected.append("GET ");
    m_expected.append("/url ");
    const std::string httpVersion = generateHttpVersion(GetParam());
    m_expected.append(httpVersion.data(), httpVersion.size());
    m_expected.append("\r\n");
    m_expected.append("Connection: keep-alive\r\n{json data}");
    // TODO: upgrade to Content-Length property

}

std::string EncodeRequestGet::generateHttpVersion(httpxx::http_t http_type)
{
    if (http_type == httpxx::http_t::HTTP_VERSION_11)
        return std::string{httpxx::factory::getHttpVersion<httpxx::http_t::HTTP_VERSION_11>()};
    if (http_type == httpxx::http_t::HTTP_VERSION_2)
        return std::string{httpxx::factory::getHttpVersion<httpxx::http_t::HTTP_VERSION_2>()};
    if (http_type == httpxx::http_t::HTTP_VERSION_3)
        return std::string{httpxx::factory::getHttpVersion<httpxx::http_t::HTTP_VERSION_3>()};

    return "";
}

void EncodeRequestGet::generateRequestHttpParametrized()
{
    m_lastStatus = httpxx::encoder::request(httpxx::req_t::GET, m_httpType,
            reinterpret_cast<void*>(m_request.data()), m_request.size(),
            reinterpret_cast<const void*>(m_url), strlen(m_url), 
            reinterpret_cast<const void*>(m_head), strlen(m_head), 
            reinterpret_cast<const void*>(m_data), strlen(m_data));
}

const char* EncodeRequestGet::getExpectedValue() const
{
    return reinterpret_cast<const char*>(m_request.data());
}

const char* EncodeRequestGet::getResultValue() const 
{
    return m_expected.data();
}

size_t EncodeRequestGet::getStatus() const
{
    return m_lastStatus;
}