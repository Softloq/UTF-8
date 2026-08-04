#include "softloq/utf-8/pch/pch.hpp"
#include "softloq/utf-8/octet/error.hpp"
#include "softloq/utf-8/octet/octet.hpp"

namespace softloq::utf_8::octet
{

Error::Error(Code code, std::string message) noexcept : code(code), message(std::move(message)) {}

Error Error::create_invalid_octet_error(const Octet& octet) noexcept
{
    return Error(Code::InvalidOctet, "Invalid octet value: " + std::to_string(octet.get_value()));
}

Error::Code Error::get_code() const noexcept { return code; }
const std::string& Error::get_message() const noexcept { return message; }

} // namespace softloq::utf_8::octet