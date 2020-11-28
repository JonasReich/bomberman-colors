#pragma once

#include <cstdint>

// Private client state, invisible to other clients.
// This information remains unchanged during the game.
class CLocalState
{
public:
    int32_t m_PlayerNr = 0;
};
