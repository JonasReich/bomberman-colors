#include "net_shared.h"

#include <iostream>
#include <string>
#include <sstream>

std::string CNet::TranslateAddr(Uint32 Addr)
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
