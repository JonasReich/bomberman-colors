#pragma once

#include <cstdint>

// Public server state.
// This information changes during the game.
class CGlobalState
{
public:
    CGlobalState();
    
    uint32_t m_Round;
    uint32_t m_Cycle;

    uint32_t m_Score[4];
};
