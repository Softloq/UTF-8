#include "softloq/utf-8/pch/pch.hpp"
#include "softloq/utf-8/error.hpp"
#include "softloq/utf-8/char.hpp"
#include "softloq/utf-8/octet/octet-sequence.hpp"

namespace softloq::utf_8
{

Error::Error(Code code, std::string message) noexcept : code(code), message(std::move(message)) {}

Error Error::create_invalid_char_error(const Char& character) noexcept
{
    return Error(Code::InvalidChar, "Invalid character with code point: " + std::to_string(character.get_code_point()));
}

Error Error::create_invalid_octet_sequence_error(const octet::OctetSequence& sequence) noexcept
{
    return Error(Code::InvalidOctetSequence, "Invalid octet sequence");
}

Error::Code Error::get_code() const noexcept { return code; }
const std::string& Error::get_message() const noexcept { return message; }

} // namespace softloq::utf_8