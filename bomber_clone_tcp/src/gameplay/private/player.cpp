#include "player.h"

CPlayer::CPlayer()
: m_BombNr(1),m_ExplosionSize(2)
{
}

CPlayer::CPlayer(
        uint32_t BombNr,
        uint32_t ExplosionSize)
: m_BombNr(BombNr), m_ExplosionSize(ExplosionSize)
{
}
