#pragma once

// Informations about player, can vary per round.
class CPlayer
{
public:
    CPlayer();
    CPlayer(unsigned int BombNr,
            unsigned int ExplosionSize);

    unsigned int m_ExplosionSize;
    unsigned int m_BombNr;
};
