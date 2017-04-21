#include "unit.h"

CUnit::CUnit()
: m_Type(UNIT_TYPE_NONE), m_LifeTime(0)
{
}

CUnit::CUnit(
        unsigned int Owner,
        UnitType Type,
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
