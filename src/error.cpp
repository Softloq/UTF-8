#include "softloq/utf-8/pch/pch.hpp"
#include "softloq/utf-8/error.hpp"
#include "softloq/utf-8/char.hpp"
#include "softloq/utf-8/octet-sequence.hpp"

namespace softloq::utf_8
{

Error::Error(Code code, const std::string& message) noexcept : code(code), message(message) {}

Error Error::create_invalid_char_error(const Char& character) noexcept
{
    return Error(Code::InvalidChar, "Invalid character with code point: " + std::to_string(character.get_code_point()));
}

Error Error::create_invalid_octet_error(const Octet& octet) noexcept
{
    return Error(Code::InvalidOctet, "Invalid octet with value: " + std::to_string(octet.get_value()));
}

Error Error::create_invalid_octet_sequence_error(const OctetSequence& sequence) noexcept
{
    return Error(Code::InvalidOctetSequence, "Invalid octet sequence");
}

Error Error::create_invalid_octet_sequence_length_error(std::size_t expected_length, std::size_t actual_length) noexcept
{
    return Error(Code::InvalidOctetSequenceLength, "Invalid octet sequence length. Expected: " + std::to_string(expected_length) + ", Actual: " + std::to_string(actual_length));
}

Error Error::create_invalid_octet_sequence_index_error(std::size_t index, std::size_t length) noexcept
{
    return Error(Code::InvalidOctetSequenceIndex, "Invalid octet sequence index. Index: " + std::to_string(index) + ", Length: " + std::to_string(length));
}

Error Error::create_encoding_empty_char_sequence_error() noexcept
{
    return Error(Code::EncodingEmptyCharSequence, "Cannot encode an empty character sequence");
}

Error::Code Error::get_code() const noexcept { return code; }

const std::string& Error::get_message() const noexcept { return message; }

} // namespace softloq::utf_8