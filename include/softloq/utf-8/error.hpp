#ifndef SOFTLOQ_UTF_8_ERROR_HPP
#define SOFTLOQ_UTF_8_ERROR_HPP

#include "softloq/utf-8/api/api.hpp"
#include <string>

namespace softloq::utf_8
{

class Char;
namespace octet { class OctetSequence; }

class Error final
{
public:
    enum class Code
    {
        InvalidChar = 1,
        InvalidOctetSequence = 2
    };

    [[nodiscard]] static SOFTLOQ_UTF_8_API Error create_invalid_char_error(const Char& character) noexcept;
    [[nodiscard]] static SOFTLOQ_UTF_8_API Error create_invalid_octet_sequence_error(const octet::OctetSequence& sequence) noexcept;
    
    [[nodiscard]] SOFTLOQ_UTF_8_API Code get_code() const noexcept;
    [[nodiscard]] SOFTLOQ_UTF_8_API const std::string& get_message() const noexcept;
    
private:
    Code code;
    std::string message;

    [[nodiscard]] SOFTLOQ_UTF_8_API Error(Code code, std::string message) noexcept;
};

} // namespace softloq::utf_8

#endif // SOFTLOQ_UTF_8_ERROR_HPP