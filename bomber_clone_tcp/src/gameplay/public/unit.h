#pragma once

#include <queue>

/** Unit type changes behavior and visuals of a unit. */
enum class EUnitType
{
    // [meta] Invalid/undefined unit type
    None,
    // Bomb that can be placed by players to attack
    Bomb,
    // Fire zone created by bomb explosion
    Fire,
    // Player controlled character/hero
    Hero,
    // [meta] Total number of unit types
    Count
};

/** A unit is a dynamic entity owned/controlled by one of the playersdw */
class CUnit
{
public:
    CUnit();
    CUnit(unsigned int Owner, EUnitType Type,
            int PosX, int PosY,
            unsigned int LifeTime);

    unsigned int m_Owner;
    EUnitType m_Type;
    int m_PosX;
    int m_PosY;
    int m_DirX;
    int m_DirY;
    unsigned int m_LifeTime;
	std::pair<unsigned int, unsigned int> GetPosition();
};
