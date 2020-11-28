#pragma once

#include <vector>
#include "unit.h"

class CUnitManager
{
public:
	std::pair<unsigned int, unsigned int> GetHeroPosition(unsigned int playerIndex)const;

    unsigned int CountPlayerUnits(unsigned int Player, EUnitType Type) const;
    std::vector<CUnit> GetPlayerUnits(unsigned int Player, EUnitType Type) const;

    unsigned int CountPlayerUnitsOnTile(unsigned int Player, EUnitType Type, unsigned int x, unsigned int y) const;
    std::vector<CUnit> GetPlayerUnitsOnTile(unsigned int Player, EUnitType Type, unsigned int x, unsigned int y) const;

    unsigned int CountAllUnitsOnTile(EUnitType Type, unsigned int x, unsigned int y) const;
    std::vector<CUnit> GetAllUnitsOnTile(EUnitType Type, unsigned int x, unsigned int y) const;

    unsigned int CountAllUnitsOnTile(unsigned int x, unsigned int y) const;
    std::vector<CUnit> GetAllUnitsOnTile(unsigned int x, unsigned int y) const;

    bool TileContains(unsigned int x, unsigned int y, EUnitType Type) const;
    bool TouchesType(unsigned int x, unsigned int y, EUnitType Type) const;

    std::vector<std::vector<CUnit> > m_PlayerUnits;
};
