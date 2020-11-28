#include "unit_manager.h"

unsigned int CUnitManager::CountPlayerUnits(
        unsigned int iPlayer, UnitType Type) const
{
    unsigned int Count = 0;

    if(iPlayer < m_PlayerUnits.size())
    {
        const unsigned int CountOfUnits = static_cast<unsigned int>(m_PlayerUnits[iPlayer].size());

        unsigned int iUnit;
        for(iUnit = 0; iUnit < CountOfUnits; iUnit++)
        {
            const CUnit CurrentUnit = m_PlayerUnits[iPlayer][iUnit];
            if(CurrentUnit.m_Type == Type)
                Count++;
        }
    }

    return Count;
}

std::vector<CUnit> CUnitManager::GetPlayerUnits(unsigned int iPlayer, UnitType Type) const
{
    std::vector<CUnit> Units;

    if(iPlayer < m_PlayerUnits.size())
    {
        const unsigned int CountOfUnits = static_cast<unsigned int>(m_PlayerUnits[iPlayer].size());

        unsigned int iUnit;
        for(iUnit = 0; iUnit < CountOfUnits; iUnit++)
        {
            const CUnit CurrentUnit = m_PlayerUnits[iPlayer][iUnit];
            if(CurrentUnit.m_Type == Type)
                Units.push_back(CurrentUnit);
        }
    }

    return Units;
}

unsigned int CUnitManager::CountPlayerUnitsOnTile(
        unsigned int iPlayer, UnitType Type, unsigned int x, unsigned int y) const
{
    unsigned int Count = 0;

    if(iPlayer < m_PlayerUnits.size())
    {
        const unsigned int CountOfUnits = static_cast<unsigned int>(m_PlayerUnits[iPlayer].size());

        unsigned int iUnit;
        for(iUnit = 0; iUnit < CountOfUnits; iUnit++)
        {
            const CUnit CurrentUnit = m_PlayerUnits[iPlayer][iUnit];
            if(CurrentUnit.m_Type == Type && CurrentUnit.m_PosX == x && CurrentUnit.m_PosY == y)
                Count++;
        }
    }

    return Count;
}

std::vector<CUnit> CUnitManager::GetPlayerUnitsOnTile(
        unsigned int iPlayer, UnitType Type, unsigned int x, unsigned int y) const
{
    std::vector<CUnit> Units;

    if(iPlayer < m_PlayerUnits.size())
    {
        const unsigned int CountOfUnits = static_cast<unsigned int>(m_PlayerUnits[iPlayer].size());

        unsigned int iUnit;
        for(iUnit = 0; iUnit < CountOfUnits; iUnit++)
        {
            const CUnit CurrentUnit = m_PlayerUnits[iPlayer][iUnit];
            if(CurrentUnit.m_Type == Type && CurrentUnit.m_PosX == x && CurrentUnit.m_PosY == y)
                Units.push_back(CurrentUnit);
        }
    }

    return Units;
}

unsigned int CUnitManager::CountAllUnitsOnTile(
        UnitType Type, unsigned int x, unsigned int y) const
{
    unsigned int Count = 0;

    unsigned int iPlayer;
    for(iPlayer = 0; iPlayer < m_PlayerUnits.size(); iPlayer++)
    {
        unsigned int iUnit;
        for(iUnit = 0; iUnit < m_PlayerUnits[iPlayer].size(); iUnit++)
        {
            const CUnit CurrentUnit = m_PlayerUnits[iPlayer][iUnit];
            if(CurrentUnit.m_Type == Type && CurrentUnit.m_PosX == x && CurrentUnit.m_PosY == y)
                Count++;
        }
    }

    return Count;
}

std::vector<CUnit> CUnitManager::GetAllUnitsOnTile(
        UnitType Type, unsigned int x, unsigned int y) const
{
    std::vector<CUnit> UnitsOnTile;

    unsigned int iPlayer;
    for(iPlayer = 0; iPlayer < m_PlayerUnits.size(); iPlayer++)
    {
        unsigned int iUnit;
        for(iUnit = 0; iUnit < m_PlayerUnits[iPlayer].size(); iUnit++)
        {
            const CUnit CurrentUnit = m_PlayerUnits[iPlayer][iUnit];
            if(CurrentUnit.m_Type == Type && CurrentUnit.m_PosX == x && CurrentUnit.m_PosY == y)
                UnitsOnTile.push_back(CurrentUnit);
        }
    }

    return UnitsOnTile;
}

unsigned int CUnitManager::CountAllUnitsOnTile(unsigned int x, unsigned int y) const
{
    unsigned int Count = 0;

    unsigned int iPlayer;
    for(iPlayer = 0; iPlayer < m_PlayerUnits.size(); iPlayer++)
    {
        unsigned int iUnit;
        for(iUnit = 0; iUnit < m_PlayerUnits[iPlayer].size(); iUnit++)
        {
            const CUnit CurrentUnit = m_PlayerUnits[iPlayer][iUnit];
            if(CurrentUnit.m_PosX == x && CurrentUnit.m_PosY == y)
                Count++;
        }
    }

    return Count;
}

std::vector<CUnit> CUnitManager::GetAllUnitsOnTile(unsigned int x, unsigned int y) const
{
    std::vector<CUnit> UnitsOnTile;

    unsigned int iPlayer;
    for(iPlayer = 0; iPlayer < m_PlayerUnits.size(); iPlayer++)
    {
        unsigned int iUnit;
        for(iUnit = 0; iUnit < m_PlayerUnits[iPlayer].size(); iUnit++)
        {
            const CUnit CurrentUnit = m_PlayerUnits[iPlayer][iUnit];
            if(CurrentUnit.m_PosX == x && CurrentUnit.m_PosY == y)
                UnitsOnTile.push_back(CurrentUnit);
        }
    }

    return UnitsOnTile;
}

bool CUnitManager::TileContains(unsigned int x, unsigned int y, UnitType Type) const
{
    unsigned int iPlayer;
    for(iPlayer = 0; iPlayer < m_PlayerUnits.size(); iPlayer++)
    {
        unsigned int iUnit;
        for(iUnit = 0; iUnit < m_PlayerUnits[iPlayer].size(); iUnit++)
        {
            const CUnit CurrentUnit = m_PlayerUnits[iPlayer][iUnit];
            if(CurrentUnit.m_PosX == x && CurrentUnit.m_PosY == y)
                if(CurrentUnit.m_Type == Type)
                    return true;
        }
    }

    return false;
}

bool CUnitManager::TouchesType(unsigned int x, unsigned int y, UnitType Type) const
{
    return TileContains(x - 1, y, Type) || TileContains(x + 1, y, Type)
            || TileContains(x, y - 1, Type) || TileContains(x, y + 1, Type);
}

std::pair<unsigned int, unsigned int> CUnitManager::GetHeroPosition(unsigned int playerIndex)const
{
	for (unsigned int i = 0; i < m_PlayerUnits[playerIndex].size(); i++)
	{
		if (m_PlayerUnits[playerIndex][i].m_Type == UNIT_TYPE_HERO)
			return std::make_pair(m_PlayerUnits[playerIndex][i].m_PosX, m_PlayerUnits[playerIndex][i].m_PosY);
	}

	return std::make_pair(-1, -1); // Einheit nicht gefunden - unm�glichen Wert als Fehler-Marker zur�ckgeben
}
