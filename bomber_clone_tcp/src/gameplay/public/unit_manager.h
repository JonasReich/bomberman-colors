#pragma once

#include <cstdint>
#include <vector>
#include "unit.h"

class CUnitManager
{
public:
	std::pair<int32_t, int32_t> GetHeroPosition(uint32_t playerIndex)const;

    uint32_t CountPlayerUnits(uint32_t Player, EUnitType Type) const;
    std::vector<CUnit> GetPlayerUnits(uint32_t Player, EUnitType Type) const;

    uint32_t CountPlayerUnitsOnTile(uint32_t Player, EUnitType Type, uint32_t x, uint32_t y) const;
    std::vector<CUnit> GetPlayerUnitsOnTile(uint32_t Player, EUnitType Type, uint32_t x, uint32_t y) const;

    uint32_t CountAllUnitsOnTile(EUnitType Type, uint32_t x, uint32_t y) const;
    std::vector<CUnit> GetAllUnitsOnTile(EUnitType Type, uint32_t x, uint32_t y) const;

    uint32_t CountAllUnitsOnTile(uint32_t x, uint32_t y) const;
    std::vector<CUnit> GetAllUnitsOnTile(uint32_t x, uint32_t y) const;

    bool TileContains(uint32_t x, uint32_t y, EUnitType Type) const;
    bool TouchesType(uint32_t x, uint32_t y, EUnitType Type) const;

    // List of all units for each player.
    // Indexed by player ID.
    std::vector<std::vector<CUnit> > m_PlayerUnits;
};
