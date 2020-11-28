#pragma once

#include <cstdint>
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
    CUnit(uint32_t Owner, EUnitType Type,
            uint32_t PosX, uint32_t PosY,
            uint32_t LifeTime);

    uint32_t m_Owner;
    EUnitType m_Type;
    uint32_t m_PosX;
    uint32_t m_PosY;
    uint32_t m_DirX;
    uint32_t m_DirY;
    uint32_t m_LifeTime;
	std::pair<uint32_t, uint32_t> GetPosition();
};
