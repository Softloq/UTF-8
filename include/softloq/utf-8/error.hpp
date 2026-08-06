#ifndef SOFTLOQ_UTF_8_ERROR_HPP
#define SOFTLOQ_UTF_8_ERROR_HPP

#include "softloq/utf-8/api/api.hpp"

#include <string>

namespace softloq::utf_8
{

class Char;
class Octet;
class OctetSequence;

class Error final
{
public:
    enum class Code
    {
        InvalidChar = 1,
        InvalidOctet = 2,
        InvalidOctetSequence = 3,
        InvalidOctetSequenceLength = 4
    };

    [[nodiscard]] static SOFTLOQ_UTF_8_API Error create_invalid_char_error(const Char& character) noexcept;
    [[nodiscard]] static SOFTLOQ_UTF_8_API Error create_invalid_octet_error(const Octet& octet) noexcept;
    [[nodiscard]] static SOFTLOQ_UTF_8_API Error create_invalid_octet_sequence_error(const OctetSequence& sequence) noexcept;
    [[nodiscard]] static SOFTLOQ_UTF_8_API Error create_invalid_octet_sequence_length_error(std::size_t expected_length, std::size_t actual_length) noexcept;

    [[nodiscard]] SOFTLOQ_UTF_8_API Code get_code() const noexcept;
    [[nodiscard]] SOFTLOQ_UTF_8_API const std::string& get_message() const noexcept;
    
private:
    Code code;
    std::string message;

    [[nodiscard]] SOFTLOQ_UTF_8_API Error(Code code, const std::string& message) noexcept;
};

} // namespace softloq::utf_8

#endif // SOFTLOQ_UTF_8_ERROR_HPP