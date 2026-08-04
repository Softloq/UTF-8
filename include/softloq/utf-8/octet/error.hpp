#ifndef SOFTLOQ_UTF_8_OCTET_ERROR_HPP
#define SOFTLOQ_UTF_8_OCTET_ERROR_HPP

#include "softloq/utf-8/api/api.hpp"
#include <string>

namespace softloq::utf_8::octet
{

class Octet;

class Error
{
public:
    enum class Code
    {
        InvalidOctet = 1
    };

    static SOFTLOQ_UTF_8_API Error create_invalid_octet_error(const Octet& octet) noexcept;
    
    SOFTLOQ_UTF_8_API Code get_code() const noexcept;
    SOFTLOQ_UTF_8_API const std::string& get_message() const noexcept;
    
private:
    Code code;
    std::string message;

    SOFTLOQ_UTF_8_API Error(Code code, std::string message) noexcept;
};

} // namespace softloq::utf_8::octet

#endif // SOFTLOQ_UTF_8_OCTET_ERROR_HPP