#ifndef ADDRESS_H 
#define ADDRESS_H

class CAddr
{
public:
    CAddr();
    CAddr(unsigned int IP, unsigned short Port);

    unsigned int m_IP;
    unsigned short m_Port;
};

bool operator==(const CAddr &L, const CAddr &R);
bool operator<(const CAddr &L, const CAddr &R);

#endif
