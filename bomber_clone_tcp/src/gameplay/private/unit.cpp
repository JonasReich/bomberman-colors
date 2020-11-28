#include "unit.h"

CUnit::CUnit()
: m_Type(EUnitType::None), m_LifeTime(0)
{
}

CUnit::CUnit(
        unsigned int Owner,
        EUnitType Type,
        int PosX, int PosY,
        unsigned int LifeTime)
: m_Owner(Owner),  m_Type(Type),
  m_PosX(PosX), m_PosY(PosY),
  m_LifeTime(LifeTime)
{
}

std::pair<unsigned int, unsigned int> CUnit::GetPosition()
{
	return std::pair<unsigned int, unsigned int>((unsigned int)m_PosX, (unsigned int)m_PosY);
}
