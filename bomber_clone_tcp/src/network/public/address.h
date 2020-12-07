#pragma once

#include <cstdint>

class CAddr
{
public:
    CAddr();
    CAddr(uint32_t IP, unsigned short Port);

    uint32_t m_IP;
    unsigned short m_Port;
};

bool operator==(const CAddr &L, const CAddr &R);
bool operator<(const CAddr &L, const CAddr &R);
