#ifndef NET_SHARED_H
#define NET_SHARED_H

#include <string>

#include "SDL.h"
#include "SDL_net.h"

class CNet
{
public:
    static std::string TranslateAddr(Uint32 Addr);

private:
    CNet();
};

// BEWARE: NOT TESTED YET!!! NEED TO VERIFY IF BUFFER-OVERFLOW POSSIBLE.
template<typename Type>
class TCNet
{
public:
    // NOTE: works only for compile-time fix-sized types!
    static bool Send(TCPsocket Socket, const Type &Value);

    // NOTE: works only for compile-time fix-sized types!
    static bool Recv(TCPsocket Socket, Type &Value);

private:
    TCNet();
};

template<typename Type>
bool TCNet<Type>::Send(TCPsocket Socket, const Type &Value)
{
    char Buffer[sizeof(Type)];
    memcpy((void *)Buffer, (void *)&Value, sizeof(Type));

    if(SDLNet_TCP_Send(Socket, (void *)Buffer, sizeof(Type)) != sizeof(Type))
        return false;

    return true;
}

template<typename Type>
bool TCNet<Type>::Recv(TCPsocket Socket, Type &Value)
{
    char Buffer[sizeof(Type)];
    if(SDLNet_TCP_Send(Socket, (void *)Buffer, sizeof(Type)) != sizeof(Type))
        return false;

    memcpy((void *)(&Value), (void *)Buffer, sizeof(Type));

    return true;
}

#endif
