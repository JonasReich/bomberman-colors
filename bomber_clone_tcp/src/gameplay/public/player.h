#pragma once

#include <cstdint>

// Informations about player, can vary per round.
class CPlayer
{
public:
    CPlayer() = default;
    CPlayer(uint32_t BombNr, uint32_t ExplosionSize);

    uint32_t m_ExplosionSize = 2;
    uint32_t m_BombNr = 1;
};
