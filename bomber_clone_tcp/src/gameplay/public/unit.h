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

/** A unit is a dynamic entity owned/controlled by one of the players */
class CUnit
{
public:
    CUnit() = default;
    CUnit(uint32_t Owner, EUnitType Type,
            uint32_t PosX, uint32_t PosY,
            uint32_t LifeTime);

    uint32_t m_Owner = 0;
    EUnitType m_Type = EUnitType::None;
    uint32_t m_PosX = 0;
    uint32_t m_PosY = 0;
    uint32_t m_DirX = 0;
    uint32_t m_DirY = 0;
    uint32_t m_LifeTime = 0;
	std::pair<uint32_t, uint32_t> GetPosition();
};
