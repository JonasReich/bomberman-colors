#include "player.h"

CPlayer::CPlayer()
: m_BombNr(1),m_ExplosionSize(2)
{
}

CPlayer::CPlayer(
        unsigned int BombNr,
        unsigned int ExplosionSize)
: m_BombNr(BombNr), m_ExplosionSize(ExplosionSize)
{
}
