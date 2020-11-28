#include "unit_manager.h"

uint32_t CUnitManager::CountPlayerUnits(
        uint32_t iPlayer, EUnitType Type) const
{
    uint32_t Count = 0;

    if(iPlayer < m_PlayerUnits.size())
    {
        const uint32_t CountOfUnits = static_cast<uint32_t>(m_PlayerUnits[iPlayer].size());

        uint32_t iUnit;
        for(iUnit = 0; iUnit < CountOfUnits; iUnit++)
        {
            const CUnit CurrentUnit = m_PlayerUnits[iPlayer][iUnit];
            if(CurrentUnit.m_Type == Type)
                Count++;
        }
    }

    return Count;
}

std::vector<CUnit> CUnitManager::GetPlayerUnits(uint32_t iPlayer, EUnitType Type) const
{
    std::vector<CUnit> Units;

    if(iPlayer < m_PlayerUnits.size())
    {
        const uint32_t CountOfUnits = static_cast<uint32_t>(m_PlayerUnits[iPlayer].size());

        uint32_t iUnit;
        for(iUnit = 0; iUnit < CountOfUnits; iUnit++)
        {
            const CUnit CurrentUnit = m_PlayerUnits[iPlayer][iUnit];
            if(CurrentUnit.m_Type == Type)
                Units.push_back(CurrentUnit);
        }
    }

    return Units;
}

uint32_t CUnitManager::CountPlayerUnitsOnTile(
        uint32_t iPlayer, EUnitType Type, uint32_t x, uint32_t y) const
{
    uint32_t Count = 0;

    if(iPlayer < m_PlayerUnits.size())
    {
        const uint32_t CountOfUnits = static_cast<uint32_t>(m_PlayerUnits[iPlayer].size());

        uint32_t iUnit;
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
        uint32_t iPlayer, EUnitType Type, uint32_t x, uint32_t y) const
{
    std::vector<CUnit> Units;

    if(iPlayer < m_PlayerUnits.size())
    {
        const uint32_t CountOfUnits = static_cast<uint32_t>(m_PlayerUnits[iPlayer].size());

        uint32_t iUnit;
        for(iUnit = 0; iUnit < CountOfUnits; iUnit++)
        {
            const CUnit CurrentUnit = m_PlayerUnits[iPlayer][iUnit];
            if(CurrentUnit.m_Type == Type && CurrentUnit.m_PosX == x && CurrentUnit.m_PosY == y)
                Units.push_back(CurrentUnit);
        }
    }

    return Units;
}

uint32_t CUnitManager::CountAllUnitsOnTile(
        EUnitType Type, uint32_t x, uint32_t y) const
{
    uint32_t Count = 0;

    uint32_t iPlayer;
    for(iPlayer = 0; iPlayer < m_PlayerUnits.size(); iPlayer++)
    {
        uint32_t iUnit;
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
        EUnitType Type, uint32_t x, uint32_t y) const
{
    std::vector<CUnit> UnitsOnTile;

    uint32_t iPlayer;
    for(iPlayer = 0; iPlayer < m_PlayerUnits.size(); iPlayer++)
    {
        uint32_t iUnit;
        for(iUnit = 0; iUnit < m_PlayerUnits[iPlayer].size(); iUnit++)
        {
            const CUnit CurrentUnit = m_PlayerUnits[iPlayer][iUnit];
            if(CurrentUnit.m_Type == Type && CurrentUnit.m_PosX == x && CurrentUnit.m_PosY == y)
                UnitsOnTile.push_back(CurrentUnit);
        }
    }

    return UnitsOnTile;
}

uint32_t CUnitManager::CountAllUnitsOnTile(uint32_t x, uint32_t y) const
{
    uint32_t Count = 0;

    uint32_t iPlayer;
    for(iPlayer = 0; iPlayer < m_PlayerUnits.size(); iPlayer++)
    {
        uint32_t iUnit;
        for(iUnit = 0; iUnit < m_PlayerUnits[iPlayer].size(); iUnit++)
        {
            const CUnit CurrentUnit = m_PlayerUnits[iPlayer][iUnit];
            if(CurrentUnit.m_PosX == x && CurrentUnit.m_PosY == y)
                Count++;
        }
    }

    return Count;
}

std::vector<CUnit> CUnitManager::GetAllUnitsOnTile(uint32_t x, uint32_t y) const
{
    std::vector<CUnit> UnitsOnTile;

    uint32_t iPlayer;
    for(iPlayer = 0; iPlayer < m_PlayerUnits.size(); iPlayer++)
    {
        uint32_t iUnit;
        for(iUnit = 0; iUnit < m_PlayerUnits[iPlayer].size(); iUnit++)
        {
            const CUnit CurrentUnit = m_PlayerUnits[iPlayer][iUnit];
            if(CurrentUnit.m_PosX == x && CurrentUnit.m_PosY == y)
                UnitsOnTile.push_back(CurrentUnit);
        }
    }

    return UnitsOnTile;
}

bool CUnitManager::TileContains(uint32_t x, uint32_t y, EUnitType Type) const
{
    uint32_t iPlayer;
    for(iPlayer = 0; iPlayer < m_PlayerUnits.size(); iPlayer++)
    {
        uint32_t iUnit;
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

bool CUnitManager::TouchesType(uint32_t x, uint32_t y, EUnitType Type) const
{
    return TileContains(x - 1, y, Type) || TileContains(x + 1, y, Type)
            || TileContains(x, y - 1, Type) || TileContains(x, y + 1, Type);
}

std::pair<uint32_t, uint32_t> CUnitManager::GetHeroPosition(uint32_t playerIndex)const
{
	for (uint32_t i = 0; i < m_PlayerUnits[playerIndex].size(); i++)
	{
		if (m_PlayerUnits[playerIndex][i].m_Type == EUnitType::Hero)
			return std::make_pair(m_PlayerUnits[playerIndex][i].m_PosX, m_PlayerUnits[playerIndex][i].m_PosY);
	}

	return std::make_pair(-1, -1); // Einheit nicht gefunden - unm�glichen Wert als Fehler-Marker zur�ckgeben
}
