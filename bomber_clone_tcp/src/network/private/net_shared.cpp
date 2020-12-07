#include "net_shared.h"

#include <iostream>
#include <string>
#include <sstream>

std::string net_shared::TranslateAddress(uint32_t Addr)
{
    std::stringstream s;

    s << ((Addr >> 0) & 0xff);
    s << ".";
    s << ((Addr >> 8) & 0xff);
    s << ".";
    s << ((Addr >> 16) & 0xff);
    s << ".";
    s << ((Addr >> 24) & 0xff);

    return s.str();
}
