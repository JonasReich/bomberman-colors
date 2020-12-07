#include "address.h"

CAddr::CAddr()
: m_IP(0), m_Port(0)
{
}

CAddr::CAddr(uint32_t IP, unsigned short Port)
: m_IP(IP), m_Port(Port)
{
}

bool operator==(const CAddr &L, const CAddr &R)
{
    if(L.m_IP != R.m_IP)
        return false;

    if(L.m_Port != R.m_Port)
        return false;

    return true;
}

bool operator<(const CAddr &L, const CAddr &R)
{
    if(L.m_IP < R.m_IP)
        return true;

    if(L.m_IP > R.m_IP)
        return false;

    if(L.m_Port < R.m_Port)
        return true;

    return false;
}
