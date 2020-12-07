#pragma once

#include <cstdint>
#include <string>

namespace net_shared
{
    // Turn a uint32_t IP address into a human readable std::string
    std::string TranslateAddress(uint32_t Addr);
}
